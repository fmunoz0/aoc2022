#include "stdio.h"
#include "stdint.h"
#include "string.h"
#include "stdlib.h"

#define TOTALDISKSPACE 70000000UL
#define MINFREESPACE 30000000UL

uint64_t traverse(FILE* f, uint64_t* dirsizes, int* lastdir) {
	char buf[50];
	uint64_t total = 0;
	int curdir = (*lastdir)++;
	
	while (1) {
		fgets(buf, 50, f);
		if (feof(f)) break;
		
		if (!strncmp(buf, "$ cd ..", 7)) break;
		
		if (!strncmp(buf, "$ cd", 4))
			total += traverse(f, dirsizes, lastdir);
		else {
			// parsing a non numeric string to int gives 0, so there is no problem
			// of adding the return of atoi directly
			total += (uint64_t)atoi(buf);
		}
	}

	dirsizes[curdir] = total;
	return total;
}

int main() {
	FILE* f = fopen("day7.txt", "r");
	uint64_t* dirsizes = calloc(200, sizeof(uint64_t));
	int lastdir = 0;
	uint64_t usedspace = traverse(f, dirsizes, &lastdir);
	fclose(f);
	uint64_t freespace = TOTALDISKSPACE - usedspace;
	uint64_t mindirsize = usedspace;
	int i;
	for (i = 0; i < 200; i++) {
		if ((freespace + dirsizes[i] > MINFREESPACE) && (dirsizes[i] < mindirsize))
			mindirsize = dirsizes[i];
	}
	free(dirsizes);
	
	printf("%llu\n", mindirsize);
	
	return 0;
}