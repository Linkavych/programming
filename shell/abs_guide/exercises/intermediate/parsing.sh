#!/bin/bash
#
# Parse /etc/passwd and output its contents in an easy-to-read tabular format
#
#
FILE=/etc/passwd

printf '%-18s   %-2s    %-4s   %-24s   %-10s\n' "USERNAME" "UID" "GID" "HOME" "SHELL" 
cat $FILE | cut -d ':' -f 1,3,4,6,7 | tr ':' ' ' | column -t  
