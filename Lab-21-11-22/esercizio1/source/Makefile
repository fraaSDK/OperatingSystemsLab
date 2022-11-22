CFLAGS=-ansi -Wpedantic -Wall -Werror

all: main.exe

main.exe: main.o dimezza.o quadrato.o
	gcc -o main.exe main.o dimezza.o quadrato.o -lm

main.o: main.c ../include/dimezza.h ../include/quadrato.h
	gcc -c ${CFLAGS} -I../include/ main.c	#-Idir Add the directory dir to the head of the list of directories to be searched for header files

dimezza.o: dimezza.c
	gcc -c ${CFLAGS} dimezza.c

quadrato.o: quadrato.c
	gcc -c ${CFLAGS} quadrato.c

.PHONY: clean

clean:
	-rm -f main.exe main.o dimezza.o quadrato.o *~ core

