#!/bin/bash

FILES=`find /usr/include/linux/ -mindepth 2 -name "*.h" -print`

# How does this work?

# Getting the first file
for RECENT in $FILES; do
    break
done

for FILE in $FILES; do
    if [[ $RECENT -nt $FILE ]]; then
        RECENT=$RECENT
    fi
done

echo $RECENT

