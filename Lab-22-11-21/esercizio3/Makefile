CFLAGS=-ansi -Wall -Wpedantic -Werror -D'ALLOCAVETTORE(PTR)=do { PTR=(int32_t*)malloc(10*sizeof(int32_t)); if(PTR != NULL) { int j; for(j=0; j<10; j++) { PTR[j]=-1000 + j; }}} while (0)'
ALLOC=-D'ALLOCAVETTORE(PTR)=do { PTR=(int32_t*)malloc(10*sizeof(int32_t)); if(PTR != NULL) { int j; for(j=0; j<10; j++) { PTR[j]=-1000 + j; }}} while (0)'

all: main.exe

main.exe: main.o
	gcc ${CFLAGS} -o main.exe main.o

main.o: main.c
	gcc -c ${CFLAGS} ${ALLOC} main.c

.PHONY: clean

clean:
	rm -f main.exe main.o *~ core 
