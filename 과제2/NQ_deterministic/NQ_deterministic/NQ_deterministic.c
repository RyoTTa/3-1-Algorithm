#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>

int num_element;
int *col;
FILE *fr,*fw;

void procedure_queens(int i);
bool promising(int i);


int main() {
	char input_n[100];
	int i = 0;

	printf("input file name?\n");
	scanf("%s",input_n);

	fr = fopen(input_n, "r");
	fw = fopen("output.txt", "w+");
	fscanf(fr, "%d", &num_element);
	fclose(fr);

	col = (int*)malloc(sizeof(int)*(num_element + 1));
	for (i = 1; i <= num_element; i++) {
		col[i] = 0;
	}

	procedure_queens(0);

	return 0;
}

void procedure_queens(int i) {
	int j;

	if (promising(i)) {
		if (i == num_element) {
			for (i = 1; i <= num_element; i++) {
				fprintf(fw, "%d\n", col[i]);
			}
			fclose(fw);
			exit(1);
		}
		else {
			for (j = 1; j <= num_element; j++) {
				col[i + 1] = j;
				procedure_queens(i + 1);
			}
		}
	}
}
bool promising(int i) {
	int k = 1;
	bool promising = true;

	while (k < i&&promising) {
		if ((col[i] == col[k]) || abs(col[i] - col[k]) == abs(i - k))
			promising = 0;
		k++;
	}
	return promising;
}