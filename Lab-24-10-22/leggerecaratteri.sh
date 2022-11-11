#!/bin/bash

exec {FD}</usr/include/stdio.h

TOT=0

#-N reads only one word each time, -r ignores the backslashes such as \n
while read -u ${FD} -N 1 -r A ; do
    if (($? == 0)); then
        ((TOT=$TOT+1))
    fi
done
exec {FD}>&-

echo $TOT
