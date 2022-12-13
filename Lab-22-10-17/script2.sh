#!/bin/bash

CURR=$#

while (( $CURR > "0" )) ; do
    echo "arg ${CURR}: ${!CURR}"
    (( CURR=$CURR - 1 ))
done
