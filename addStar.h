#pragma once
#define MAX 100
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "struct.h"

//별점 추가 함수
double addStar(STORE *s, ANSWER *a){
	int i, check, index=-1;
	FILE *f_w;
	double re;

	for(i=0; i<MAX; i++){
		if (strcmp(s[i].name,a[0].news.name)==0){
			index=i;
			break;
		}
	}
	
	if (index<0||index==99) re=10.0; //없을 때
	else{
		s[index].star = ((double)a[0].news.star + s[index].star)/2;		
		re=s[index].star; //있을 때
	}
	
	switch(a[0].place){
	case 1: {
		if((f_w=fopen("dataJ.txt","w"))==NULL){
			printf("Cannot open the data file!\n");
			exit(0);
		}
		break;
		} //end of case 1

	case 2: {
		if((f_w=fopen("dataH.txt","w"))==NULL){
			printf("Cannot open the data file!\n");
			exit(0);
		}
		break;
		} //end of case 2

	case 3: {
		if((f_w=fopen("dataB.txt","w"))==NULL){
			printf("Cannot open the data file!\n");
			exit(0);
		}
		break;
		} //end of case 3
	}//end of writeswitch

	for(i=0; i<MAX; i++){
		check=strcmp(s[i].name, "\0");
		if(check==0) break;
		fprintf(f_w,"%s %s %s ",s[i].name,s[i].menu,s[i].type);		
		fprintf(f_w,"%.1lf\n",s[i].star);
	}
	fclose(f_w); //end of file write
	return re;

}
