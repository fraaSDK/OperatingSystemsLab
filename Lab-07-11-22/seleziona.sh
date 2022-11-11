#!/bin/bash

#This method meanwhihle is very concise it makes you do this: cat filename | seleziona.sh
#grep a | wc -c

COUNT=0
while read LINE; do
    #Checking if the current line has the char 'a' in any part of it
    if [[ $LINE == *a* ]]; then
        (( COUNT=$COUNT+${#LINE}+1 ))   #If we want to count \n like wc we should add + 1 here
    fi
done < $1
echo "$COUNT"
