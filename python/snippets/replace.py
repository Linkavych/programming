#!/usr/bin/env python3
"""
FILE: replace.py

USAGE: ./replace.py

DESCRIPTION: Replace any files with a space in their name with an '_'; non-recursive

AUTHOR:      Adam V. Link (linkavych)
CREATED: 2023-05-04
MODIFIED: --
VERSION: 0.1

LICENSE: BSD 3-Clause (Provided in repository)
"""
import os

# Get the directory
current_dir = os.getcwd()

# Get the file listing
files = os.listdir(current_dir)

# Loop
for file in files:
    if " " in file:
        new_name = file.replace(" ", "_")

        #rename
        os.rename(file, new_name)

print("[+] Completed renaming!")
