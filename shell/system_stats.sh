#!/bin/bash
#==============================================================================#
#
#   FILE: system_stats.sh
#                   
#   USAGE: ./system_stats.sh
#                   
#   DESCRIPTION: Gathers quick uptime, logged in users, and current date time
#     to a logfile.
#
#   AUTHOR: Adam V. Link (linkavych)
#   CREATED: 2023-05-2023
#   MODIFIED: --
#   VERSION: 0.1
#
#   LICENSE: BSD 3-Clause (copy in repo)
#==============================================================================#
LOGFILE=status.log

echo -n "[+] Current Time: " | tee -a "$LOGFILE"

date | tee -a "$LOGFILE"

echo | tee -a "$LOGFILE"

echo "[+] Logged In Users:" | tee -a "$LOGFILE"

who | tee -a "$LOGFILE"

echo | tee -a "$LOGFILE"

echo -n "[+] System uptime: " | tee -a "$LOGFILE"

uptime | tee -a "$LOGFILE"

