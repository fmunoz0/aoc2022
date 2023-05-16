#include "stdio.h"
#include "stdlib.h"

int main() {
	FILE* f = fopen("day2.txt", "r");
	char buf[100];
	int sum = 0;
	
	while (1) {
		fgets(buf, 100, f);
		if (feof(f)) break;
		
		char op = buf[0];
		char me = buf[2];

		int score = 0;
		
/*
		if ((op=='A' && me=='Y') || (op=='B' && me=='Z') || (op=='C' && me=='X'))
			score = 6;
		else if ((op=='A' && me=='X') || (op=='B' && me=='Y') || (op=='C' && me=='Z'))
			score = 3;

		score += (me-'X'+1);
*/		

		if (me == 'Y') {
			score = 3;
			if (op == 'A') score += 1;
			else if (op == 'B') score += 2;
			else if (op == 'C') score += 3;
		}
		else if (me == 'Z') {
			score = 6;
			if (op == 'A') score += 2;
			else if (op == 'B') score += 3;
			else if (op == 'C') score += 1;
		} else {
			if (op == 'A') score += 3;
			else if (op == 'B') score += 1;
			else if (op == 'C') score += 2;
		}
		
		sum += score;
	}
	
	fclose(f);
	
	printf("%d\n", sum);

	return 0;
}