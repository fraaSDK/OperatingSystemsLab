#include <stdio.h>
#include <stdlib.h>
#include <time.h>

unsigned int dammi_il_precedente(unsigned int current) {
	static unsigned int prev = 0;
	unsigned int res;
	
	printf("prev: %d\vcurr: %d\n", prev, current);
	res = prev;
	prev = current;
	return res;
}

int main() {

	srand(time(NULL));

	while ((dammi_il_precedente(rand()) % 10) != 3);

	return 0;
}
