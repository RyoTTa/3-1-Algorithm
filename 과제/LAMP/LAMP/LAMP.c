#include <stdio.h>
#define MIN(X,Y) ((X) < (Y) ? (X) : (Y)) 
#define ARRAY_S 500
#define MAX_INT 99999999

int M = 0;
unsigned long EE[ARRAY_S][ARRAY_S][2] = { 0, };
int PP[ARRAY_S][ARRAY_S][2] = { 0, };
int W[ARRAY_S] = { 0, };
int D[ARRAY_S] = { 0, };
int WS[ARRAY_S] = { 0, };
int max=0;

int min1(int L, int R, int A, int B) {

	if (A <= B) {
		PP[L][R][0] = L + 1;
		return A;
	}
	else {
		PP[L][R][0] = R;
		return B;
	}
}

int min2(int L, int R,int A, int B) {

	if (A <= B) {
		PP[L][R][1] = L;
		return A;
	}
	else {
		PP[L][R][1] = R - 1;
		return B;
	}
}

int off_lamp(int L, int R, int direction) {

	if (M == L && M == R) return 0;
	else if (L == R && L != M) return MAX_INT;
	else if (L > M || R < M) return MAX_INT;
	if (EE[L][R][direction] != 0) return EE[L][R][direction];

	if (direction == -1) {
		EE[L][R][0] = min1(L, R, off_lamp(L + 1, R, 0) + (D[L + 1] - D[L]) * (WS[max] - (WS[R] - WS[L])), off_lamp(L + 1, R, 1) + (D[R] - D[L]) * (WS[max] - (WS[R] - WS[L])));
		EE[L][R][1] = min2(L, R, off_lamp(L, R - 1, 0) + (D[R] - D[L]) * (WS[max] - (WS[R-1] - WS[L-1])), off_lamp(L, R - 1, 1) + (D[R] - D[R - 1]) * (WS[max] - (WS[R - 1] - WS[L - 1])));
		return MIN(EE[L][R][0],EE[L][R][1]);
	}
	else if (direction == 0) {
		EE[L][R][0] = min1(L, R, off_lamp(L + 1, R, 0) + (D[L + 1] - D[L]) * (WS[max] - (WS[R] - WS[L])), off_lamp(L + 1, R, 1) + (D[R] - D[L]) * (WS[max] - (WS[R] - WS[L])));
		return EE[L][R][0];
	}
	else if (direction == 1) {
		EE[L][R][1] = min2(L, R, off_lamp(L, R - 1, 0) + (D[R] - D[L]) * (WS[max] - (WS[R - 1] - WS[L - 1])), off_lamp(L, R - 1, 1) + (D[R] - D[R - 1]) * (WS[max] - (WS[R - 1] - WS[L - 1])));
		return EE[L][R][1];
	}
}

void print_path(int L, int R, int direction, FILE *fw)
{
	int temp=0;

	temp = PP[L][R][direction];

	if (temp == M) { fprintf(fw, "%d\n", temp); return 0; }

	if (direction == 0) {
		if (temp - L == 1) {
			print_path(temp, R, 0, fw);
		}
		else {
			print_path(L + 1, temp, 1, fw);
		}
		fprintf(fw, "%d\n", temp);
	}
	else{
		if (R - temp == 1) print_path(L, temp, 1, fw);
		else print_path(temp, R - 1, 0, fw);
		fprintf(fw, "%d\n", temp);
	}
}
int main(void) {

	int i, j;
	char filename[ARRAY_S] = { 0, };
	FILE *fr, *fw;

	printf("input file name?\n");
	scanf("%s", filename);

	if (!(fr = fopen(filename, "r"))) {		//파일 input
		printf("fopen error!\n");
		return 0;
	}

	fscanf(fr, "%d", &max);					//가로등 최대값 입력
	fscanf(fr, "%d", &M);					//초기 위치 입력
	for (i = 1; i <= max*2; i++) {			//D, W 파일 입력
		fscanf(fr, "%d", &D[i]);
		fscanf(fr, "%d", &W[i]);
	}
	fclose(fr);

	for (i = 1; i <= max; i++) {			//WS, PP EE 초기화
		for (j = 1; j <= i; j++) {			
			WS[i] += W[j];
		}
		if (i != M) EE[i][i][0] = EE[i][i][1] = MAX_INT;
	}

	fw = fopen("output.txt", "w+");
	i = off_lamp(1, max, -1);
	fprintf(fw, "%d\n", i);
	if (i == EE[1][6][1]) {
		print_path(1, max, 1, fw);
		fprintf(fw,"%d\n", max);
	}
	else if (i == EE[1][6][0]) {
		print_path(1, max, 0, fw);
		fprintf(fw,"%d\n", 1);
	}
	fclose(fw);

	return 0;
}
