#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int main() {
	int32_t *p;
	int i;

	ALLOCAVETTORE(p);
	
	/* Controllo */
	for (i = 0; i < 10; i++) {
		printf("%d ", p[i]);
	}
	printf("\n");

	for (i = 0; i < 10; i++) {
		p[i] = -19 + i;
	}
	for (i = 0; i < 10; i++) {
		printf("%d ", p[i]);
	}
	printf("\n");

	return 0;
}
