#pragma once

#define MAX 100
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//위치 입력 받고 1, 2, 3으로 리턴하는 함수
int place(){
	char num[MAX];
	printf("맛집의 위치를 선택해 주세요\n");
	while(1){
		printf("1.정문 2.후문 3.북아현동 :  ");
		
		fgets(num,MAX,stdin);
		num[strlen(num)-1]='\0';
		
		if(strcmp(num,"1")==0) return 1;
		else if(strcmp(num,"2")==0) return 2;
		else if(strcmp(num,"3")==0) return 3;
		else printf("잘못된 입력입니다. 다시 입력해 주세요.\n\n");
	}
}
