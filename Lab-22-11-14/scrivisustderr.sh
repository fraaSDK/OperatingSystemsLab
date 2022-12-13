#!/bin/bash

while read LINE; do
    # Using "" to stop expansions such as *
    # %% removes the longest suffix that matches the regex,
    # we want to get the first word of each line, therefore
    # we look for a whitespace, followed by any character (*)
    echo "${LINE%% *}" 1>&2
    echo "evviva"
done

