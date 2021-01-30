#pragma once
#define MAX 100

typedef struct store{
	char name[MAX];
	char menu[MAX];
	char type[5];
	double star;
} STORE;

typedef struct answer{
	int afood[8];
	int auchoice;
	int place;
	int newtype;
	STORE news;
} ANSWER;

ANSWER afoodArray(int* food, ANSWER a){
	for(int i = 0; i < 9; i++){
		if (food[i] == 0) break;
		a.afood[i] = food[i];
	}
	return a;
}
