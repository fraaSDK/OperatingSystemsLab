#!/bin/bash

FILE_NAME=`ls`

for name1 in $FILE_NAME ; do
    for name2 in $FILE_NAME ; do
        for name3 in $FILE_NAME ; do
	    echo $name1 $name2 $name3
	done
    done
done
