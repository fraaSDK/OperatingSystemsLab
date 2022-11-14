#!/bin/bash

while read LINE; do
    #Using "" to stop expansions such as *
    #%% removes the longest suffix that matches the regex, * will be expanded in a space
    echo "${LINE%%*}" 1>&2
    echo "evviva"
done

