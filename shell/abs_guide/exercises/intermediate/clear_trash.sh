#!/bin/bash
#
# Check the ~/TRASH file for any files and delete them if older than 48 hours
#
TRASHDIR=/home/$USERNAME/TRASH
DELETEME=*.gz
DATE=$(date "+%Y.%m.%d")
DELETEDLOG=/home/$USERNAME/TRASH/deleted.log

if [[ -d "$TRASHDIR" ]]; then
    # Find all files older than 48 hours and delete; capturing file info to log
    find "$TRASHDIR" -name "$DELETEME" -type f -mtime +2 -delete -printf \
        "[$DATE] - %s\n" {} \; >> "$DELETEDLOG"    
else
    echo "[!] No trash directory found. Exiting."
    exit 1
fi

exit 0
