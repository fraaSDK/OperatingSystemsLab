CFLAGS=-ansi -Wall -Wpedantic -Werror

all: libA.so

# renenyffenegger.ch/notes/development/languages/C-C-plus-plus/GCC/options/shared/index
# renenyffenegger.ch/notes/development/languages/C-C-plus-plus/GCC/options/f/pic/index
# -lm used to link math.h
libA.so: A.o
	gcc -shared -fPIC -o libA.so A.o -lm -Wl,-soname,libA.so

A.o: A.c
	gcc -c -fPIC ${CFLAGS} A.c

.PHONY: clean

clean:
	-rm -f *.o *.so *.exe
