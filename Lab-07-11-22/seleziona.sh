#!/bin/bash

#grep A | wc -c

COUNT=0
while read LINE; do
    #Checking grep exit status FIX
    grep a
    if (($? == 0)); then
        ((COUNT=$COUNT+${#LINE}))
    fi
done < $1
