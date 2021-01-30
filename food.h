#pragma once
#define MAX 100
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int* food(){
	char num[MAX], ans[MAX], temp[MAX] = {'\0',};
	static int choice[8] = {0,};
	int i = 0;
	printf("\n음식 카테고리를 입력하세요.(중복된 입력 시 입력받기 종료.)\n");
	while (1){

		printf("1. 한식 2. 분식 3. 일식 4. 패스트푸드 5. 양식 6. 중식 7. 아시안 8. 기타 : ");
		fgets (num, MAX, stdin);
		num[strlen(num) - 1] = '\0';
		
		if(strcmp(num, "1") == 0) {
			choice[i] = 1;
			if ( i > 0){
				for (int j = 0; j < i; j++){
					if (choice[i] == choice[j]){
						printf("중복된 입력입니다. 입력받기를 종료합니다.\n\n");
						strcpy(temp,"break");
						break;
					}
				}
			}
			if(strcmp(temp,"break") == 0) break;
			i++;
		}
		else if(strcmp(num, "2") == 0) {
			choice[i] = 2;
			if ( i > 0){
				for (int j = 0; j < i; j++){
					if (choice[i] == choice[j]){
						printf("중복된 입력입니다. 입력받기를 종료합니다.\n");
						strcpy(temp,"break");
						choice[i] = 0;
						break;
					}
				}
			}
			if(strcmp(temp,"break") == 0) break;
			i++;
		}
		else if(strcmp(num, "3") == 0) {
			choice[i] = 3;
			if ( i > 0){
				for (int j = 0; j < i; j++){
					if (choice[i] == choice[j]){
						printf("중복된 입력입니다. 입력받기를 종료합니다.\n");
						strcpy(temp,"break");
						choice[i] = 0;
						break;
					}
				}
			}
			if(strcmp(temp,"break") == 0) break;
			i++;
		}
		else if(strcmp(num, "4") == 0) {
			choice[i] = 4;
			if ( i > 0){
				for (int j = 0; j < i; j++){
					if (choice[i] == choice[j]){
						printf("중복된 입력입니다. 입력받기를 종료합니다.\n");
						strcpy(temp,"break");
						choice[i] = 0;
						break;
					}
				}
			}
			if(strcmp(temp,"break") == 0) break;
			i++;
		}
		else if(strcmp(num, "5") == 0) {
			choice[i] = 5;
			if ( i > 0){
				for (int j = 0; j < i; j++){
					if (choice[i] == choice[j]){
						printf("중복된 입력입니다. 입력받기를 종료합니다.\n");
						strcpy(temp,"break");
						choice[i] = 0;
						break;
					}
				}
			}
			if(strcmp(temp,"break") == 0) break;
			i++;
		}
		else if(strcmp(num, "6") == 0) {
			choice[i] = 6;
			if ( i > 0){
				for (int j = 0; j < i; j++){
					if (choice[i] == choice[j]){
						printf("중복된 입력입니다. 입력받기를 종료합니다.\n");
						strcpy(temp,"break");
						choice[i] = 0;
						break;
					}
				}
			}
			if(strcmp(temp,"break") == 0) break;
			i++;
		}		
		else if(strcmp(num, "7") == 0) {
			choice[i] = 7;
			if ( i > 0){
				for (int j = 0; j < i; j++){
					if (choice[i] == choice[j]){
						printf("중복된 입력입니다. 입력받기를 종료합니다.\n");
						strcpy(temp,"break");
						choice[i] = 0;
						break;
					}
				}
			}
			if(strcmp(temp,"break") == 0) break;
			i++;
		}
		else if(strcmp(num, "8") == 0) {
			choice[i] = 8;
			if ( i > 0){
				for (int j = 0; j < i; j++){
					if (choice[i] == choice[j]){
						printf("중복된 입력입니다. 입력받기를 종료합니다.\n");
						strcpy(temp,"break");
						choice[i] = 0;
						break;
					}
				}
			}
			if(strcmp(temp,"break") == 0) break;
			i++;
		}
		else {
			printf("잘못된 입력입니다.\n");
		}

		printf("\n계속 하시겠습니까? (Y/N) : ");
		fgets (ans, MAX, stdin);
		ans[strlen(ans) - 1] = '\0';
		if(strcasecmp(ans, "Y")==0) continue;
		else break;
	}
	return choice;
}
