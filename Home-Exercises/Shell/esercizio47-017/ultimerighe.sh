#!/bin/bash

if (( $# != 1 )); then echo "Pass 1 argument." >&2; exit 1; fi

if [[ ! -f $1 ]]; then echo "Arg1 not a file." >&2; exit 2; fi

if [[ -e $1 ]]; then
	(sleep 2; tail -n 3 $1 >> ./OUTPUT.txt) &
fi

exit 0
