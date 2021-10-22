#!/usr/bin/env python3
# A web fuzzing tool with python and threading
# Made to reinforce learning python
# Author: @linkavych
# Modified: 2021-06-25
import argparse
import logging
import os
import requests
import sys

from logging.handlers import RotatingFileHandler
from multiprocessing.pool import ThreadPool
from pathlib import Path, PurePath
from requests.packages import urllib3

urllib3.disable_warnings()

# Configure workers
ASYNCH_WORKERS_COUNT = 100  # Number of threads running for http requests
WORKERS_DECREMENTED_COUNT = 10  # Retry fuzzing with x less worker to decrease load
STARTED_JOB_LOG_INTERVAL = 100  # Every x jobs, write a log entry

# IO Stuff
DEFAULT_PATHS_LIST_FILE = (
    "/usr/share/seclists/Discovery/Web-Content/raft-small-words.txt"
)
VALID_ENDPOINTS_FILE = "endpoints.txt"

# HTTP CONFIG
RESOURCE_EXISTS_STATUS_CODES = list(range(200, 300)) + [401, 402, 403]

# LOGGING CONFIG
LOGS_DIR_NAME = "logs"
LOG_FORMAT = "%(asctime)s - %(name)s - %(levelname)s - %(message)s"
LOGGING_LEVEL = logging.INFO
BACKUP_COUNT = 5
FUZZING_LOGGER_NAME = "fuzzing"
LOG_FILE_MAX_BYTES = 0.5 * 1000 * 1000  # 500 KB


class FileHelper(object):
    """
    Helps to manage all files and directories provided as input.

    PARAMETER:
        file (object)
    """

    files = []
    urls = []

    def read_files_dir(self, user_path):
        self.files = [
            Path(user_path).joinpath(f)
            for f in Path(user_path).iterdir()
            if Path(user_path).joinpath(f).is_file
        ]

    def read_lines_from_file(self):
        for file in self.files:
            hst = open(file, "r")
            self.urls += hst.read().splitlines()

    def __init__(self, user_path):
        if Path(user_path).is_dir():
            self.read_files_dir(user_path)
            self.read_lines_from_file()
        elif Path(user_path).is_file():
            self.files.append(user_path)
            self.read_lines_from_file()


class LogFacility(object):
    """
    Manage logging facilities
    """

    loggers = {}
    log_level = LOGGING_LEVEL
    logging.basicConfig(stream=sys.stdout, level=log_level, format=LOG_FORMAT)

    # Modify log level to ERROR
    logging.getLogger("urllib3").setLevel(logging.WARNING)

    @staticmethod
    def get_logger(logger_name):
        """
        Gets a logger by name

        PARAMETER:
            logger_name - identifier for logger
        RETURN:
            logger instance
        """
        if logger_name not in LogFacility.loggers:
            LogFacility.loggers[logger_name] = LogFacility._get_logger(logger_name)

        return LogFacility.loggers[logger_name]

    @staticmethod
    def _get_logger(logger_name, logs_directory_path=LOGS_DIR_NAME):
        """
        Create a logger with file handler, or return if exists.

        PARAMETER:
            logger_name - identifier for logger
            logs_directory_path - Path where logs will be written
        Return:
            initialized logger instance
        """
        # Create a logs foler if !exists
        if not Path.cwd().joinpath(logs_directory_path).exists():
            Path.cwd().joinpath(logs_directory_path).mkdir()

        logger = logging.getLogger(logger_name)
        formatter = logging.Formatter(LOG_FORMAT)
        path = Path.cwd().joinpath(logs_directory_path)

        # File handler
        rotating_file_handler = RotatingFileHandler(
            path.joinpath("{0}.log".format(logger_name)),
            maxBytes=LOG_FILE_MAX_BYTES,
            backupCount=BACKUP_COUNT,
        )

        rotating_file_handler.setFormatter(formatter)
        rotating_file_handler.setLevel(LOGGING_LEVEL)
        logger.addHandler(rotating_file_handler)

        return logger


