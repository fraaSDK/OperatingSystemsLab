CFLAGS=-ansi -Wall -Wpedantic -Werror -D_REENTRANT -D_THREAD_SAFE -D_POSIX_C_SOURCE=200112L
LIBRARIES=-lpthread

all: form_retrieval.exe

form_retrieval.exe: form_retrieval.o
	gcc ${CFLAGS} -o form_retrieval.exe form_retrieval.o ${LIBRARIES}

form_retrieval.o: form_retrieval.c
	gcc -c ${CFLAGS} form_retrieval.c

.PHONY: clean

clean:
	-rm -rf *.o *.exe
