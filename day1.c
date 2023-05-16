#include "stdio.h"
#include "stdlib.h"

int main() {
	FILE* f = fopen("day1.txt", "r");
	char buf[100];
	unsigned max[3] = {0};
	unsigned sum = 0;
	
	while (1) {
		fgets(buf, 100, f);
		if (feof(f)) break;
		
		if (buf[0] == '\n') {
			if (sum > max[0]) {
				max[2] = max[1];
				max[1] = max[0];
				max[0] = sum;
			} else if (sum > max[1]) {
				max[2] = max[1];
				max[1] = sum ;
			} else if (sum > max[2])
				max[2] = sum;
			
			sum = 0;
			continue;
		}
		
		sum += (unsigned)atoi(buf);
	}
	
	fclose(f);
	
	printf("%u\n", max[0]);
	printf("%u\n", max[1]);
	printf("%u\n", max[2]);
	printf("%u\n", max[0]+max[1]+max[2]);
	return 0;
}