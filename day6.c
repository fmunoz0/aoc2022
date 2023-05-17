#include <stdio.h>
#include <stdlib.h>

int main() {
	FILE* f = fopen("day6.txt", "r");
	char* buf = calloc(5000, 1);
	fgets(buf, 5000, f);
	
	int i = 0;
	
	while (1) {
		if (buf[i] != buf[i+1] && buf[i] != buf[i+2] && buf[i] != buf[i+3] &&
			buf[i+1] != buf[i+2] && buf[i+1] != buf[i+3] &&
			buf[i+2] != buf[i+3])
			break;
		
		i++;
	}
	
	printf("%d\n", i+4);
	
	free(buf);
	fclose(f);
	return 0;
}