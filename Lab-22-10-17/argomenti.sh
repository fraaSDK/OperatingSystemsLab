#!/bin/bash

STR=""
INDEX=0

#Puts the args with even index in the string
for (( INDEX=2; INDEX <= $#; INDEX=$INDEX+2 )); do
    STR="${STR} ${!INDEX}"
done

#Puts the args with odd index in the string
for (( INDEX=1; INDEX <= $#; INDEX=$INDEX+2 )); do
    STR="${STR} ${!INDEX}"
done

echo $STR
