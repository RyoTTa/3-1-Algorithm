#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct Level {
	int inc;
	int profit;
	int weight;
}Level;

Level *level;
int num_element = 0;
int weight_limit, numbest, maxprofit;
FILE *fr;
int *bestset;
int *include = NULL;

void swap(Level*a, Level*b);
int  promising(int i, int profit, int weight);
void knapsack(int i, int profit, int weight);
void quicksort(int left, int right);
void file_output();
void print_bestset(FILE *f);

int main() {
	char input_n[100];
	int i = 0;

	printf("input file name?");
	scanf("%s", input_n);
	fr = fopen(input_n, "r");
	fscanf_s(fr, "%d", &num_element);
	fscanf_s(fr, "%d", &weight_limit);
	level = (Level*)malloc(sizeof(Level)*(num_element + 1));
	bestset = (int*)malloc(sizeof(int)*(num_element + 1));
	include = (int*)malloc(sizeof(int)*(num_element + 1));

	for (i = 0; i <= num_element; i++) {
		level[i].profit = 0;
		level[i].weight = 0;
		bestset[i] = 0;
		include[i] = 0;
	}
	for (i = 1; i <= num_element; i++) {
		level[i].inc = i;
		fscanf_s(fr, "%d", &level[i].profit);
		fscanf_s(fr, "%d", &level[i].weight);
	}
	fclose(fr);

	maxprofit = 0;
	knapsack(0, 0, 0);
	file_output();
	return 0;
}
int  promising(int i, int profit, int weight)
{
	int j;
	int bound;
	int totweight;
	if (weight >= weight_limit) {
		return 0;
	}

	j = i + 1;
	bound = profit;
	totweight = weight;
	while (j <= weight_limit && totweight + level[j].weight <= weight_limit) {
		totweight = totweight + level[j].weight;
		bound = bound + level[j].profit;
		j++;
	}

	if (j <= weight_limit) {
		bound += (weight_limit - totweight)*level[j].profit / level[j].weight;

	}
	if (bound > maxprofit)
		return 1;
	return 0;
}
void knapsack(int i, int profit, int weight) {
	int k;

	if (weight <= weight_limit && profit > maxprofit)
	{
		maxprofit = profit;
		for (k = 1; k <= num_element; k++) {
			bestset[k] = include[k];
		}
	}
	if (promising(i, profit, weight)) {
		if (i > num_element) return;
		include[i+1] = 1;
		knapsack(i + 1, profit + level[i + 1].profit, weight + level[i + 1].weight);
		include[i+1] = 0;
		knapsack(i + 1, profit, weight);
	}
}
void file_output() {
	FILE *f_out;
	f_out = fopen("output.txt", "w");
	print_bestset(f_out);
	fclose(f_out);
	free(level);
	level = NULL;
	free(bestset);
	bestset = NULL;
	free(include);
}
void print_bestset(FILE *f) {
	int i;
	fprintf(f, "%d\n", maxprofit);
	for (i = 1; i <= num_element; i++) {
		fprintf(f, "%d\n", bestset[i]);
	}
}
