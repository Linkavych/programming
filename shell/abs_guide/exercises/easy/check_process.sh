#!/bin/bash
#
# Given a PID as an argument, the script will check - at a specified interval
# whether the process is running.
PID=$1
TIME=$2

echo "[+] Checking for the process: $PID..."

sleep 1

check() {
    if ps -p $PID > /dev/null; then
        echo "[+] $PID is active!"
    else
        echo "[!] $PID is no longer active!"
        exit 1
    fi
}

while :
do
    echo "[+] Check for the process ID: $PID..."

    check

    sleep $TIME

done
