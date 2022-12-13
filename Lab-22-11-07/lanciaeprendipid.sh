#!/bin/bash

for ((I=0; $I < 10; I=$I+1)); do
    #Launching in bg 10 intances of the script, redirecting to stderr
    ./puntini.sh 30 1>&2 &
    echo -n "$! "
done
