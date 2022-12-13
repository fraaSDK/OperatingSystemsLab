LIB=-lcmph
RUNTIME_LIBPATH=/home/fra/LIB/lib
LINKTIME_LIBPATH=/home/fra/LIB/lib
INCLUDE_PATH=/home/fra/LIB/include

all: file_adapter_ex2.exe

file_adapter_ex2.exe: file_adapter_ex2.o
	gcc -o file_adapter_ex2.exe -Wl,-rpath,${RUNTIME_LIBPATH} -L${LINKTIME_LIBPATH} file_adapter_ex2.o ${LIB}

file_adapter_ex2.o: file_adapter_ex2.c
	gcc -c file_adapter_ex2.c -I${INCLUDE_PATH}

.PHONY: clean

clean:
	-rm -f file_adapter_ex2.exe file_adapter_ex2.o
