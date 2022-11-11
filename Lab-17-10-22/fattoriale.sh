#!/bin/bash

INDEX=1
MUL=1
while (( $INDEX <= $1 )) ; do
    (( MUL=$MUL * $INDEX ))
    (( INDEX=$INDEX + 1 ))
done

echo $MUL
