#include "NetworkManager.h"
#include "../Common/Structures.h"

#define SERVER_ADDRESS "127.0.0.1"

void NetworkManager::Initialize()
{
	struct sockaddr_in serverAddr;
        bzero((char *) &serverAddr, sizeof(serverAddr));
        serverAddr.sin_family = PF_INET;
        serverAddr.sin_addr.s_addr = inet_addr(SERVER_ADDRESS);
        serverAddr.sin_port = htons(PORT);

        if((clientSocket = socket(PF_INET, SOCK_STREAM, 0))<0)
        {
                fprintf(stderr, "[ERROR] : SOCKET ERROR\n");
                return -1;
        }NetworkManager::Connect()
{
}

void NetworkManager::ReadAndDispatch()
{
}

void NetworkManager::WritePacket(Packet packet)
{
}
