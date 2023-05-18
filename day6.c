#include <stdio.h>
#include <stdlib.h>

void resolve(const char* buf, int marker_length) {
	int marker_end = marker_length;
	int cur_byte = marker_end; // this holds the pos of the byte being compared
	
	while (1) {
		int i = cur_byte - 1; // this always move between [marker_end-13, marker_end-1]
			
		while (buf[i] != buf[cur_byte] && i > marker_end-marker_length)
			i--;
		
		// if we found a repeated byte, we can advance the marker start
		// to the byte next to the repeated byte
		if (marker_end - i < marker_length) {
			marker_end = i + marker_length;
			cur_byte = marker_end;
		} else {
			// if we checked all the bytes in the marker, we found the solution
			if (marker_end - cur_byte == marker_length) {			
				printf("%d\n", marker_end + 1);
				break;
			}
			
			// if there is no repeated byte, we check the byte before current byte
			cur_byte--;
		}
	}
}

int main() {
	FILE* f = fopen("day6.txt", "r");
	char* buf = calloc(5000, 1);
	fgets(buf, 5000, f);
	
	//resolve(buf, 4);
	resolve(buf, 14);
	
	free(buf);
	fclose(f);
	return 0;
}