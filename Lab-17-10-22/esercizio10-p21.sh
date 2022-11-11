#!/bin/bash

#Iterating over all directory's files
for file in `ls` ; do
    echo file is $file
    ls -ld $file            #Extended list, only dir names
done
