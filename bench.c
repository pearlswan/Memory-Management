// Implementation of bench, which tests the memory manager we wrote.
// Author: Yicheng Wang

#include "mem.h"
#include <stdlib.h>
#include <time.h>
#include "mem_impl.h"

int main(int argc, char** argv) {
// parameters
int ntrials, pctget, pctlarge, small_limit, large_limit, random_seed;
int count = 0;
int malloc_ed = 0;  // Num of malloced blocks
int decide;  // Random decider
uintptr_t malloc_size;  // Random malloc size
clock_t t = clock();
if (argc >= 2) {
	ntrials = atoi(argv[1]);
} else {
	ntrials = 10000;
}
if (argc >= 3) {
	pctget = atoi(argv[2]);
} else {
	pctget = 50;
}
if (argc >= 4) {
	pctlarge = atoi(argv[3]);
} else {
	pctlarge = 10;
}
if (argc >= 5) {
	small_limit = atoi(argv[4]);
} else {
	small_limit = 200;
}
if (argc >= 6) {
	large_limit = atoi(argv[5]);
} else {
	large_limit = 20000;
}
if (argc >= 7) {
	random_seed = atoi(argv[6]);
} else {
	random_seed = time(NULL);
}
srand(random_seed);
void** pointer_array = calloc(ntrials, sizeof(uintptr_t));  // Stores addresses
total_size = malloc(sizeof(uintptr_t));
total_free = malloc(sizeof(uintptr_t));
n_free_blocks = malloc(sizeof(uintptr_t));
while (count < ntrials) {
	decide = rand() % 100;
	count++;
	// Case when getmem
	if (decide < pctget) {
		decide = rand() % 100;
		if (decide < pctlarge) {
			malloc_size = rand() % small_limit + 1;
		} else {
			malloc_size = 1 + small_limit +
			rand() % (large_limit - small_limit);
		}
		pointer_array[malloc_ed] = getmem(malloc_size);
		malloc_ed++;
	// Case when freemem
	} else {
		if (malloc_ed > 0) {
			decide = rand() % malloc_ed;
			freemem(pointer_array[decide]);
			pointer_array[decide] = pointer_array[malloc_ed - 1];
			malloc_ed--;
		}
	}
	// For ntrials >= 50, print info every 10%
	if ((ntrials >= 50)) {
		if (count % (ntrials / 10) == 0) {
			printf("%d0%% Finished\n", count / (ntrials / 10));
			get_mem_stats(total_size, total_free, n_free_blocks);
			printf("Time used: %f seconds\n", ((float)(clock() - t)/CLOCKS_PER_SEC));
			printf("Total amount of storage accquired: %"PRIuPTR" bytes\n", *total_size);
			printf("Total numbers of blocks: %"PRIuPTR"\n", *n_free_blocks);
			printf("Average bytes in free blocks: %"PRIuPTR"\n", *total_free / *n_free_blocks);
			printf("\n");
		}
	// ntrials < 50, print just once
	} else if ((ntrials < 50) && (count == ntrials)) {
		printf("%d0%% Finished\n", 10);
		get_mem_stats(total_size, total_free, n_free_blocks);
		printf("Time used: %f seconds\n", ((float)(clock() - t)/CLOCKS_PER_SEC));
		printf("Total amount of storage accquired: %"PRIuPTR" bytes\n", *total_size);
		if (*n_free_blocks == 0) {
			printf("Total numbers of blocks: 0\n");
		} else {
			printf("Total numbers of blocks: %"PRIuPTR"\n", *n_free_blocks);
			printf("Average bytes in free blocks: %"PRIuPTR"\n", *total_free / *n_free_blocks);
		}
		printf("\n");
	}
}

return 0;
}
