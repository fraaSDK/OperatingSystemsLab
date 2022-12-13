SHELL=/bin/bash

all: out.txt

out.txt: file1.txt file2.txt
	[[ -e out.txt ]]; [[ out.txt -nt file1.txt || out.txt -nt file2.txt ]]; ./alterna.sh in1.txt in2.txt

file1.txt: in1.txt
	cat in1.txt

file2.txt: in2.txt
	cat in2.txt

.PHONY: clean

clean:
	-rm -f out.txt
