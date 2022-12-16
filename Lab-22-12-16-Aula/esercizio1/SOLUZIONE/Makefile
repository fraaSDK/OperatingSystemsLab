# Makefile per fachirifurbi.c
# a causa della presenza di pthread
# occorre compilare col flag -D_REENTRANT
# oppure con  -D_THREAD_SAFE 

CFLAGS=-ansi -Wpedantic -Wall -D_REENTRANT  -D_THREAD_SAFE -D_POSIX_C_SOURCE=200112L
LIBRARIES=-lpthread

all: 	fachirifurbi.exe 

fachirifurbi.exe: fachirifurbi.o
	gcc -o fachirifurbi.exe fachirifurbi.o ${LIBRARIES}

fachirifurbi.o: fachirifurbi.c
	gcc ${CFLAGS} -c fachirifurbi.c


.PHONY:	clean

clean:
	rm -f fachirifurbi.o fachirifurbi.exe 

