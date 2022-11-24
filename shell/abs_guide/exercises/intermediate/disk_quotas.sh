#!/bin/bash
#
# Write a script for a multi-user system that checks users' disk usage.
# If a user surpasses a preset limit (500MB) in their /home/$USERNAME
# directory, then the script automaticaly sends a warning email.
#
# Use du and mail commands. As an option, allow setting and enforcing quotas
#
USERTMP=/tmp/user.tmp
LOGFILE=/var/log/diskwarn.log

check_disk() {
    # 500 MB
    FULL=500
    HOMEDIR=/home

    # get amount of disk usage at depth 1 from the home directory
    du -d 1 -m $HOMEDIR > $USERTMP
    
    # remove the home directory from the output
    sed -i '/\/home$/d' $USERTMP
    # change tabs to newlines
    sed -i 's/\t/\n/g' $USERTMP

    diskarr=()
    while IFS= read -r line; do
        diskarr+=("$line")
    done <$USERTMP

    i=0
    until (($i >= "${#diskarr[@]}"));
    do
        echo $i
        if  (("${diskarr[$i]}" > "$FULL")); then
            send_mail "${diskarr[$i+1]}"
            write_to_log "${diskarr[$i+1]}" "${diskarr[$i]}"
            ((i=i+2))
        else
            ((i=i+2))
            continue
        fi
    done
}

send_mail() {
    USER=$1
    SUBJECT="WARNING: Disk Limit (500MB) Exceeded"
    MESSAGE="Your account will be locked unless you reduce your disk usage within 5 working days. Contact your system administrator with any questions."

    mail -s $SUBJECT $USER@nowhere <<< $MESSAGE
}

write_to_log() {
    # Write user info to logfile
    USER=$1
    DISK=$2
    DATE=$(date "+%Y.%m.%d-%H:%M")

    echo "User warned: $USER, Disk: $DISK, Date: $DATE" >> $LOGFILE
}

# Main functionality starts here
check_disk
