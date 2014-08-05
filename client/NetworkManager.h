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
	void Write(const Packet& packet);
	void SendMessage(char* message, int strlen);
	int GetSessionId() { return this->m_sessionId; }
	void SetSessionId(int sessionId) { this->m_sessionId = sessionId; }

private:
	int m_sessionId;
	int m_socketFd;
	char m_packetBuffer[MAX_PACKET_SIZE];
	char m_readBuffer[MAX_BUFFER_LENGTH];
	int m_idxPacket;

	static NetworkManager* sm_instance;
};

#endif
