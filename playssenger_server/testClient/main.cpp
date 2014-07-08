#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

int main()
{
	int clientSocket;
	struct sockaddr_in serverAddr;
	bzero((char *) &serverAddr, sizeof(serverAddr));
	serverAddr.sin_family = PF_INET;
	serverAddr.sin_addr.s_addr = inet_addr("165.132.121.42");
	serverAddr.sin_port = htons(7554);
	
	if((clientSocket = socket(PF_INET, SOCK_STREAM, 0))<0)
	{
		fprintf(stderr, "[ERROR] : SOCKET ERROR\n");
		return -1;
	}
	
	if(connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0)
	{
		fprintf(stderr, "[ERROR] : CONNECT ERROR\n");
		return -1;
	}
	printf("connected\n");
	
	int result = 0;
	char strBuffer[1024];
	for(;;)
	{
		bzero(strBuffer, 1024);
		scanf("%s", strBuffer);
		int len = strlen(strBuffer);
		if((result = write(clientSocket, strBuffer, len)) < 0)
		{
			fprintf(stderr, "[ERROR] : WRITE ERROR\n");
		}
		else
	{
		printf("%d sended!\n", result);
	}
	
	}
	getchar();

	char* buffer = "I`m sending message!\n";
	if((result = write(clientSocket, buffer, 21)) < 0)
	{
		fprintf(stderr, "[ERROR] : WRITE ERROR\n");
	}
	else
	{
		printf("%d sended!\n", result);
	}
	getchar();
	if(close(clientSocket) < 0)
	{
		fprintf(stderr, "[ERROR] : CLOSE ERROR\n");
		return -1;
	}
	return 0;
}
