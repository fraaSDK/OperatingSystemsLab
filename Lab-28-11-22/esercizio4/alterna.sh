#!/bin/bash

if (( $# != 2 )); then exit 1; fi
if [[ -e out.txt ]]; then rm -f out.txt; fi

exec {FD1}< $1
exec {FD2}< $2
currentFD=${FD1}

while read -u ${currentFD} LINE; EXTSTATUS=$?; [[ ${LINE} != "" || ${EXTSTATUS} -eq 0 ]]; do
	echo "${LINE}" >> out.txt

	if (( currentFD==${FD1} )); then currentFD=${FD2};
	else currentFD=${FD1}
	fi
done

# Closing the shortest file's FD.
if (( currentFD==${FD1} )); then
	exec {FD1}>&-
	currentFD=${FD2}
else
	exec {FD2}>&-
	currentFD=${FD1}
fi

# Continuing
while read -u ${currentFD} LINE; EXTSTATUS=$?; [[ ${LINE} != "" || ${EXTSTATUS} -eq 0 ]]; do
	echo "${LINE}" >> out.txt
done

exec {currentFD}>&-
