#!/bin/bash

DIRNUM=0
LungNomiDirectory=0
NONDIR=0

for name in `ls`; do
    if [[ -d $name ]]; then
        ((DIRNUM=$DIRNUM+1))
        ((LungNomiDirectory=$LungNomiDirectory+${#name}))
    else
        ((NONDIR=$NONDIR+1))
    fi
done

echo "Dir num: $DIRNUM"
echo "Length: $LungNomiDirectory"
echo "NonDir num: $NONDIR"
