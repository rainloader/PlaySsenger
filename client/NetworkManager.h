#ifndef _NETWORKMANAGER_H
#define _NETWORKMANAGER_H

#include "../common/Structures.h"

class NetworkManager
{
public:
	static NetworkManager& GetInstance();
	void Initialize();
	bool Connect();
	void ReadAndDispatch();
	void SendMessage(char* message, int strlen);
	int GetSessionId() { return this->sessionId; }
	void SetSessionId(int sessionId) { this->sessionId = sessionId; }

private:
	int sessionId;
	int socketFd;
	char packetBuffer[MAX_PACKET_SIZE];
	char readBuffer[MAX_BUFFER_LENGTH];
	int idxPacket;

	static NetworkManager* sm_instance;
};

#endif
