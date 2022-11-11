#!/bin/bash

exec {FD}<./miofileNoNL.txt

#Checks if the file has not ended or the last line is not empty.
while read -u ${FD} LINE; [[ $? == 0 || $LINE != "" ]]; do
    echo $LINE
done

exec {FD}>&-
