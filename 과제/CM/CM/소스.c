#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define ARRAY_S 101
#define MAX_INT 2147483647
void minmult(int max, int d[], int M[][ARRAY_S], int P[][ARRAY_S]) {
	
	int i, j, k = 0;

	for (i = max - 1; i >= 1; i--) {
		for (j = 1; j <= max - 1; j++) {
			if (i < j) {
				M[i][j] = MAX_INT;
				for (k = i; k <= j - 1; k++) {
					if ((M[i][k] + M[k + 1][j] + d[i - 1] * d[k] * d[j]) < M[i][j]) {
						M[i][j] = M[i][k] + M[k + 1][j] + d[i - 1] * d[k] * d[j];
						P[i][j] = k;
					}
				}
			}
		}
	}
}

void print_order(int i, int j, int P[][ARRAY_S],FILE *fw) {
	
	int k = 0;

	if (i == j) {
		fprintf(fw, " %d ", i);
	}
	else {
		k = P[i][j];
		fprintf(fw, " ( ");
		print_order(i, k, P, fw);
		print_order(k + 1, j, P, fw);
		fprintf(fw, " ) ");
	}
}

int main(void) {
	
	int i, max = 0;
	char filename[ARRAY_S] = { 0, };
	int d[ARRAY_S], M[ARRAY_S][ARRAY_S]={ 0, }, P[ARRAY_S][ARRAY_S] = { 0, };
	FILE *fr,*fw;

	printf("input file name?\n");
	scanf("%s", filename);

	if (!(fr = fopen(filename, "r"))) {
		printf("fopen error!\n");
		return 0;
	}

	fscanf(fr, "%d", &max);
	for (i = 0; i < max; i++) {
		fscanf(fr, "%d", &d[i]);
	}

	minmult(max, d, M, P);

	fw = fopen("output.txt", "w+");
	print_order(1, max-1, P,fw);
	return 0;
}
