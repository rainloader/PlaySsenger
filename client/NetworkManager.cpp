#include "NetworkManager.h"
#include "../common/Structures.h"
#include "../common/PacketProcessor.h"
#include "../common/Packets.h"

#include <strings.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define SERVER_ADDRESS "127.0.0.1"

void NetworkManager::Initialize()
{        
	if((socketFd = socket(PF_INET, SOCK_STREAM, 0))<0)
        {
                fprintf(stderr, "[ERROR] : SOCKET ERROR\n");
                exit(-1);
        }
	idxPacket = 0;
}

bool NetworkManager::Connect()
{
	struct sockaddr_in serverAddr;
        bzero((char *) &serverAddr, sizeof(serverAddr));
        serverAddr.sin_family = PF_INET;
        serverAddr.sin_addr.s_addr = inet_addr(SERVER_ADDRESS);
        serverAddr.sin_port = htons(PORT_NUM);

	if(connect(socketFd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0)
	{
		fprintf(stderr, "[ERROR] : CONNECT ERROR\n");
		return false;
	}
	printf("Connected");
	return true;
}

void NetworkManager::ReadAndDispatch()
{
	int result = 0;
	result = read(socketFd, readBuffer, MAX_BUFFER_LENGTH);

	PacketProcessor::ReadBuffer(idxPacket, packetBuffer, readBuffer, result);

	int protocol;
	Packet packet;
	int packetBodyLength;
	while(PacketProcessor::FetchPacket(protocol, packet.buffer, packetBodyLength, idxPacket, packetBuffer))
	{
		if(0 <= protocol && protocol < PT_MAX)
		{
			
		}
	}
}

