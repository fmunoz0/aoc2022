#include "stdio.h"
#include "string.h"
#include "stdlib.h"

int main() {
	FILE* f;
	char buf[100];
	int cycle = 1, x = 1, k, i, col;
	
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
			col = (cycle - 1) % 40;
			if (col >= (x - 1) && col <= (x + 1))
				putchar('#');
			else
				putchar('.');
			
			if (col == 39)
				putchar('\n');
			
			cycle++;
		}
		
		if (!strncmp(buf, "addx", 4))
			x += atoi(buf + 5);
	}
	
	fclose(f);
	return 0;
}