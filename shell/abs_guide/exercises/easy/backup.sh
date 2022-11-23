#!/bin/bash
#
# Archive as a tarball (*.tar.gz) all files in your home directory tree
# that have been modified in the last 24 hours.
#
DIRPATH=$1
TARFILE=backup.tar
TARBALL=$TARFILE.gz
FILES=files.tmp

if [[ $# -ne 1 ]]; then
    echo "Usage: ./backup.sh [path]"
    echo "Backup all files from the last 24 hours."
    exit 1
fi

echo "[+] Finding all files modified in the last 24 hours..."

find $DIRPATH -type f -mtime -1 -execdir tar -rf $TARFILE --exclude=./$TARFILE '{}' \; 

echo "[+] Compressing files..."
 
gzip -c $TARFILE > $TARBALL

echo "[+] Tarball created: $TARBALL..."

echo "[+] Cleaning up..."

rm -rf $TARFILE

echo "[+] Complete!"

exit 0

