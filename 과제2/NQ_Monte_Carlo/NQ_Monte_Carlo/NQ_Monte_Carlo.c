#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#define D_NUM 5

int num_element;
int *col;
FILE *fr, *fw;
time_t startTime;

void procedure_queens(int i);
int promising(int i);
void montecarlo_n_queens();

int main() {
	char input_n[100];
	int i = 0;
	int cnt = 0;

	printf("input file name?\n");
	scanf("%s", input_n);

	fr = fopen(input_n, "r");
	fw = fopen("output.txt", "w+");
	fscanf(fr, "%d", &num_element);
	fclose(fr);

	col = (int*)malloc(sizeof(int)*(num_element + 1));
	for (i = 1; i <= num_element; i++) {
		col[i] = 0;
	}

	srand(time(NULL));
	while (1) {
		montecarlo_n_queens();
	}
	return 0;
}
void procedure_queens(int i) {
	int j;
	if (promising(i)) {
		if (i == num_element){
			for (int k = 1; k <= num_element; k++) {
				fprintf(fw, "%d\n", col[k]);
			}
			fclose(fw);
			exit(1);
		}
		else{
			for (j = 1; j <= num_element; j++) {
				col[i + 1] = j;
				procedure_queens(i + 1);
			}
		}
	}
}
void montecarlo_n_queens() {
	int i, j, temp, temp2;
	temp = 0;
	temp2 = 0;
	i = 1;

	if (num_element > D_NUM) {
		while (i <= (num_element - D_NUM)) {
			j = (rand() % num_element) + 1;
			col[i] = j;

			if (promising(i)) {
				temp = 0;
				i++;
			}
			if (temp >= num_element * 0.95) {
				i = i * 0.95;
				temp = 0;
				temp2++;
			}
			if (temp2 >= num_element * 0.2) {
				i = 1;
				temp = 0;
				temp2 = 0;
			}
			temp++;
		}
	}
	else
	procedure_queens(0);
	procedure_queens(num_element - D_NUM);
}
int promising(int i) {
	int k = 1;
	int result = 1;

	while (k < i&&result) {
		if ((col[i] == col[k]) || abs(col[i] - col[k]) == abs(i - k))
			result = 0;
		k++;
	}
	return result;
}