#ifndef _SESSION_H
#define _SESSION_H

#include "../common/Structures.h"

#include <sys/socket.h>
#include <netinet/in.h>
enum SessionState
{
	SS_CONNECTED, SS_LOGINED, SS_JOINED, SS_DISCONNECTED
};

struct Session
{
	Session(int sessionId, sockaddr_in addr);
	SessionState state;
	int sessionId;	// session id equals to socket fd.
	char buffer[MAX_BUFFER_LENGTH];
	char packetBuffer[MAX_PACKET_SIZE];
	int idxPacket;
	sockaddr_in addr;	// socket addr
};

#endif
