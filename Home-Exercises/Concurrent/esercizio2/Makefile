CFLAGS=-ansi -Wall -Wpedantic -Werror -D_REENTRANT -D_THREAD_SAFE -D_POSIX_C_SOURCE=201112L
LIBRARIES=-lpthread

all: bridge.exe

bridge.exe: bridge.o
	gcc ${CFLAGS} -o bridge.exe bridge.o ${LIBRARIES}

bridge.o: bridge.c
	gcc -c ${CFLAGS} bridge.c

.PHONY: clean

clean:
	-rm -rf *.o *.exe
