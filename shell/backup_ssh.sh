#!/bin/sh
#
# Script to backup files from a provided path
# Compress using XZ compression
# Send the compress file to a remote server for storage
#
# Check for path and remote host
if [ $# -lt 3 ]; then
    echo "[!] Error: No path, remote host, or ssh key provided."
    echo "[!] Usage: $0 path remote_host ssh_key"
    exit 1
fi

# Set the target path and remote host vars
path=$1
remote=$2
key=$3

# Create a backup directory
if [ ! -d "backup" ]; then
    mkdir backup
fi

# Find all files in our path and copy them to the backup directory
find $path -type f -exec cp {} backup/ \;

# Compress the backup directory using tar and XZ compression
tar -cvJf backup.tar.xz backup

# Clean up
rm -rf backup/

# Copy our backup files to a remote server
scp -i $key backup.tar.xz $remote:~/

# Cleanup again
rm -f backup.tar.xz

echo "[+] Backup process complete."
