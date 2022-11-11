#!/bin/bash

#Opening the file (read only)
exec {FD}</usr/include/stdio.h

while read -u ${FD} A B C D; do
    if (( $? == 0 )); then
        echo $C
    fi
done

#Closing the file
exec {FD}>&-
