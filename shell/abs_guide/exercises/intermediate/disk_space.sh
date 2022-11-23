#!/bin/bash
#
# List, one at a time, all files larger than 100K in the /home/username directory tree. Give the user
# the option to delete or compress the file, then proceed to show the next one. Write to a logfile the
# names of all deleted files and the deletion times
#
LOGFILE=deleted.log
DIRPATH=/home/$USERNAME
FILELIST=files.tmp

write_to_log(){
    # Write any deleted files to a log file
    TIME=$(date "+%Y-%m-%d_%H:%M")
    FILENAME=$1

    printf "[$TIME] - $FILENAME\n" >> $LOGFILE
}

delete_file(){
    # Write to the log file and delete
    FILENAME=$1

    write_to_log $FILENAME
    
    rm -f $FILENAME

    echo "[+] File deleted..."
}

compress_file() {
    # Compress file with XZ
    FILENAME=$1

    echo "[+] Compressing $FILENAME..."

    xz $FILENAME

    echo "[+] File compressed..."
}

do_sigint() {
    echo "[!] Terminating (Ctrl-c) program..."
    
    rm -f $FILELIST
    
    exit 0
}

# MAIN LOGIC BEGINS
# find all files in home greater than 100kb and save to temp file
find $DIRPATH -size -100k -type f > $FILELIST

trap do_sigint SIGINT

for line in $(cat $FILELIST)
do
    echo "[D]elete, [c]ompress, or [n]othing: $line"
    read OPTION

    case $OPTION in
        d|D)    delete_file $line     ;;
        c|C)    compress_file $line   ;;
        *)      continue        ;;
    esac

done


