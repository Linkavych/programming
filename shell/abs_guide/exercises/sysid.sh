#!/bin/bash
#
# Generate a unique 6 digit id for the computer
# Do not use `hostid`
HASH=$(md5sum /etc/passwd)
ID=${HASH:0:6}

echo "System Identifier: '$ID'"

