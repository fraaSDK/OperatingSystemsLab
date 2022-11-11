#!/bin/bash

SUM=0

for args in $@; do
    (( SUM=$SUM + ($args * $args) ));
done

for (( NUM=1; $NUM<=$#; NUM=$NUM+1 )); do
    (( SUM=$SUM-$NUM ))
done

echo $SUM
