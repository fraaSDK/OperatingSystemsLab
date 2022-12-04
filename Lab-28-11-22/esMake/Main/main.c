#include <stdio.h>
#include <stdlib.h>
#include "A.h"
#include "B.h"

int main(int argc, char *argv[]) {
	double num = (double) atoi(argv[1]);

	if (argc != 2) {
		printf("I need 1 parameter\n");
		return 1;
	}

	printf("%f\n", calcolaA(calcolaB(num)));
	return 0;
}
