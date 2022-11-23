#!/bin/bash
#
# Converting a for loop script to while loops
# Listing the planets.
#
#for planet in Mercury Venus Earth Mars Jupiter Saturn Uranus Neptune Pluto
#do
#    echo $planet # Each planet on a separate line.
#done
#
#echo; echo
#
#for planet in "Mercury Venus Earth Mars Jupiter Saturn Uranus Neptune Pluto"
## All planets on same line.
## Entire 'list' enclosed in quotes creates a single variable.
## Why? Whitespace incorporated into the variable.
#do
#    echo $planet
#done
#
#echo; echo "Whoops! Pluto is no longer a planet!"
#
#exit 0

PLANETS=("Mercury" "Venus" "Earth" "Mars" "Jupiter" "Saturn" "Uranus" "Neptune" "Pluto")

i=0
len=${#PLANETS[@]}
while [[ "$i" -lt "$len" ]]
do
    echo ${PLANETS[$i]}
    let i++
done

j=0
lenn=${#PLANETS[@]}
while [[ "$j" -lt "$lenn" ]]
do
    printf "%s " "${PLANETS[$j]}"
    let j++
done