class AsyncURLFuzz(object):
    """
    Asycnhronous fuzzing of a website.
    Tests for endpoints based on a list.
    """

    def __init__(
        self,
        base_url,
        list_file=DEFAULT_PATHS_LIST_FILE,
        async_workers=ASYNCH_WORKERS_COUNT,
        output_file=VALID_ENDPOINTS_FILE,
        resource_exists=RESOURCE_EXISTS_STATUS_CODES,
    ):
        """
        Initialize a new class instance.

        PARAMETER:
            base_url (str) - base url of website
            list_file (str) - path of a file containing paths to test
            async_workers (int) - Number of threads (100 default)
            output_file (str) - Name of active endpoints output file
            resource_exists (list) - List of HTTP status codes (valid)
        """
        self._logger = LogFacility.get_logger(FUZZING_LOGGER_NAME)
        self._base_url = base_url
        self._list_file_path = list_file
        self._async_workers = async_workers
        self._output_file_path = output_file
        self._resource_exists = resource_exists
        self._active_paths_status_codes = {}
        self._checked_endpoints = {}
        self._endpoints_total_count = {}
        self._session = requests.session()

    def start(self):
        """
        Start the process
        """
        self._get_endpoints()

    def _get_endpoints(self, async_workers=ASYNCH_WORKERS_COUNT):
        """
        Send async requests with threads. If failure, workers are reduced.

        PARAMETERS:
            async_workers (int) - Number of threads (default 100)
        """
        self._load_paths_list()
        self._logger.info(
            'Getting endpoints for {0} with file "{1}" and {2} workers.'.format(
                self._base_url, self._list_file_path, async_workers
            )
        )

        if 0 >=  async_workers:
            self._logger.error("DDOS protection likely in place.")
            return

        pool = ThreadPool(async_workers)
        try:
            tasks = []
            self._logger.debug("Starting workers...")
            for i, path in enumerate(self._paths):
                self._logger.debug("Started worker for endpoint {0}".format(path))
                if i > i and i % STARTED_JOB_LOG_INTERVAL == 0:
                    self._logger.info("Started {0} workers.".format(i))

                path = path.strip()
                full_path = "/".join([self._base_url, path])
                tasks.append(pool.apply_async(self.request_head, (full_path, path)))

            for t in tasks:
                status_code, full_path, path = t.get()
                self._checked_endpoints[path] = path
                if self._is_valid_status_code(status_code):
                    self._active_paths_status_codes[path] = status_code
                self._logger.info(
                    "Retrieved {0}/{1}; {2}; {3}".format(
                        len(self._checked_endpoints),
                        self._endpoints_total_count,
                        status_code,
                        full_path,
                    )
                )

            self._save_output_log()

        except requests.ConnectionError as e:
            pool.terminate()
            self._logger.error(e)
            self._logger.warning(
                "An error has occured." " Retrying with fewer workers."
            )
            retry_workers_count = WORKERS_DECREMENTED_COUNT
            self._get_enpoints(retry_workers_count)

    def _is_valid_status_code(self, status_code):
        """
        Tests the retrieved status code against a list of valid codes.

        PARAMETER:
            status_code (int) - HTTP status code
        RETURN:
            bool - True if status code is valid else False
        """
        return status_code in self._resource_exists

    def _save_output_log(self):
        """
        Saves the results of tests to a file.
        """
        full_status_codes = {
            "/".join([self._base_url, p]): code
            for p, code in self._active_paths_status_codes.items()
        }
        output_lines = [
            "{0} : {1}".format(path, code) for path, code in full_status_codes.items()
        ]

        if 1 >= len(output_lines):
            self._logger.warning(
                "There are no discovered endpoints. Try a different file."
            )
        self._logger.info(
            "The following endpoints are active: {0}{1}".format(
                os.linesep, os.linesep.join(output_lines)
            )
        )

        with open(self._output_file_path, 'w') as output_file:
            output_lines.sort()
            output_file.write(os.linesep.join(output_lines))

        self._logger.info("Endpoints exported to {0}.".format(self._output_file_path))

    def _load_paths_list(self):
        """
        Loads the list of paths from config status.
        """
        if not Path(self._list_file_path).exists():
            raise FileNotFoundError(
                'The file "{0}" does not exist'.format(self._list_file_path)
            )
        with open(self._list_file_path) as paths_file:
            paths = [p.strip().lstrip("/").rstrip("/") for p in paths_file.readlines()]
            paths = [p for p in paths if p not in self._active_paths_status_codes]
            if not self._endpoints_total_count:
                self._endpoints_total_count = len(paths)
            self._paths = paths

    def request_head(self, url, path):
        """
        Executes an HTTP HEAD request.

        PARAMETERS:
            url (str) - Full url to test.
            path (str) - URI of the request
        RETURN:
            tuple:
                received status code (int)
                url argument (str)
                path (str)
        """
        if url != "":
            res = self._session.head(url, verify=False, allow_redirects=True)
            return res.status_code, url, path


if __name__ == "__main__":
    # Argparse section
    parser = argparse.ArgumentParser(
        description="Asynchronous website fuzzing tool."
        "\nAttempts to determine the presence of endpoints.",
        usage="fuzzer.py -u http://www.example.com/ -w wordlist.txt",
    )
    parser.add_argument(
        "-u", "--url", dest="base_url", help="Target website.", required=True
    )
    parser.add_argument(
        "-w",
        "--wordlist",
        dest="list_file",
        help="File containing paths to test.",
        required=True,
    )
    args = parser.parse_args()

    list_file = args.list_file
    base_url = args.base_url

    if base_url is None:
        parser.print_help()
        sys.exit()

    logging.getLogger("urllib3").setLevel(logging.ERROR)
    logging.getLogger("requests").setLevel(logging.ERROR)

    # Execution from here
    if Path(base_url).is_dir() or Path(base_url).is_file():
        FileHelper(base_url)
        for u in FileHelper.urls:
            fuzzer = AsyncURLFuzz(u, list_file)
            fuzzer.start()
    else:
        fuzzer = AsyncURLFuzz(base_url, list_file)
        fuzzer.start()
