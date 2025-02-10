#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// first col is dir
// second col is number of steps
int moves[2000][2];
int num_moves;

void readMoves(const char* name){
	char buf[100];
	FILE* f = fopen(name, "r");
	int i = 0;
	
	while (fgets(buf, sizeof(buf), f)) {
		sscanf(buf, "%c %d", moves[i], moves[i]+1);
		i++;
	}
	
	num_moves = i;
	
	fclose(f);
}

int startRow, startCol;
bool** map;
int rows, cols;

void createMap(){
	int row=0, col=0;
	int minRow=0, maxRow=0;
	int minCol=0, maxCol=0;
	
	for (int i = 0; i < num_moves; i++){
		switch (moves[i][0]){
			case 'U': row -= moves[i][1]; break;
			case 'D': row += moves[i][1]; break;
			case 'L': col -= moves[i][1]; break;
			case 'R': col += moves[i][1]; break;
		}
		minRow = row < minRow ? row : minRow;
		maxRow = row > maxRow ? row : maxRow;
		minCol = col < minCol ? col : minCol;
		maxCol = col > maxCol ? col : maxCol;
	}
	
	rows = abs(maxRow - minRow + 1);
	cols = abs(maxCol - minCol + 1);
	
	startRow = abs(minRow);
	startCol = abs(minCol);
	
	// create map
	map = malloc(sizeof(bool*) * rows);
	for (int i = 0; i < rows; i++){
		map[i] = malloc(sizeof(bool) * cols);
		for (int j = 0; j < cols; j++)
			map[i][j] = false;
	}
}

void moveTail(int headRow, int headCol, int* tailRow, int* tailCol){
	int deltaRow = headRow - *tailRow;
	int deltaCol = headCol - *tailCol;
	
	// if the head is adyacent to the tail, do nothing
	if (abs(deltaRow) <= 1 && abs(deltaCol) <= 1)
		return;	
	
	// at this point we only have 2 possible cases:
	// one delta is 0 and the other is 2 -> orthogonal motion
	// one delta is 1 and the other is 2 -> diagonal motion
	
	if (abs(deltaRow) > 0)
		*tailRow += deltaRow > 0 ? 1 : -1;
	
	if (abs(deltaCol) > 0)
		*tailCol += deltaCol > 0 ? 1 : -1;
}

int simulateMoves(){
	int headRow=startRow, headCol=startCol;
	int tailRow=startRow, tailCol=startCol;
	int visitedCount=0;
	
	for (int i = 0; i < num_moves; i++){
		for (int j = 0; j < moves[i][1]; j++) { // for each step
			// move head
			switch (moves[i][0]){
				case 'U': headRow--; break;
				case 'D': headRow++; break;
				case 'L': headCol--; break;
				case 'R': headCol++; break;
			}
			
			moveTail(headRow, headCol, &tailRow, &tailCol);
			
			visitedCount += map[tailRow][tailCol] ? 0 : 1; // only count when visiting for first time
			map[tailRow][tailCol] = true; // visit position
		}
	}
	
	return visitedCount;
}

int main(){
	readMoves("day9.txt");

	createMap();
	//printf("%d %d %d %d\n", rows, cols, startRow, startCol);
	printf("%d\n", simulateMoves());
	
	/*for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++)
			printf("%c", map[i][j] ? '*' : '-');
		puts("");
	}*/
	
	return 0;
}