#!/bin/bash

# First exit status = 1, (second (0) || third (1)) = 1, third = 1 -> exit status 0
# Pay attention to > and < with strings. Its lexicographycally ordered.
( sleep 2; ls -d /usr/include/ ) && { [[ ( !( "false" > "true" )) ||
    ( 3 -le 5 ) ]] ; } && if [[ $? < "01" ]] ; then exit 0; else exit 1 ; fi ;
exit $?

