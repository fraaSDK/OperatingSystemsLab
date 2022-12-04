#!/bin/bash

for file in `find /usr/include/ -type f -name "*.h"`; do
	grep '#' ${file}
done

#TODO
