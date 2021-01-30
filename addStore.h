#pragma once
#define MAX 100
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "struct.h"

//식당 추가 함수
double addStore(STORE *s, ANSWER *a){
	int i, check, index=-1;
	double re;
	FILE *f_w;

	for(i=0; i<MAX; i++){
		if (strcmp(s[i].name,a[0].news.name)==0) index=i;
		if (strcmp(s[i].name,"\0")==0) break;
	}
	switch(a[0].newtype){
	case 1:
		a[0].news.type[0]='H';
		break;	
	case 2:
		a[0].news.type[0]='B';
		break;	
	case 3:
		a[0].news.type[0]='I';
		break;	
	case 4:
		a[0].news.type[0]='F';
		break;	
	case 5:
		a[0].news.type[0]='Y';
		break;	
	case 6:
		a[0].news.type[0]='J';
		break;	
	case 7:
		a[0].news.type[0]='A';
		break;	
	case 8:
		a[0].news.type[0]='G';
		break;	
	default:
		printf("잘못된 입력입니다.");
		break;	
	}
	if (index<0||index==99){
		memcpy(&s[i], &a[0].news, sizeof(STORE));
		re = 10.0; //없을 때
	}
	else{
		re = 11.0; //있을 때
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
