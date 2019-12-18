#include <stdio.h>

#define ARRAY_S 101
#define MAX_INT 2147483647

int result = MAX_INT;

void make_maze(int max, int MAP[][ARRAY_S], char T[][ARRAY_S], int L[][ARRAY_S]) {

	int i, j, row = 1, col = 1, min = 0;
	L[1][1] = 0;

	for (int count = 1; count <= max * max; count++) {
		min = MAX_INT;
		for (i = 1; i <= max; i++) {
			for (j = 1; j <= max; j++) {
				if ((L[i][j] != -1) && (L[i][j] < min)) {
					row = i;
					col = j;
					min = L[i][j];
				}
			}
		}
		if (L[row][col] + (MAP[row - 1][col] == 0 ? 1 : 0) < L[row - 1][col]) {
			L[row - 1][col] = L[row][col] + (MAP[row - 1][col] == 0 ? 1 : 0);
			T[row - 1][col] = 'D';
		}
		if (L[row][col] + (MAP[row][col + 1] == 0 ? 1 : 0) < L[row][col + 1]) {
			L[row][col + 1] = L[row][col] + (MAP[row][col + 1] == 0 ? 1 : 0);
			T[row][col + 1] = 'L';
		}
		if (L[row][col] + (MAP[row + 1][col] == 0 ? 1 : 0) < L[row + 1][col]) {
			L[row + 1][col] = L[row][col] + (MAP[row + 1][col] == 0 ? 1 : 0);
			T[row + 1][col] = 'U';
		}
		if (L[row][col] + (MAP[row][col - 1] == 0 ? 1 : 0) < L[row][col - 1]) {
			L[row][col - 1] = L[row][col] + (MAP[row][col - 1] == 0 ? 1 : 0);
			T[row][col - 1] = 'R';
		}
		if (row == max && col == max) {
			if (result > L[row][col]) {
				result = L[row][col];
			}
		}
		L[row][col] = -1;
	}

}

void print_path(int max, char T[][ARRAY_S], FILE *fw) {

	int i, count = 0;
	int row = max, col = max;
	char stack[ARRAY_S][ARRAY_S];

	while (row != 1 || col != 1){
		sprintf(stack[count], "%d %d", row, col);
		if (T[row][col] == 'D')
			row++;
		else if (T[row][col] == 'L')
			col--;
		else if (T[row][col] == 'U')
			row--;
		else if (T[row][col] == 'R')
			col++;
		count++;
	}
	sprintf(stack[count], "%d %d", 1, 1);

	fprintf(fw, "%d\n", result);
	for (i = count; i >= 0; i--) {
		fprintf(fw,"%s\n", stack[i]);
	}
	fclose(fw);
}
int main(void) {

	int i, j, max = 0;
	char filename[ARRAY_S] = { 0, };
	int MAP[ARRAY_S][ARRAY_S] = { 0, }, L[ARRAY_S][ARRAY_S] = { 0, };
	char  T[ARRAY_S][ARRAY_S] = { 0, };
	FILE *fr, *fw;

	printf("input file name?\n");
	scanf("%s", filename);

	if (!(fr = fopen(filename, "r"))) {
		printf("fopen error!\n");
		return 0;
	}

	fscanf(fr, "%d", &max);
	for (i = 1; i <= max; i++) {
		for (j = 1; j <= max; j++) {
			fscanf(fr, "%1d", &MAP[i][j]);
		}
	}
	fclose(fr);

	for (i = 1; i <= max; i++) {
		for (j = 1; j <= max; j++) {
			L[i][j] = MAX_INT;
		}
	}
	make_maze(max, MAP, T, L);
	fw = fopen("output.txt", "w+");
	print_path(max, T, fw);
	return 0;
}
