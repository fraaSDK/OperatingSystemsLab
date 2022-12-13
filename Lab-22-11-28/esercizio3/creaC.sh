#!/bin/bash

read DEFINE VAR NUM < ./define.h
echo ${NUM}

# Deletes file in case it exists.
rm -f variabiliglobali.c

for ((i=1; i <= ${NUM}; i=${i}+1)); do
	echo "int var${i} = ${i};" >> variabiliglobali.c
done

echo 'int conta() {' >> variabiliglobali.c
echo -n '    int sum = 0' >> variabiliglobali.c
for ((i=1; i <= ${NUM}; i=${i}+1)); do
	echo -n "+var${i}" >> variabiliglobali.c
done
echo ';' >> variabiliglobali.c
echo '    return sum;' >> variabiliglobali.c
echo '}' >> variabiliglobali.c
