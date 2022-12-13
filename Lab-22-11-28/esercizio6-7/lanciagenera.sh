#!/bin/bash

if [[ -e out.txt ]]; then echo "Removing out.txt..."; rm -f out.txt; fi

for ((i=0; i<10; i++)); do
	./genera.sh out.txt
done

SUM=0
while read NUM; do
	(( SUM=${SUM} + NUM ))
done < out.txt
echo "Sum is: ${SUM}"
