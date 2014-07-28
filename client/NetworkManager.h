#ifndef _NETWORKMANAGER_H
#define _NETWORKMANAGER_H

#include "../common/Structures.h"

class NetworkManager
{
public:
	void Initialize();
	bool Connect();
	void ReadAndDispatch();

private:
	int sessionId;
	int socketFd;
	char packetBuffer[MAX_PACKET_SIZE];
	char readBuffer[MAX_BUFFER_LENGTH];
	int idxPacket;
};

#endif
