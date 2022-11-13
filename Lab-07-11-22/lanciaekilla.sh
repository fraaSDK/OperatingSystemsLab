#!/bin/bash

#Putting the output into a variable
PIDs=`./lanciaeprendipid.sh`
echo -e "\nPID list: $PIDs"

for PID in $PIDs; do kill -9 $PID; echo "Killed PID: $PID"; done
