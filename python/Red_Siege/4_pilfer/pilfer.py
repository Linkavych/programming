#!/usr/bin/env python3
"""
A program for finding interesting files that might contain passwords
or other juicy information.

Program: pilfer.py
Author: Adam V. Link
Date: 2021-11-12

License:
Copyright 2021 Adam V. Link

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and 
the following disclaimer in the documentation and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or 
promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, 
INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; 
OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
"""
import argparse
import re
import sys
from logging import ERROR
from pathlib import Path

try:
    from loguru import logger
except ImportError:
    print("[!] The 'loguru' module is required.")
    sys.exit(1)


def arguments():
    """
    Function to take in any argumentes required by the program.

    Params:
        None
    Return:
        Arguments namespace
    """
    parser = argparse.ArgumentParser(
        description="Tool for finding interesting files with potential passwords."
    )
    parser.add_argument(
        "-e", "--extensions", type=Path, help="File with extensions to test"
    )

    parser.add_argument("-n", "--names", type=Path, help="List of file")
    parser.add_argument(
        "-p", "--path", type=Path, help="Starting path for search", required=True
    )
    parser.add_argument(
        "-s", "--strings", type=Path, help="File with strings to search for"
    )

    return parser.parse_args()


def file_to_list(filename):
    """
    Creates a list of items from a file
    Params:
        file - list of some items
    Return:
        list
    """
    items = []

    with open(filename, "r", encoding="utf-8") as fd:
        for line in fd.readlines():
            items.append(line.strip())

    return items


def find_files_by_name(file_path, name):
    """
    Find interesting files

    Params:
        file_path - Starting file path
        check_files - a list of file names to check, provided by user as a file
    Returns:
        List of interesting files with their full path
    """
    files = list(file_path.rglob(name + ".*"))

    return files


def check_file_content(filepath, string):
    """
    Fucntion to check the contents of a file for interesting information.

    Params:
        Filename - name of the file to search the contents of
    Return:
        None
    """
    pattern = re.compile(string)

    logger.info(f"[*] Searching: {filepath}...")

    for line in open(filepath, "r", encoding="utf-8"):
        for match in re.finditer(pattern, line):
            logger.success(f"[+] Found '{string}' at: {line}")


def main():
    """
    Main function for the pilfering
    """
    args = arguments()

    # Test for variables
    if not args.names:
        logger.info("[*] Using default filenames...")
        filenames = ["wp-config", "password", "secret", "api", "apikey", "id_rsa", "id"]
    else:
        logger.info("[*] Custom file names loading...")
        filenames = file_to_list(args.names)

    if not args.extensions:
        logger.info("[*] Using default file extensions...")
        extensions = ["conf", "config", "py", "txt", "ini", "xml", "key"]
    else:
        logger.info("[*] Custom file extensions loading...")
        extensions = file_to_list(args.extensions)

    if not args.strings:
        logger.info("[*] Using default strings...")
        strings = ["username", "pass", "password", "key", "apikey", "api_key", "secret"]
    else:
        logger.info("[*] Custom strings loading...")
        strings = file_to_list(args.strings)

    # Start doing the work now; first find files matching names
    logger.info("[*] Beginning to pilfer...")

    found_files = []
    try:
        for name in filenames:
            temp = find_files_by_name(args.path, name)
            for n in temp:
                found_files.append(str(n))
    except FileNotFoundError:
        pass

    # Check found files against relevant extensions
    logger.info("[*] Checking for relevant file extensions...")

    interesting_files = []
    try:
        for item in found_files:
            for ext in extensions:
                if item.endswith(ext):
                    interesting_files.append(item)
                else:
                    pass
    except ERROR:
        pass

    logger.info(f"[*] Checking {len(interesting_files)} files for information...")

    for item in interesting_files:
        for string in strings:
            check_file_content(item, string)


if __name__ == "__main__":
    main()
