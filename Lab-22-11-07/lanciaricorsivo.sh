#!/bin/bash

PROC=$1

if (( $PROC > 0 )); then
    ./lanciaricorsivo.sh $(( $PROC-1 )) &
    echo $!
    wait $!
fi
