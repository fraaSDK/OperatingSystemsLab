#!/bin/bash

# Hint cat <file> | grep -oc <match>
# -o prints the only-matching part of the string
# -c counts the matched elements.

PREVIOUS_VALUE=0

while read NAME SURNAME VALUE OTHER; do
	if [[ ${VALUE} == ${PREVIOUS_VALUE} ]]; then
		continue
	fi
	PREVIOUS_VALUE=${VALUE}

	echo -n "${VALUE} "
	cat ./multe.txt | grep -oc ${VALUE}
done < ./multe.txt
