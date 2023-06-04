#!/bin/bash
#==============================================================================#
#
#   FILE: archiver
#                   
#   USAGE: ./archiver <directory> <archive_name>
#                   
#   DESCRIPTION: A simple program to archive a lot of files and organize them.
#
#   AUTHOR: Adam V. Link (linkavych)
#   CREATED: 2023-05-04
#   MODIFIED: --
#   VERSION: 0.1
#
#   LICENSE: BSD 3-Clause (copy in repo)
#==============================================================================#
# Test for arguments
if [[ "$#" -lt 2 ]]; then
    echo "[!] Usage: ./archiver <directory> <archive_name>"
    exit 1
fi

echo "[+] Archiving data!"

target_dir="$1"
archive_name="$2"

# Create the archive structure
archive_dir="$(pwd)/archive"
mkdir -p "$archive_dir"

# Find all the files in the dir
files=$(find "$target_dir" -type f)

# Loop through all files
for f in $files; do
    # Get the created date
    created=$(stat -c %y "$f")

    # Get the month and year to build structure
    month=$(date -d "$created" +%m)
    year=$(date -d "$created" +%Y)

    # Create the new structure in the arcvhie folder
    archive_path="$archive_dir/$year/$month"

    if [[ ! -d "$archive_path"  ]]; then
        mkdir -p "$archive_path"
    fi

    # Move the files
    mv "$f" "$archive_path"

done

# Compress the data
tar cJvf "$archive_name.tar.xz" "$archive_dir"


