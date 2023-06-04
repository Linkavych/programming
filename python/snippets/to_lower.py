#!/usr/bin/env python3
"""
FILE:        

USAGE:       

DESCRIPTION: 

AUTHOR:      Adam V. Link (linkavych)
CREATED:     
MODIFIED:    
VERSION:     

LICENSE: BSD 3-Clause (Provided in repository)
"""
import sys
from pathlib import Path

for path in Path(sys.argv[1]).rglob('*'):
    path.rename(f"{path.parent}{path.stem.lower()}{path.suffix}")
