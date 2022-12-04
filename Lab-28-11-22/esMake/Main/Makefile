INSTALL_DIR_A=../LibA
INSTALL_DIR_B=../LibB
CFLAGS=-ansi -Wall -Wpedantic -Werror

all: main.exe

# -lname -- library name
# -Lpath -- library dir path.
# -Wl,-rpath,runtimeLibDir -- library dir at runtime
main.exe: main.o ${INSTALL_DIR_A}/libA.so ${INSTALL_DIR_B}/libB.so
	gcc -o main.exe main.o \
	-lA -L${INSTALL_DIR_A} -Wl,-rpath,`pwd`/${INSTALL_DIR_A} \
	-lB -L${INSTALL_DIR_B} -Wl,-rpath,`pwd`/${INSTALL_DIR_B}

# -I to specify headers' directory path.
main.o: main.c ${INSTALL_DIR_A}/A.h ${INSTALL_DIR_B}/B.h
	gcc -c ${CFLAGS} -I${INSTALL_DIR_A} -I${INSTALL_DIR_B} main.c

.PHONY: clean

clean:
	-rm -f *.o *.exe
