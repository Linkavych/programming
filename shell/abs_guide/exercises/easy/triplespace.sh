#!/bin/bash
#
# A script to triple space a target file.
if [[ "$#" -ne 1 ]]; then
    echo "Usage: ./triplespace [file]"
    exit 1
fi

if [[ ! -f $1 ]]; then
    echo "[!] File does not exist!"
    exit 1
fi

while read -r line;
do
    printf "%s\n\n\n" "$line"
done < $1
