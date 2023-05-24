#include "stdio.h"
#include "string.h"
#include "stdlib.h"

int main() {
	FILE* f;
	char buf[100];
	int cycle = 1, x = 1, k, i, total = 0;
	
	f = fopen("day10.txt", "r");
	
	while (1) {
		fgets(buf, 100, f);
		if (feof(f)) break;
	
		if (!strncmp(buf, "noop", 4))
			k = 1;
		else if (!strncmp(buf, "addx", 4))
			k = 2;
		else
			k = 0;
			
		for (i = 0; i < k; i++) {
			if (cycle >= 20 && (cycle - 20) % 40 == 0) {
				printf("%d * %d = %d\n", cycle, x, cycle * x);
				total += cycle * x;
			}
			cycle++;
		}
		
		if (!strncmp(buf, "addx", 4))
			x += atoi(buf + 5);
	}
	
	printf("%d\n", total);
	
	fclose(f);
	return 0;
}