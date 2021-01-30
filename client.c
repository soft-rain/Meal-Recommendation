#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>
#include "struct.h"
#include "food.h"
#include "place.h"

#define PORT 13912
#define BUFFER_SIZE 8388608
#define BUFF_SIZE 100

int count_Hanguel(char *string)
{
	int i = 0, count_han = 0, strLength = strlen(string);

	for ( ; i < strLength ; i++)
	{
		if( ((string[i] & 0xE0) == 0xE0) &&  ((string[i+1] & 0x80) == 0x80) && ((string[i+2] & 0x80) == 0x80))
		{
			++i;
			++i;
			count_han++;
		}
	}
	return count_han;
}

int print_space(int number)
{
	int i = 0;
	for ( ; i <= number ; i++)
		printf(" ");
	return 0;

}int main()
{

	struct sockaddr_in connectSocket;

	memset(&connectSocket, 0, sizeof(connectSocket));

	connectSocket.sin_family = AF_INET;
	connectSocket.sin_addr.s_addr = inet_addr("127.0.0.1");
	connectSocket.sin_port = htons(PORT);
	int j;
	int connectFD = socket(AF_INET, SOCK_STREAM, 0);
	j = (connect(connectFD, (struct sockaddr*) &connectSocket, sizeof(connectSocket)));
	if(j == -1){
		printf("%d",j);
		printf("Cannot connect.\n");
		return -1;
	}

	else
	{
		ANSWER sendBuffer[MAX];		//server에게 보내는 버퍼
		STORE* receiveBuffer;		//server에게서 받는 버퍼
		receiveBuffer = (STORE*)malloc(BUFFER_SIZE);
		ANSWER a[1];
		int* foodTemp;
		foodTemp = (int*) malloc(BUFFER_SIZE);
		char num[MAX];
		char temp[MAX];
		char star[MAX];
		printf("=======================================================================================================\n");
		printf("               |      |     |            |         |           |       |    |                      \n");
		printf("               |      |     |           / \\        |           |       |    |  \n");
		printf("               |______|   --|          /   \\       |        -------    |____|\n");
		printf("               |      |     |         /     \\      |          / \\      |    | \n");
		printf("               |______|     |        /       \\     |         /   \\     |    | \n");
		printf("                        |                ___________        /     \\ ________\n");
		printf("                       / \\                         |                        |\n");
		printf("                      /   \\                        |                        |\n");
		printf("                     /     \\                       |                        | \n");
		printf("                    /       \\                      |                        | \n");
		printf("=======================================================================================================\n");
		printf("		        	   벗들의 식사는 우리가 책임집니다!                           \n");
		printf("-------------------------------------------------------------------------------------------------------\n");
		printf("		   	          	      벗.식.책.		               	              \n");
		printf("=======================================================================================================\n");
		
		printf("\n◈◈◈◈◈◈실행시킬 작업의 번호를 입력해주세요.◈◈◈◈◈◈\n");
		printf("1. 별점 순서로 맛집  출력\n");
		printf("2. 랜덤으로 맛집  출력\n");
		printf("3. 별점 추가\n");
		printf("4. 새로운 맛집  추가\n");
		
		fgets(num, MAX, stdin);
		printf("\n");
		num [strlen(num) - 1] = '\0';

		if (strcmp(num, "1") == 0) a[0].auchoice = 1;
		else if (strcmp(num, "2") == 0) a[0].auchoice = 2;
		else if (strcmp(num, "3") == 0) a[0].auchoice = 3;
		else if (strcmp(num, "4") == 0) a[0].auchoice = 4;
		else a[0].auchoice = 0;
		
		switch(a[0].auchoice){
		case 1:{
			a[0].place = place();
			foodTemp = food();
			a[0] = afoodArray(foodTemp, a[0]);	
			memcpy(&sendBuffer[0], &a[0], sizeof(ANSWER)*MAX);
			send(connectFD, sendBuffer, BUFFER_SIZE, 0);
			recv(connectFD, receiveBuffer, BUFFER_SIZE, 0);
			printf("-------------------------------------------------------------------------------------------------------\n");
			printf("맛집 이름\t\t     | 대표 메뉴\t\t   | 종류\t\t\t| 별점\t\t\n");	
			printf("-------------------------------------------------------------------------------------------------------\n");
			if(strcmp(receiveBuffer[0].type,"\0")==0) printf("조건에 맞는 맛집이 없습니다!\n");
			else{
			for(int i = 0; i < MAX; i++){
			if (strcmp(receiveBuffer[i].type,"\0")==0) break;
				printf("%-30s", receiveBuffer[i].name);
				print_space(count_Hanguel(receiveBuffer[i].name));
					
				printf("%-29s", receiveBuffer[i].menu);
				print_space(count_Hanguel(receiveBuffer[i].menu));
				if(strcmp(receiveBuffer[i].type, "H") == 0) 
					printf("한식\t\t\t");
				else if(strcmp(receiveBuffer[i].type, "B") == 0)
					printf("분식\t\t\t");
				else if(strcmp(receiveBuffer[i].type, "I") == 0)
					printf("일식\t\t\t");
				else if(strcmp(receiveBuffer[i].type, "F") == 0)
					printf("패스트푸드 \t\t");
				else if(strcmp(receiveBuffer[i].type, "Y") == 0)
					printf("양식\t\t\t");
				else if(strcmp(receiveBuffer[i].type, "J") == 0)
					printf("중식\t\t\t");
				else if(strcmp(receiveBuffer[i].type, "A") == 0)
					printf("아시안\t\t\t");
				else if(strcmp(receiveBuffer[i].type, "G") == 0)
					printf("기타\t\t\t");
				printf("  %-11.1lf\n", receiveBuffer[i].star);
			}
			printf("\n");
			}
			break;
		}
		case 2:{
			a[0].place = place();
			foodTemp = food();
			a[0] = afoodArray(foodTemp, a[0]);
			memcpy(&sendBuffer[0], &a[0], sizeof(ANSWER)*MAX);
			send(connectFD, sendBuffer, BUFFER_SIZE, 0);
			recv(connectFD, receiveBuffer, BUFFER_SIZE, 0);
			printf("-------------------------------------------------------------------------------------------------------\n");
			printf("맛집 이름\t\t     | 대표 메뉴\t\t  | 종류\t\t\t| 별점\t\t\n");	
			printf("-------------------------------------------------------------------------------------------------------\n");
			if(strcmp(receiveBuffer[0].type,"\0")==0) printf("조건에 맞는 맛집이 없습니다!\n");
			else{
			for(int i = 0; i < MAX; i++){
			if (strcmp(receiveBuffer[i].type,"\0")==0) break;
				printf("%-30s", receiveBuffer[i].name);
				print_space(count_Hanguel(receiveBuffer[i].name));
					
				printf("%-28s", receiveBuffer[i].menu);
				print_space(count_Hanguel(receiveBuffer[i].menu));
				
				if(strcmp(receiveBuffer[i].type, "H") == 0) 
					printf("한식\t\t\t");
				else if(strcmp(receiveBuffer[i].type, "B") == 0)
					printf("분식\t\t\t");
				else if(strcmp(receiveBuffer[i].type, "I") == 0)
					printf("일식\t\t\t");
				else if(strcmp(receiveBuffer[i].type, "F") == 0)
					printf("패스트푸드 \t\t");
				else if(strcmp(receiveBuffer[i].type, "Y") == 0)
					printf("양식\t\t\t");
				else if(strcmp(receiveBuffer[i].type, "J") == 0)
					printf("중식\t\t\t");
				else if(strcmp(receiveBuffer[i].type, "A") == 0)
					printf("아시안\t\t\t");
				else if(strcmp(receiveBuffer[i].type, "G") == 0)
					printf("기타\t\t\t");
				printf("  %-10.1lf\n", receiveBuffer[i].star);
			}
			printf("\n");}
			break;
		}	
		case 3:{
			a[0].place = place();
			printf("\n맛집 이름을 입력하세요.\n");
			fgets(a[0].news.name, MAX, stdin);
			a[0].news.name[strlen(a[0].news.name)-1] = '\0';
			while(1){
				printf("\n별점을 0부터 5까지의 정수로 입력해 주세요 : ");
				fgets(star, MAX, stdin);
				star[strlen(star) - 1] = '\0';
				
				if(strcmp(star,"0") == 0){
					a[0].news.star = 0;
					break;
				}
				else if(strcmp(star,"1") == 0){ 
					a[0].news.star = 1;
					break;
				}
				else if(strcmp(star,"2") == 0) {
					a[0].news.star = 2;
					break;
				}
				else if(strcmp(star,"3") == 0){ 
					a[0].news.star = 3;
					break;
				}
				else if(strcmp(star,"4") == 0){ 
					a[0].news.star = 4;
					break;
				}
				else if(strcmp(star,"5") == 0){ 
					a[0].news.star = 5;
					break;
				}
				else
					printf("잘못된 입력입니다.\n");
			}		
			free(foodTemp);
			foodTemp = NULL;
			memcpy(&sendBuffer, &a, sizeof(ANSWER));
			send(connectFD, sendBuffer, BUFFER_SIZE, 0);
			recv(connectFD, receiveBuffer, BUFFER_SIZE, 0);
			if (receiveBuffer[0].star == 10.0) printf("해당 맛집은 없습니다.\n");
			else {
				printf("\n맛집%s의 수정된 별점은 %.1lf점입니다.\n",a[0].news.name, receiveBuffer[0].star);	
			}
			break;
		}
		case 4:{
			a[0].place = place();
			printf("\n맛집 이름을 입력하세요.\n");
			fgets(a[0].news.name, MAX, stdin);
			a[0].news.name[strlen(a[0].news.name)-1] = '\0';
			printf("\n대표 메뉴를 입력하세요.\n");
			fgets(a[0].news.menu, MAX, stdin);
			a[0].news.menu[strlen(a[0].news.menu)-1] = '\0';
			while(1){
				printf("\n별점을 0부터 5까지의 정수로 입력해 주세요 : ");
				fgets(star, MAX, stdin);
				star[strlen(star) - 1] = '\0';
				
				if(strcmp(star,"0") == 0){
					a[0].news.star = 0;
					break;
				}
				else if(strcmp(star,"1") == 0){ 
					a[0].news.star = 1;
					break;
				}
				else if(strcmp(star,"2") == 0) {
					a[0].news.star = 2;
					break;
				}
				else if(strcmp(star,"3") == 0){ 
					a[0].news.star = 3;
					break;
				}
				else if(strcmp(star,"4") == 0){ 
					a[0].news.star = 4;
					break;
				}
				else if(strcmp(star,"5") == 0){ 
					a[0].news.star = 5;
					break;
				}
				else
					printf("잘못된 입력입니다.\n");
			}
			while(1){
				printf("\n음식의 종류를 입력하세요.\n");
				printf("1.한식 2.분식 3.일식 4.패스트푸드 5.양식 6.중식 7.아시안 8.기타 : ");
					
				fgets(temp, MAX, stdin);
				temp[strlen(temp) - 1] = '\0';
				if(strcmp(temp,"1") == 0){
					a[0].newtype = 1;
					break;
				}
				else if(strcmp(temp, "2") == 0){ 
					a[0].newtype = 2;
					break;
				}
				else if(strcmp(temp, "3") == 0){ 
					a[0].newtype = 3;
					break;
				}
				else if(strcmp(temp, "4") == 0){ 
					a[0].newtype = 4;
					break;
				}
				else if(strcmp(temp, "5") == 0){ 
					a[0].newtype = 5;
					break;
				}
				else if(strcmp(temp, "6") == 0){ 
					a[0].newtype = 6;
					break;
				}

				else if(strcmp(temp, "7") == 0){ 
					a[0].newtype = 7;
					break;
				}

				else if(strcmp(temp, "8") == 0){ 
					a[0].newtype = 8;
					break;
				}
				else{
					printf("잘못된 입력입니다.\n");				
				}
			}

			memcpy(&sendBuffer, &a, sizeof(ANSWER)*2);
			send(connectFD, sendBuffer, BUFFER_SIZE, 0);	
			recv(connectFD, receiveBuffer, BUFFER_SIZE, 0);
			if (receiveBuffer[0].star == 10.0) printf("\n맛집 %s을(를) 추가합니다.\n",a[0].news.name);
			else printf("\n해당 맛집은 이미 있습니다.\n");	
			break;
		}
		default:{
			printf("잘못된 입력입니다.\n");
			exit(0);
		}
		}

		printf("-------------------------------------------------------------------------------------------------------\n");
		printf("					벗.식.책.을 종료합니다.\n");
		printf("=======================================================================================================\n");
		
		free(receiveBuffer);
		receiveBuffer = NULL;
		fputs((char*)&receiveBuffer, stdout);
		fflush(stdout);
		close(connectFD);
		return 0;
	}
}
