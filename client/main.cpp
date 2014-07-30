#include "ClientCore.h"

#include "NetworkManager.h"

#include "../common/Packets.h"
#include "../common/Structures.h"
#include "../common/PacketProcessor.h"

#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

int main()
{
	ClientCore& clientCore = ClientCore::GetInstance();
	clientCore.Run();
/*
	NetworkManager& nm = NetworkManager::GetInstance();
	nm.Initialize();
	nm.Connect();
for(;;)
	nm.ReadAndDispatch();
/*
	int sessionId;
	int clientSocket;
	struct sockaddr_in serverAddr;
	bzero((char *) &serverAddr, sizeof(serverAddr));
	serverAddr.sin_family = PF_INET;
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	//serverAddr.sin_addr.s_addr = inet_addr("165.132.121.42");
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
	char packetBuffer[1024];
	char readBuffer[1024];
	int protocol;
	int packetBodyLength;
	int idxPacket = 0;

	result = read(clientSocket, readBuffer, 1024);
	
	Packet packet;
	PacketProcessor::ReadBuffer(idxPacket, packetBuffer, readBuffer, result);
	
	while(PacketProcessor::FetchPacket(protocol, packet.buffer, packetBodyLength, idxPacket, packetBuffer))
	{
		if(0 <= protocol && protocol < PT_MAX)
		{
			if(protocol == PT_SESSION_U)
			{
				S_PT_SESSION_U structSession;
				READ_PT_SESSION_U(packet.buffer, structSession);
				sessionId = structSession.sessionId;
			}
		}
	}

	printf("my session id is %d\n", sessionId);

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
		if(strcmp(strBuffer, "exit") == 0)
			break;
	}

	if(close(clientSocket) < 0)
	{
		fprintf(stderr, "[ERROR] : CLOSE ERROR\n");
		return -1;
	}*/
	return 0;
}
