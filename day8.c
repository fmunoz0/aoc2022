#include "stdio.h"

struct max {
	int up, down, left, right;
};

int map[100][100];
int rows, cols;
struct max max[100][100];

void initmap() {
	/*map[0][0]=3; map[0][1]=0; map[0][2]=3; map[0][3]=7; map[0][4]=3;
	map[1][0]=2; map[1][1]=5; map[1][2]=5; map[1][3]=1; map[1][4]=2;
	map[2][0]=6; map[2][1]=5; map[2][2]=3; map[2][3]=3; map[2][4]=2;
	map[3][0]=3; map[3][1]=3; map[3][2]=5; map[3][3]=4; map[3][4]=9;
	map[4][0]=3; map[4][1]=5; map[4][2]=3; map[4][3]=9; map[4][4]=0;
	rows = 5;
	cols = 5;*/
	FILE* f;
	char buf[200];
	int i;

	f = fopen("day8.txt", "r");
	rows = 0;
	while (1) {
		fgets(buf, sizeof(buf), f);
		if (feof(f)) break;
		
		for (i = 0; buf[i] != '\n'; i++) {
			map[rows][i] = buf[i] - '0';
		}
		
		cols = i;
		rows++;
	}
	fclose(f);
}

void initmax() {
	int i, j;
	for (i = 0; i < rows; i++)
		for (j = 0; j < cols; j++) {
			max[i][j].up = -1;
			max[i][j].down = -1;
			max[i][j].left = -1;
			max[i][j].right = -1;
		}
}

// 38:40
void recursion(int r, int c) {
	if (r == 0)
		max[r][c].up = map[r][c];
	else if (r == rows-1)
		max[r][c].down = map[r][c];

	if (c == 0)
		max[r][c].left = map[r][c];
	else if (c == cols-1)
		max[r][c].right = map[r][c];

	if (max[r][c].right < 0) {
		if (max[r][c+1].right < 0)
			recursion(r, c+1);
		max[r][c].right = (max[r][c+1].right <= map[r][c] ? map[r][c] : max[r][c+1].right);
	}
	
	if (max[r][c].left < 0) {
		if (max[r][c-1].left < 0)
			recursion(r, c-1);
		max[r][c].left = (max[r][c-1].left <= map[r][c] ? map[r][c] : max[r][c-1].left);
	}
	
	if (max[r][c].down < 0) {
		if (max[r+1][c].down < 0)
			recursion(r+1, c);
		max[r][c].down = (max[r+1][c].down <= map[r][c] ? map[r][c] : max[r+1][c].down);
	}
	
	if (max[r][c].up < 0) {
		if (max[r-1][c].up < 0)
			recursion(r-1, c);
		max[r][c].up = (max[r-1][c].up <= map[r][c] ? map[r][c] : max[r-1][c].up);
	}
}

int main() {
	int i, j, total;
	
	initmap();
	initmax();
	
	recursion(0, 0);
	
	int r = 4, c = 4;
	
	printf("%d %d %d %d\n", max[r][c].up, max[r][c].down, max[r][c].left, max[r][c].right);
	
	total = rows * 2 + (cols - 2) * 2;
	for (i = 1; i < rows - 1; i++) {
		for (j = 1; j < cols - 1; j++) {
			total += (map[i][j] > max[i-1][j].up || map[i][j] > max[i+1][j].down || map[i][j] > max[i][j+1].right || map[i][j] > max[i][j-1].left);
		}
	}
	
	printf("%d\n", total);
	
	return 0;
}