#!/bin/sh
#==============================================================================#
#
#   FILE: backup_enc.sh
#                   
#   USAGE: ./backup_enc.sh {path}
#                   
#   DESCRIPTION: Backup a file, or directory. Creates a .tgz compressed archive,
#     then encrypts the archive with a provided password. Send to a remote host
#     with `rsync`.
#
#   AUTHOR: Adam V. Link (linkavych)
#   CREATED: 2023-04-18
#   MODIFIED: --
#   VERSION: 1.0
#
#   LICENSE: BSD 3-Clause (copy in repo)
#==============================================================================#

DIRPATH="$1"
COMPRESSED="backup.tgz"
ENCRYPTED="backup.tgz.enc"

# Compress the directory
/usr/bin/tar czf "$COMPRESSED" "$DIRPATH"

# Encrypt using openssl
echo '[+] Encrypting archive. Please submit a password'
/usr/bin/openssl enc -aes-256-cbc -in "$COMPRESSED" -out "$ENCRYPTED" -pbkdf2

# Clean up
/usr/bin/rm -f "$COMPRESSED"

echo "[+] Compression and encryption completed. Encrypted file: $ENCRYPTED"
