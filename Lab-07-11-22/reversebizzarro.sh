#!/bin/bash

#Declaring the variable outside the loop and printing it after the loop is done is useless:
#the loop is done inside a daughter shell
#REVERSE=""

#echo "$1"   #Printing the original string
#while read -N 1 CHAR; do
#    if (( $? == 0 )); then
#        REVERSE="${CHAR}${REVERSE}"
#    fi
#done < $1

echo $1 | while true; do
    read -n 1 CHAR
    if (( $? == 0 )); then
        REVERSE=${CHAR}${REVERSE}
    else
        echo $REVERSE
        break
    fi
done
#echo $REVERSE
