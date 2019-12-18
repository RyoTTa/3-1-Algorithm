#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define ARRAY_S 101
#define MAX_INT 2147483647

int result = MAX_INT;

void make_maze(int max, int **MAP, char **T, int **L) {

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

void print_path(int max, char **T, FILE *fw) {

	int i, count = 0;
	int row = max, col = max;
	char **stack;

	stack = (int**)malloc(sizeof(int*) * (max*max));
	for (int i = 0; i < max*max + 2; i++) {
		stack[i] = (int*)malloc(sizeof(int) * (max*max));
	}

	while (row != 1 || col != 1) {
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
		fprintf(fw, "%s\n", stack[i]);
	}
	fclose(fw);
}
int main(void) {

	int i, j, max = 0;
	char filename[ARRAY_S] = { 0, };
	int **MAP, **L;
	char **T;
	FILE *fr, *fw;

	printf("input file name?\n");
	scanf("%s", filename);

	if (!(fr = fopen(filename, "r"))) {
		printf("fopen error!\n");
		return 0;
	}

	fscanf(fr, "%d", &max);

	MAP = (int**)malloc(sizeof(int*) * (max+2));
	L = (int**)malloc(sizeof(int*) * (max+2));
	T = (char**)malloc(sizeof(char*) * (max+2));
	for (int i = 0; i < max+2; i++) {
		MAP[i] = (int*)malloc(sizeof(int) * (max+2));
		L[i] = (int*)malloc(sizeof(int) * (max+2));
		T[i] = (char*)malloc(sizeof(char) * (max+2));
	}

	for (i = 0; i < max+2; i++) {
		for (j = 0; j < max+2; j++) {
			MAP[i][j] = 0;
			L[i][j] = 0;
			T[i][j] = 0;
		}
	}

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
