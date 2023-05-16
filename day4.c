#include "stdio.h"

int main(){
	FILE* f = fopen("day4.txt", "r");
	int a,b,c,d;
	int total = 0;
	int nonoverlap = 0;
	for(;;){
		fscanf(f, "%d-%d,%d-%d", &a,&b,&c,&d);
		if(feof(f)) break;
		
		if(b<c || a>d)
			nonoverlap++;
		
		total++;
	}
	
	printf("%d\n", total-nonoverlap);
	
	fclose(f);
}