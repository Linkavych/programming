#/bin/bash
#
# Generate five random numbers between 1 and 50
# Echo to stdout or save to file
help() {
    echo "Usage: ./lottery [-h|-o]"
    echo "options:"
    echo "h     Print help."
    echo "w     Write lottery numbers to lottery.ticket"
    echo
}

write() {
    for num in {1..5}
    do
        echo -n "$((1 + $RANDOM %50)) " >> lottery.ticket
    done
}

out(){
    echo -n "Lottery numbers: "
    for num in {1..5}
    do
        echo -n "$((1 + $RANDOM % 50)) "
    done
    echo
}

# If no arguments, write to stdout
if [[ $# -lt 1 ]]; then
    out
fi

while getopts ":h:w" option; do
    case $option in
        h)  help    exit;;
        w)  write   exit;;
        *)  out     exit;;
    esac
done
