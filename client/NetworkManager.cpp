#include "NetworkManager.h"
#include "../common/Structures.h"

#include <strings.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define SERVER_ADDRESS "127.0.0.1"

void NetworkManager::Initialize()
{
	struct sockaddr_in serverAddr;
        bzero((char *) &serverAddr, sizeof(serverAddr));
        serverAddr.sin_family = PF_INET;
        serverAddr.sin_addr.s_addr = inet_addr(SERVER_ADDRESS);
        serverAddr.sin_port = htons(PORT_NUM);
/*
        if((clientSocket = socket(PF_INET, SOCK_STREAM, 0))<0)
        {
                fprintf(stderr, "[ERROR] : SOCKET ERROR\n");
                return -1;
        }*/
}

void NetworkManager::Connect()
{
}

void NetworkManager::ReadAndDispatch()
{
}

