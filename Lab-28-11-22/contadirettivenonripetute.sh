#!/bin/bash

for file in `find /usr/include/ -type f -name "*.h"`; do
	grep '#' ${file}
done | sort | uniq | wc -l	# sort before uniq because uniq filters adjacent matching lines.
