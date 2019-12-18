#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#define MAX_INT 999999999
#define ARRAY_S 500

void print_path(int L, int R, int k, int*** PP, FILE* fw);
void off_lamp(int*** EE, int*** PP, int* WS, int* D, int M, int N);

int main() {
	int i, j, N, M;
	int *D, *W, *WS;
	int ***EE, ***PP;
	char filename[ARRAY_S];
	FILE *fr, *fw;

	printf("input file name?\n");
	scanf("%s", filename);
	if (!(fr = fopen(filename, "r"))) {
		printf("fopen error!\n");
		return 0;
	}

	fscanf(fr, "%d\n", &N);
	fscanf(fr, "%d\n", &M);

	D = (int*)malloc(sizeof(int)*(N + 1));
	W = (int*)malloc(sizeof(int)*(N + 1));
	WS = (int*)malloc(sizeof(int)*(N + 1));

	EE = (int***)malloc(sizeof(int**)*(N + 1));
	PP = (int***)malloc(sizeof(int**)*(N + 1));

	for (i = 1; i <= N; i++) {
		EE[i] = (int**)malloc(sizeof(int*)*(N + 1));
		PP[i] = (int**)malloc(sizeof(int*)*(N + 1));
		for (j = 1; j <= N; j++) {
			EE[i][j] = (int*)malloc(sizeof(int) * 2);
			PP[i][j] = (int*)malloc(sizeof(int) * 2);
		}
	}

	for (i = 1; i <= N; i++) {
		fscanf(fr, "%d %d\n", &D[i], &W[i]);
		for (j = 1; j <= N; j++) {
			if (i > M || j <= M) EE[i][j][0] = EE[i][j][1] = MAX_INT;
		}
		EE[i][i][0] = EE[i][i][1] = MAX_INT;
		PP[i][i][0] = PP[i][i][1] = 0;
		WS[i] = 0;
		for (j = 1; j <= i; j++) {
			WS[i] = WS[i] + W[j];
		}
	}

	off_lamp(EE, PP, WS, D, M, N);

	if (!(fw = fopen("output.txt", "w"))) {
		printf("fopen error!\n");
		return 0;
	}

	if (EE[1][N][0] < EE[1][N][1]) {
		fprintf(fw, "%d\n", EE[1][N][0]);
		print_path(1, N, 0, PP, fw);
		fprintf(fw, "1\n");
	}
	else {
		fprintf(fw, "%d\n", EE[1][N][1]);
		print_path(1, N, 1, PP, fw);
		fprintf(fw, "%d\n", N);
	}

	return 0;
}

void print_path(int L, int R, int LR, int*** PP, FILE *fw) {
	if (L == R) return;

	if (PP[L][R][LR] == L + 1 && LR == 0) 	print_path(L + 1, R, 0, PP, fw);
	else if (PP[L][R][LR] == R && LR == 0) 	print_path(L + 1, R, 1, PP, fw);
	else if (PP[L][R][LR] == L && LR == 1) 	print_path(L, R - 1, 0, PP, fw);
	else if (PP[L][R][LR] == R - 1 && LR == 1) 	print_path(L, R - 1, 1, PP, fw);

	fprintf(fw, "%d\n", PP[L][R][LR]);
}

void off_lamp(int*** EE, int*** PP, int* WS, int* D, int M, int N) {

	int L, R, A, B;

	EE[M][M][0] = EE[M][M][1] = 0;

	for (R = M; R <= N; R++) {
		for (L = M; L >= 1; L--) {
			if (R == M && L == M) continue;

			if ((A = EE[L + 1][R][0] + (D[L + 1] - D[L]) * (WS[N] - (WS[R] - WS[L]))) <
				(B = EE[L + 1][R][1] + (D[R] - D[L]) * (WS[N] - (WS[R] - WS[L])))) {
				EE[L][R][0] = A;
				PP[L][R][0] = L + 1;
			}
			else {
				EE[L][R][0] = B;
				PP[L][R][0] = R;
			}

			if ((A = EE[L][R - 1][0] + (D[R] - D[L]) * (WS[N] - (WS[R - 1] - WS[L - 1]))) <
				(B = EE[L][R - 1][1] + (D[R] - D[R - 1]) * (WS[N] - (WS[R - 1] - WS[L - 1])))) {
				EE[L][R][1] = A;
				PP[L][R][1] = L;
			}
			else {
				EE[L][R][1] = B;
				PP[L][R][1] = R - 1;
			}
		}
	}

}