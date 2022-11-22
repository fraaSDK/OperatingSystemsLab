#define ALLOCAVETTORE(PTR)											\
		do {														\
			PTR=(int32_t*)malloc(10 * sizeof(int32_t));				\
			if (PTR != NULL) {										\
				int i, j = 0;										\
				for (i = -1000; i <= -991; i++) {					\
					PTR[j] = i;										\
					j++;											\
				}													\
			}														\
		} while (0)
