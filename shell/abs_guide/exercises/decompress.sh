#!/bin/bash
#
# Given a list of filenames as input, this script queries each target file (parsing the output of the file
# command) for the type of compression used on it. Then the script automatically invokes the
# appropriate decompression command (gunzip, bunzip2, unzip, uncompress, or whatever). If a target
# file is not compressed, the script emits a warning message, but takes no other action on that particular
# file.
#
# This does not include every type of compressed file, but it hits most for now
if [[ $# -lt 1 ]]; then
    echo "Usage: ./decompress [file1 file2 file3 ...]"
    exit 1
fi

for FILE in $*; do
    if [[ ! -f $FILE ]]; then
        echo "[!] File does not exist!"
        continue
    fi

    TYPE=$(file $FILE | awk '{ print $2 }')
    case $TYPE in
        XZ)         tar xf $FILE    ;;
        gzip)       tar xzf $FILE   ;;
        bzip2)      tar xjf $FILE   ;;
        POSIX)      tar xf $FILE    ;;
        Zip)        unzip $FILE     ;;
        7-zip)      7z x $FILE      ;;
        *)          echo "'$FILE' cannot be extracted"  ;;
    esac
done

