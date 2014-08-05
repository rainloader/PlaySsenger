#include "NetworkManager.h"
#include "../common/Structures.h"
#include "../common/PacketProcessor.h"
#include "../common/Packets.h"
#include "PacketDispatcher.h"

#include <strings.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>

#define SERVER_ADDRESS "127.0.0.1"

NetworkManager* NetworkManager::sm_instance = NULL;

NetworkManager& NetworkManager::GetInstance()
{
	if(sm_instance == NULL)
		sm_instance = new NetworkManager();
	return *sm_instance;
}

void NetworkManager::Initialize()
{        
	if((m_socketFd = socket(PF_INET, SOCK_STREAM, 0))<0)
        {
                fprintf(stderr, "[ERROR] : SOCKET ERROR\n");
                exit(-1);
        }
	m_idxPacket = 0;
}

bool NetworkManager::Connect()
{
	struct sockaddr_in serverAddr;
        bzero((char *) &serverAddr, sizeof(serverAddr));
        serverAddr.sin_family = PF_INET;
        serverAddr.sin_addr.s_addr = inet_addr(SERVER_ADDRESS);
        serverAddr.sin_port = htons(PORT_NUM);

	if(connect(m_socketFd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0)
	{
		fprintf(stderr, "[ERROR] : CONNECT ERROR\n");
		return false;
	}
	printf("Connected\n");
	return true;
}

void NetworkManager::ReadAndDispatch()
{
	int result = 0;
	result = read(m_socketFd, m_readBuffer, MAX_BUFFER_LENGTH);

	PacketProcessor::ReadBuffer(m_idxPacket, m_packetBuffer, m_readBuffer, result);

	int protocol;
	Packet packet;
	int packetBodyLength;
	while(PacketProcessor::FetchPacket(protocol, packet.buffer, packetBodyLength, m_idxPacket, m_packetBuffer))
	{
		if(0 <= protocol && protocol < PT_MAX)
		{
			g_handlerTable[protocol](packet.buffer, packetBodyLength);
		}
	}
}

void NetworkManager::Write(const Packet& packet)
{
	int result = write(m_socketFd, packet.buffer, packet.size);
	if(result < 0)
	{
		fprintf(stderr, "[ERROR] write() ERROR : %s\n", strerror(errno));
		exit(1);
	}
}

void NetworkManager::SendMessage(char* message, int strlen)
{
	Packet packet;
	char m_packetBuffer[MAX_PACKET_SIZE];
	int packetSize;
	S_PT_MESSAGE data;
	data.sessionId = m_sessionId;
	data.message.resize(strlen);
	data.message.assign(message, message + strlen);
	MAKE_PT_MESSAGE(packet.buffer, packet.size, data);
	printf("%s %d\n", message, strlen);
	for(int i=0; i<packet.size; i++)
	{
		printf("%c", packet.buffer[i]);
	}
	printf("%s %d\n", packet.buffer, packet.size);
	Write(packet);
}

