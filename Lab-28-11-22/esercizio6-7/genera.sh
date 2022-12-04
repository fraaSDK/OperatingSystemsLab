#!/bin/bash

if (( $# != 1 )); then echo "I need 1 input file."; exit 1; fi

if [[ ! -e $1 ]]; then echo "File does not exist, creating file..."; touch $1; fi

if [[ -f $1 ]]; then
	../random09.sh >> $1
else
	echo "$1 is not a file."
	exit 1
fi
echo "DONE"
