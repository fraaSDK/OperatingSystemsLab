#!/bin/bash

while true; do
    read first second third fourth

    #EOF not reached.
    if (($? == 0)); then
        echo "$fourth $third"
    else
        break
    fi
done
