CFLAGS=-ansi -Wall -Wpedantic -Werror

all: libB.so

libB.so: B.o
	gcc -shared -fPIC -o libB.so B.o -Wl,-soname,libB.so

B.o: B.c
	gcc -c -fPIC ${CFLAGS} B.c

.PHONY: clean

clean:
	-rm -f *.o *.exe *.so
