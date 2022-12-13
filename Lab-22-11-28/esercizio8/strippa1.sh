#!/bin/bash

for fpath in `find /usr/include/ -mindepth 1 -type f`; do
	# Removing the longest prefix to keep the name of the subdir.
	dirname=${fpath##*/}
	if (( ${#dirname} >= 7 )); then
		# Parameter expansion: getting char at pos 6 (offset) using length 1.
		echo "${dirname:6:1}" >> 7.txt
		if (( ${#dirname} >= 8 )); then
			echo "${dirname:7:1}" >> 8.txt
		fi
	fi
done
