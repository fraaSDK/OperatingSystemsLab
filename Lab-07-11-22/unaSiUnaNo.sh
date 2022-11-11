#!/bin/bash

CONDITION=1

while read LINE; do
    if (($CONDITION == 1)); then
        echo "A:" $LINE
        CONDITION=0
    else
        CONDITION=1
    fi
done
