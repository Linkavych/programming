#!/bin/bash
#
# Write a script to automatically monitor and log activities of a single user
# when signed on. Log file will save entries for the previous week, and delete entries 
# more than seven days old.
#
DATE=$(date "+%Y.%m.%d")
LOGDIR=/var/log/monitor
LOGFILE=/var/log/monitor/$DATE.log
PERS=linkavych

copy_files() 
{
    echo "[$DATE]"
    echo "[+] USER LOGIN INFO ================================================="
    echo "User session completed: $(lastlog -u $PERS | tail -n1 | awk '{ print $3,$4,$5,$6 }')"
    echo "====================================================================="
    echo
    echo "[+] USER HISTORY INFO ==============================================="
    $(cat /home/$PERS/*history)
    echo "====================================================================="
}

check_user()
{
    lastlogin=$(last $PERS | grep -i 'down' | awk '{date_var=$5 FS $6; print date_var}')
    copied=0
    while : 
    do
        if [[ "$(last $PERS | grep -i 'still logged in')" ]]; then
            copied=0
            sleep 60
            continue
        elif [[ "$copied" -eq 1 ]]; then
            sleep 60
            continue
        else
            copied=1
            copy_files
        fi
    done
}

if [[ "$EUID" -ne 0 ]]; then
    echo "[!] Must be run as root!"
    exit 1;
fi

if [[ -d "$LOGDIR" ]]; then
    check_user
else
    mkdir -p /var/log/monitor
fi


