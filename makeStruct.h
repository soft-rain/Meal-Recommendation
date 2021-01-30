#pragma once

#define MAX 100
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "food.h"
#include "struct.h"

STORE* makeStruct(int (*f), STORE *s){
	int index = 0, sendI = 0;
	static STORE send[MAX] = {"\0", "\0", "\0", 0.0};

	while(1){
		if(f[index]==0)
			break;
		switch(f[index]){
		case 1:
			for(int i = 0; i < MAX; i++){
				if (strcmp(s[i].type,"H") == 0){
					memcpy(&send[sendI], &s[i], sizeof (STORE));
					sendI++;
				}
			}
			break;
		case 2:
			for(int i = 0; i < MAX; i++){
				if (strcmp(s[i].type,"B") == 0){
					memcpy(&send[sendI], &s[i], sizeof (STORE));
					sendI++;
				}
			}
			break;
		case 3:
			for(int i = 0; i < MAX; i++){
				if (strcmp(s[i].type,"I") == 0){
					memcpy(&send[sendI], &s[i], sizeof (STORE));
					sendI++;
				}
			}
			break;
		case 4:
			for(int i = 0; i < MAX; i++){
				if (strcmp(s[i].type,"F") == 0){
					memcpy(&send[sendI], &s[i], sizeof (STORE));
					sendI++;
				}
			}
			break;
		case 5:
			for(int i = 0; i < MAX; i++){
				if (strcmp(s[i].type,"Y") == 0){
					memcpy(&send[sendI], &s[i], sizeof (STORE));
					sendI++;
				}
			}
			break;
		case 6:
			for(int i = 0; i < MAX; i++){
				if (strcmp(s[i].type,"J") == 0){
					memcpy(&send[sendI], &s[i], sizeof (STORE));
					sendI++;
				}
			}
			break;
		case 7:
			for(int i = 0; i < MAX; i++){
				if (strcmp(s[i].type,"A") == 0){
					memcpy(&send[sendI], &s[i], sizeof (STORE));
					sendI++;
				}
			}
			break;
		case 8:
			for(int i = 0; i < MAX; i++){
				if (strcmp(s[i].type,"G") == 0){
					memcpy(&send[sendI], &s[i], sizeof (STORE));
					sendI++;
				}
			}
			break;
		default:
			printf("problem\n");
			break;
		}
		index++;
	}
	return send;
}

