#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {

	int counter = 0;

	srand(time(NULL));

	while ((rand() % 10) != 3) {
		counter++;
	}

	printf("Extracted %d random numbers before terminating.\n", counter);

	return 0;
}
