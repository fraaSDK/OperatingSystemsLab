CFLAGS=-ansi -Wall -Wpedantic -Werror

all: dammi_il_precedente.exe

dammi_il_precedente.exe: dammi_il_precedente.o
	gcc -o dammi_il_precedente.exe dammi_il_precedente.o

dammi_il_precedente.o: dammi_il_precedente.c
	gcc ${CFLAGS} -c dammi_il_precedente.c

.PHONY: clean

clean:
	rm -f dammi_il_precedente.o dammi_il_precedente.exe
