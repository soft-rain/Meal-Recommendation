#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <signal.h>
#include "database.h"
#include "random.h"
#include "sort.h"
#include "struct.h"

#define PORT 13912
#define BUFFER_SIZE 8388608
#define BUFF_SIZE 100

#define LISTEN_QUEUE_SIZE 5

STORE* sock2dat(ANSWER *a){
	return database(a);
}

STORE* dat2sock(STORE* s){
	return s;
}

STORE* dat2sort(STORE *s){
	return sort(s);
}

STORE* dat2rand(STORE *s){
	return randoms(s);
}

STORE* sort2sock(STORE *s){
	return s;
}

STORE* rand2sock(STORE *s){
	return s;
}

void childHandler(int signal)
{
	int status;
	pid_t spid;
	
	pid_t waitpid(pid_t pid, int *status, int options);
	//-1::어떠한 child process모두 다 받는다. WNOHANG :: 자식 프로세스가 종료되지 않아도 부모는 자신할 일 한다.
	while((spid = waitpid(-1, &status, WNOHANG)) > 0)
	{
		printf("자식프로세스 wait한 결과\n");
		printf("=============================\n");
		printf("PID        :%d\n",spid);
		printf("Exit Value : %d\n", WEXITSTATUS(status));
		printf("Exit Stat  : %d\n", WIFEXITED(status));
	}
}

int main(){
	//childHandler 함수가 SIGCHLD 시그널을 처리할 수 있도록 시그널 설치

	signal(SIGCHLD, (void *)childHandler);
	
	struct sockaddr_in listenSocket;
	
	memset(&listenSocket, 0, sizeof(listenSocket));

	listenSocket.sin_family = AF_INET;
	listenSocket.sin_addr.s_addr = htonl(INADDR_ANY);
	listenSocket.sin_port = htons(PORT);
	
	int listenFD = socket(AF_INET, SOCK_STREAM, 0);
	int connectFD;

	pid_t pid;
	if(bind(listenFD, (struct sockaddr *) &listenSocket, sizeof(listenSocket))== -1){
		printf("Can not bind. \n");
		return -1;
	}

	if (listen(listenFD, LISTEN_QUEUE_SIZE) == -1){
		printf("Listen fail.\n");
		return -1;
	}

	printf("Waiting for clients....\n");
	
	while(1)
	{
		struct sockaddr_in connectSocket, peerSocket;
		socklen_t connectSocketLength = sizeof(connectSocket);
		while((connectFD = accept(listenFD, (struct sockaddr*)&connectSocket, (socklen_t *)&connectSocketLength)) >= 0)
		{
			getpeername(connectFD, (struct sockaddr*)&peerSocket, &connectSocketLength);

			char peerName[sizeof(peerSocket.sin_addr) + 1] = {0};
			sprintf(peerName, "%s", inet_ntoa(peerSocket.sin_addr));
		
			//접속이 안되었을 때는 출력x
			if(strcmp(peerName, "0.0.0.0")!=0)
			{
				printf("Client : %s\n", peerName);
			}

			if(connectFD < 0)
			{
				printf("Server: accept failed \n");
				exit(0);
			}
			//클라이언트가 접속할 때마다 fork를 통해 child process를 생성해 echo를 발생.
			pid = fork();
					//자식 서버일 때
			if(pid ==  0)
			{

				//리스닝 소켓은 닫아준다.
				close(listenFD);
				ANSWER ansBuff[1];
				ANSWER ans[MAX];
				STORE* dat;
				
				recv(connectFD, ansBuff, BUFFER_SIZE, 0);
//client에서 받은 이후				
				memcpy(&ans[0],&ansBuff[0],sizeof(ANSWER)*5);
				//ans = ansBuff;
				
				STORE* temps;
				STORE* result;
				dat = sock2dat(ans);
				switch(ans[0].auchoice){
				case 1:{
					temps = dat2sort(dat);
					result = sort2sock(temps);
					send(connectFD, result, BUFFER_SIZE,0);
					break;
					}
				case 2:{
					temps = dat2rand(dat);
					result = rand2sock(temps);
					//printf("%s\n",result[0].type);
					send(connectFD, result, BUFFER_SIZE,0);
					break;
					}
				case 3: case 4: {
					result = dat2sock(dat);
					send(connectFD, result, BUFFER_SIZE,0);
					break;
					}
				}
	
				//클라이언트가 종료되면 해당 자식 프로세스의 커넥팅 소켓도 종료
				close(connectFD);
				return 0; //혹은 exit(0);이용
			}
			//부모 서버라면 커넥팅 소켓을 닫아준다.
			else{
				close(connectFD);
			}
		}
		close(listenFD);
		return 0;
		}

}
