#!/bin/bash
#
# remove all blank lines from a file
if [[ "$#" -ne 1 ]]; then
    echo "Usage: ./removeblank [file]"
    exit 1
fi

if [[ ! -f "$1" ]]; then
    echo "[!] File does not exist!"
    exit 1
fi

sed '/^$/d' $1
