SHELL=/bin/bash

CFLAGS=-ansi -Wpedantic -Wall

all: main.exe

main.exe: main.o  funzioni.o
	gcc -o main.exe main.o funzioni.o

# If Makefile changes saved date, this task will be re-executed
main.o:	main.c  funzioni.h strutture.h Makefile
	gcc -c ${CFLAGS} main.c

# If Makefile changes saved date, this task will be re-executed
funzioni.o:	funzioni.c  strutture.h Makefile
	gcc -c ${CFLAGS} funzioni.c

.PHONY: clean

clean:		
	-rm -f main.exe *.o

