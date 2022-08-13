#!/usr/bin/env python3
"""
Search for files containing possible passwords, keys, or other useful credentials
on a system.

Author: @linkavych
Date: 2022-08-13
"""
import re
import sys
from pathlib import Path

# Non-typical libraries for CLI stuff
try:
    import typer
    from rich import print
    from rich.console import Console
    from rich.table import Table

except ImportError:
    print("[!] The python libraries 'rich' and 'typer' are required.")
    sys.exit(1)

console = Console()

INTERESTING_INFO = []


def file_to_list(filename: str):
    """
    Convert a given file into a list of strings
    """
    items = []

    with open(filename, "r", encoding="utf-8") as fd:
        for line in fd.readlines():
            items.append(line.strip())

    return items


def find_files_by_name(file_path, name):
    """
    find interesting files
    """
    files = list(file_path.rglob(name + ".*"))

    return files


def check_contents(filepath: str, regex: str):
    """
    Check the content of a file for keywords
    """
    pattern = re.compile(regex)

    # Puts out alot of extra messages, but can be useful for tracking all files searched
    # console.log(f"[+] Searching: {filepath}...")

    for line in open(filepath, "r", encoding="utf-8"):
        for match in re.finditer(pattern, line):
            INTERESTING_INFO.append((regex, filepath, line))


def main(
    path: str = typer.Option(..., help="Path from which to being the search."),
    ext: str = typer.Option("", help="Newline separated file of fil extensions"),
    names: str = typer.Option("", help="Newline separated file of file names"),
    strings: str = typer.Option("", help="Newline separated file of strings to search."),
):
    """
    Main function for processing our search for interesting information
    """
    table = Table(title="Interesting Information")
    table.add_column("Regex", justify="center", style="green")
    table.add_column("Path", justify="center", style="blue")
    table.add_column("Data", justify="center", style="red")

    if ext:
        extensions = file_to_list(ext)
    else:
        extensions = ["conf", "config", "py", "txt", "ini", "xml", "key"]
    if names:
        filenames = file_to_list(names)
    else:
        filenames = [
            "wp-config",
            "password",
            "passwd",
            "secret",
            "passwords",
            "api",
            "key",
            "keys",
            "api",
            "apikeys",
            "api_key",
            "id_rsa",
            "id",
        ]
    if strings:
        string_list = file_to_list(strings)
    else:
        string_list = [
            "username",
            "pass",
            "passwd",
            "password",
            "key",
            "api_key",
            "apikey",
            "secret",
        ]

    path = Path(path)

    console.log("[+] Beginning search...")

    found_files = []
    try:
        for name in filenames:
            temp = find_files_by_name(path, name)
            for item in temp:
                found_files.append(str(item))
    except FileNotFoundError:
        pass

    console.log(f"[+] Testing against {len(extensions)} file extensions...")

    interesting_files = []
    try:
        for file in found_files:
            for extension in extensions:
                if file.endswith(extension):
                    interesting_files.append(file)
                else:
                    pass
    except Error:
        pass

    console.log(f"[+] Checking {len(interesting_files)} files for information...")

    for i in interesting_files:
        for string in string_list:
            check_contents(i, string)

    for tup in INTERESTING_INFO:
        table.add_row(tup[0], tup[1], tup[2])

    print(table)

if __name__ == "__main__":
    typer.run(main)
