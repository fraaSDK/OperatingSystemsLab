CFLAGS=-ansi -Wall -Wpedantic -Werror

all: main.exe

main.exe: main.o
	gcc ${CFLAGS} -o main.exe main.o

main.o: main.c macro1.h
	gcc -c ${CFLAGS} main.c

.PHONY: clean

clean:
	rm -f main.exe main.o macro1.o *~ core 
