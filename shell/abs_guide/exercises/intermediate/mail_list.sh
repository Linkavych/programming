#!/bin/bash
#
# A script to manage a mailing list with mail
# Sends an email monthly (cron), the body is from a specified text file
# The email list is also from a text file
# 
# author: Adam V. Link (@linkavych)
# date: 2022-11-25
#
LIST=/tmp/mailer.list
MESSAGE=/tmp/message.txt
NEWSLOG=/tmp/mailer.log
DATE=$(date "+%Y.%m.%d")

for email in $(cat "$LIST")
do
    mail -s "Monthly Newsletter - [$DATE]" "$email" < "$MESSAGE"
    echo "[+] Message sent to $email - [$DATE]" > "$NEWSLOG"
done


