#!/bin/bash

TIME=$1

while (( TIME != 0 )); do
    echo -n ".$$"   #-n prints without newline, $$ is the bash PID (better than $BASHPID - not portable)
    ((TIME=TIME-1))
    sleep 1
done
