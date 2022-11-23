#!/bin/bash
#
# Check for and delete user accounts that have not been accessed within 90 days
#
DAYS=90
$LOGFILE=/var/log/deleted_users.log
$DATE=$(date "+%Y.%m.%d")

if [[ "$EUID" -ne 0 ]]; then
    exit 1
fi

echo "[STARTED: $DATE]" >> $LOGFILE

# Explaing this command:
# lastlog -b 90 prints any user who has logged in within 90 days
# tail -n+2 removes the header from the output of lastlog
# grep -vi never will remove any system accounts that should never login to the system
# awk will print the first column, which is the user name
# tee -a (appends) shuttles our usernames off to a log file
# xargs will take each of our users and feed them into the userdel command
# this will force delete the user from the system, and remove their files
lastlog -b $DAYS | tail -n+2 | grep -vi never | awk '{ print $1 }' | tee -a /var/log/inactives.log | xargs -I{} userdel -fr {}

echo "[COMPLETED: $DATE]" >> $LOGFILE

exit 0
