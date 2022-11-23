#!/bin/bash
#
# Capture strings from running process memory
# Idea/structure/code from Hal Pomeranz
# Cleaned into a script by Adam Link (@linkavych)
# Date: 2022-11-22
#
PID=$1

if [[ "$EUID" -ne 0 ]]; then
    echo "[!] Run script as root!"
    exit 1
fi

if [[ "$#" -lt 1 ]]; then
    echo "Usage: ./memstrings.sh PID"
    exit 1
fi

cat /proc/$PID/maps | tr - ' ' | while read start end junk; do

start=$((16#$start / 4096)); dd if=/proc/$PID/mem bs=4096 skip=$start count=$((16#$end / 4096 - $start))

done 2>/dev/null | strings -a >strings_$PID.txt
