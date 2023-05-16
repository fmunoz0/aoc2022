#include "stdio.h"
#include "string.h"

#define P(c) (c<='Z' ? (c-'A'+26) : (c-'a'))

int main() {
	char line1[100];
	char line2[100];
	char line3[100];
	FILE* f = fopen("day3.txt", "r");
	int total = 0;
	int i, len;
	
	while (1) {
		fgets(line1, 200, f);
		fgets(line2, 200, f);
		fgets(line3, 200, f);
		if (feof(f)) break;
		
		len = strlen(line1) - 1;
		for (i = 0; i < len; i++) {
			char c = line1[i];
			
			// si el caracter c esta en las 3 lineas
			if (strchr(line2, c) && strchr(line3, c)){
				if (c >= 'a' && c <= 'z')
					total += (c - 'a' + 1);
				else
					total += (c - 'A' + 27);
				
				break;
			}
		}
	}
	fclose(f);
	
	printf("%d\n", total);

	return 0;
}