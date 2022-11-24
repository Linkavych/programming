#!/bin/bash
#
# Implement, as a script, a "safe" delete command, sdel.sh. Filenames passed as command-line
# arguments to this script are not deleted, but instead gzipped if not already compressed (use file to
# check), then moved to a ~/TRASH directory. Upon invocation, the script checks the ~/TRASH
# directory for files older than 48 hours and permanently deletes them. (An better alternative might be
# to have a second script handle this, periodically invoked by the cron daemon.)
# Extra credit: Write the script so it can handle files and directories recursively. This would give it the
# capability of "safely deleting" entire directory structures.
#
TRASHDIR=/home/$USERNAME/TRASH

delete_file() {
    # Safely delete a file
    file=$1

    gzip "$file"

    mv $file.gz "$TRASHDIR"
}

delete_dir() {
    # Safely delete a directory
    directory=$1

    tar -zcf $directory.tar.gz "$directory"

    mv $directory.tar.gz "$TRASHDIR"
}

# Check fotr trash directory
if [[ ! -d "$TRASHDIR" ]]; then
    mkdir $TRASHDIR
fi

for file in "$@"; do
    if [[ -f "$file" ]]; then
        delete_file "$file"
        echo "[+] Sent $file to the trash..."
    elif [[ -d "$file" ]]; then
        delete_dir "$file"
        echo "[+] Sent the contents of $file to the trash..."
    else
        echo "[!] Not a file or directory!"
        exit 1
    fi
done

exit 0
