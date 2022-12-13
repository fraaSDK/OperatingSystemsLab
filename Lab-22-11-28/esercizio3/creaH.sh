#!/bin/bash

read DEFINE VAR NUM < ./define.h
echo ${NUM}

rm -f variabiliglobali.h

for ((i=1; i <= ${NUM}; i=${i}+1)); do
	echo "extern int var${i};" >> variabiliglobali.h
done
echo "extern int conta();" >> variabiliglobali.h
