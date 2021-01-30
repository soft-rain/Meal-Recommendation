#pragma once
#define MAX 100
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "struct.h"
#include <time.h>

STORE* randoms(STORE *rs){
	int length=0, rannum;
	static STORE restore[1];
	for(int i=0; i<MAX; i++){
		if(strcmp(rs[i].name, "\0")==0)
			break;
		length++;
	}
	if(length!=0){
		srand(time(NULL));
		rannum=rand()%length;
		memcpy(&restore[0], &rs[rannum], sizeof(STORE));
	}
	return restore;
}
