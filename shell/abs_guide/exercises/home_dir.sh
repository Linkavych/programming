#!/bin/bash
#
# Home Directory Listing
# Perform a recursive directory listing on the user's home directory and save the information to a file.
# Compress the file, have the script prompt the user to insert a USB flash drive, then press ENTER.
# Finally, save the file to the flash drive after making certain the flash drive has properly mounted by
# parsing the output of df. Note that the flash drive must be unmounted before it is removed.
#
HOMEDIR=/home/$USERNAME
FILENAME=file_list.log
XZFILE=$FILENAME.txz

ls -laR $HOMEDIR > $FILENAME

bsdtar -cJf $XZFILE $FILENAME

rm $FILENAME

chown $USERNAME:$USERNAME $XZFILE

# Have the user insert a USB and test for it
read -p "Insert a USB drive...[Enter once inserted]"


df -hPT | while read first second third fourth fifth sixth seventh
do
    if [[ $seventh =~ ^/media+ ]]; then
        cp $XZFILE $seventh
    fi
done

rm $XZFILE

exit 0





