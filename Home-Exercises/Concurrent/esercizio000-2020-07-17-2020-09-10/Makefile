CFLAGS=-ansi -Wall -Wpedantic -Werror -D_REENTRANT -D_THREAD_SAFE -D_POSIX_C_SOURCE=200112L
LIBRARIES=-lpthread
FILENAME=sync

all: ${FILENAME}.exe

${FILENAME}.exe: ${FILENAME}.o
	gcc ${CFLAGS} -o ${FILENAME}.exe ${FILENAME}.o ${LIBRARIES}

${FILENAME}.o: ${FILENAME}.c
	gcc -c ${CFLAGS} ${FILENAME}.c

.PHONY: clean

clean:
	-rm -rf *.o *.exe