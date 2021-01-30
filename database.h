#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "makeStruct.h"
#include "addStar.h"
#include "addStore.h"

STORE* database(ANSWER *a){
	FILE *fd;
	int i;
	static STORE* s;
	s = (STORE*) malloc(sizeof(STORE)*MAX);
	static STORE re[1] = {"\0", "\0", "\0", 0.0};

	switch(a[0].place){
		case 1 : {
			fd = fopen("dataJ.txt", "r");
			break;
			}
		case 2 : fd = fopen("dataH.txt", "r"); break;
		case 3 : fd = fopen("dataB.txt", "r"); break;
		dafault : printf("place error\n");
	}

	for (i=0; i<MAX; i++){
		fscanf(fd, "%s %s %s", s[i].name, s[i].menu, s[i].type);
		fscanf(fd, "%lf", &s[i].star);
	}
	fclose(fd);

	if (a[0].auchoice==1||a[0].auchoice==2){	
		STORE *rs = makeStruct(a[0].afood, s);	
		return rs;
	}
	else if (a[0].auchoice==3){
		re[0].star=addStar(s, a);
		return re;
	}
	else if (a[0].auchoice==4){
		re[0].star=addStore(s, a);
		return re;
	}
	free(s);
}
