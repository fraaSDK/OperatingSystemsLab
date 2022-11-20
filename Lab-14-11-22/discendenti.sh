#!/bin/bash

INSTANCES=$1

if (( $# != 1 )); then exit 1; fi
if (( $1 < 0 )); then exit 1; fi

for (( i=0; $i < ${INSTANCES}; i=$i+1 )); do
    ./discendenti.sh $(( ${INSTANCES}-1 )) &
done

wait
echo "${INSTANCES}"
exit 0

