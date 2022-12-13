#!/bin/bash

OUT=""

if (($# != 1)); then exit 1; fi

while read FIRST SECOND NEXT; do
    #Checks if the string is not zero
    if [[ -n $SECOND ]]; then
        OUT=${OUT}${SECOND}   #String concat
    fi
done < $1   #read would wait for user input, however we redirect it from the file ($1)
echo $OUT
