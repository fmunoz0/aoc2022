#include "stdio.h"
#include "stdint.h"
#include "string.h"
#include "stdlib.h"

#define MAXDIRSIZE 100000

uint64_t traverse(FILE* f, uint64_t* result) {
	char buf[50];
	uint64_t total = 0;
	
	while (1) {
		fgets(buf, 50, f);
		if (feof(f)) break;
		
		if (!strncmp(buf, "$ cd ..", 7)) break;
		
		if (!strncmp(buf, "$ cd", 4))
			total += traverse(f, result);
		else {
			// parsing a non numeric string to int gives 0, so there is no problem
			// of adding the return of atoi directly
			total += (uint64_t)atoi(buf);
		}
	}
	
	*result += (total < MAXDIRSIZE ? total : 0);
	
	return total;
}


int main() {
	FILE* f = fopen("day7.txt", "r");
	
	uint64_t result = 0;
	traverse(f, &result);
	
	fclose(f);
	
	printf("%llu\n", result);
	
	
	return 0;
}