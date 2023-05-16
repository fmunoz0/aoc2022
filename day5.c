#include "stdio.h"

void resolve(int part){
	FILE* f = fopen("day5.txt", "r");
	char stacks[9][56]={0}; //en peor caso todas las cajas en un stack son 56
	int sizes[9]={0};
	int i,j;
	char buf[100];
	
	for(i=0; i<8; i++){
		fgets(buf, 100, f);
		for(j=0; j<9; j++){
			//las cajas estan en la columna 1,5,9,13,... del archivo de entrada
			int c = buf[j*4+1];
			if (c != ' ') {
				//guardo las cajas de mas arriba al final del stack
				stacks[j][7-i] = c;
				sizes[j]++;
			}
		}
	}
	fgets(buf, 100, f);
	fgets(buf, 100, f);

	for(;;){
		if (feof(f)) break;
		int move, from, to;
		fscanf(f, "move %d from %d to %d\n", &move, &from, &to);
		//en la entrada los stacks van del 1 al 9
		// pero en memoria del 0 al 8
		from--;
		to--;
		for(i=0; i<move; i++){
			if (part == 1) {
				stacks[to][sizes[to]] = stacks[from][sizes[from]-1];
				sizes[to]++;
				sizes[from]--;
			} else {
				stacks[to][sizes[to]] = stacks[from][sizes[from]-move+i];
				sizes[to]++;
			}
		}
		if (part == 2)
			sizes[from] -= move;
	}
	
	for(i=0; i<9; i++)
		if (sizes[i] > 0)
			printf("%c", stacks[i][sizes[i]-1]);
	printf("\n");
	
	fclose(f);
}

int main(){
	resolve(2);
}