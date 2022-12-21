CFLAGS=-ansi -Wall -Wpedantic -D_REENTRANT -D_THREAD_SAFE -D_POSIX_C_SOURCE=200112L
LIBRARIES=-lpthread
FILENAME=piattello

all: ${FILENAME}.exe

${FILENAME}.exe: ${FILENAME}.o DBGpthread.o
	gcc ${CFLAGS} -o ${FILENAME}.exe ${FILENAME}.o DBGpthread.o ${LIBRARIES}

${FILENAME}.o: ${FILENAME}.c DBGpthread.h printerror.h
	gcc -c ${CFLAGS} ${FILENAME}.c

DBGpthread.o: DBGpthread.c printerror.h
	gcc -c ${CFLAGS} DBGpthread.c

.PHONY: clean

clean:
	-rm -rf *.o *.exe
