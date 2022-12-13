CFLAGS=-ansi -Wall -Wpedantic -Werror

all: main.exe

main.exe: main.o variabiliglobali.o
	gcc -o main.exe main.o variabiliglobali.o

main.o: main.c variabiliglobali.h define.h
	gcc -c ${CFLAGS} main.c

variabiliglobali.o: variabiliglobali.c
	gcc -c ${CFLAGS} variabiliglobali.c

variabiliglobali.c: define.h
	./creaC.sh

variabiliglobali.h: define.h
	./creaH.sh

.PHONY: clean

clean:
	-rm -rf *.o *.exe variabiliglobali.*
