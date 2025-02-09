#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int map[100][100];
int rows, cols;

void readMap(const char* name){
	char buf[200];
	FILE* f = fopen(name, "r");
	
	rows = 0;
	
	while (fgets(buf, sizeof(buf), f)) {
		int len = strlen(buf) - 2; // trim \r\n
		
		for (cols = 0; cols < len; cols++) {
			int height = buf[cols] - '0'; // convert caracter to int
			map[rows][cols] = height;
		}
		
		rows++;
	}
	
	fclose(f);
}

bool isVisible(int row, int col){
	int height = map[row][col];
	
	// up
	bool visible = true;
	for (int r = row-1; r >= 0 && visible; r--)
		if (height <= map[r][col])
			visible = false;
	
	if (visible) return true;
	
	// bottom
	visible = true;
	for (int r = row+1; r < rows && visible; r++)
		if (height <= map[r][col])
			visible = false;
	
	if (visible) return true;
	
	// left
	visible = true;
	for (int c= col-1; c >= 0 && visible; c--)
		if (height <= map[row][c])
			visible = false;
	
	if (visible) return true;
	
	
	// right
	visible = true;
	for (int c= col+1; c < cols && visible; c++)
		if (height <= map[row][c])
			visible = false;
	
	if (visible) return true;
	
	return false;
}

int countVisibleTrees(){
	int count = (rows<<1) + (cols<<1) - 4; // trees on border
	
	for (int r = 1; r < rows-1; r++)
		for (int c = 1; c < cols-1; c++)
			count += isVisible(r, c) ? 1 : 0;
	
	return count;
}

int scenicScore(int row, int col){
	int height = map[row][col];
	int up=0, down=0, left=0, right=0;
	
	// up
	for (int r = row-1; r >= 0; r--){
		up++;
		if (map[r][col] >= height)
			break;
	}
	// down
	for (int r = row+1; r < rows; r++){
		down++;
		if (map[r][col] >= height)
			break;
	}
	// left
	for (int c = col-1; c >= 0; c--){
		left++;
		if (map[row][c] >= height)
			break;
	}
	// right
	for (int c = col+1; c < cols; c++){
		right++;
		if (map[row][c] >= height)
			break;
	}
	
	return up * down * left * right;
}

int maxScenicScore(){
	int maxScore = 0;
	
	for (int r = 1; r < rows-1; r++)
		for (int c = 1; c < cols-1; c++){
			int score = scenicScore(r, c);
			maxScore = score > maxScore ? score : maxScore;
		}
			
	return maxScore;
}

int main(){
	readMap("day8.txt");
	
	// part 1
	//printf("%d\n", countVisibleTrees());
	
	// part 2
	printf("%d\n", maxScenicScore());
	return 0;
}