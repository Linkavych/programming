#!/usr/bin/env python3
"""
FILE: change_perms.py

USAGE: ./change_perms.py <path> <file extension>

DESCRIPTION: A program to change the permissions of files within a nested directory
structure based on file extension. Recursive by default.

AUTHOR:      Adam V. Link (linkavych)
CREATED: 2023-05-11
MODIFIED: --
VERSION: 0.1

LICENSE: BSD 3-Clause (Provided in repository)
"""
import sys
from pathlib import Path

p = sys.argv[1]
ext = sys.argv[2]

paths = Path(p).rglob(f'*.{ext}')

for i in paths:
    i.chmod(0o664)
