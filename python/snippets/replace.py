#!/usr/bin/env python3
"""
FILE: replace.py

USAGE: ./replace.py <path>

DESCRIPTION: Replace any files with a space in their name with an '_'; non-recursive

AUTHOR:      Adam V. Link (linkavych)
CREATED: 2023-05-04
MODIFIED: --
VERSION: 0.1

LICENSE: BSD 3-Clause (Provided in repository)
"""
import os
import sys

path = sys.argv[1]

for path, folders, files in os.walk(path):
    for f in files:
        os.rename(os.path.join(path, f), os.path.join(path, f.replace(' ', '_')))
    for i in range(len(folders)):
        new_name = folders[i].replace(' ', '_')
        os.rename(os.path.join(path, folders[i]), os.path.join(path, new_name))
        folders[i] = new_name
