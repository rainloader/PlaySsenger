#ifndef _SESSION_H
#define _SESSION_H

#include <sys/socket.h>
#include <netinet/in.h>

#define MAX_BUFFER_LENGTH 1024

enum SessionState
{
	SS_CONNECTED, SS_LOGINED, SS_JOINED, SS_DISCONNECTED
};

struct Session
{
	Session(int sessionId, sockaddr_in addr);
	SessionState state;
	int sessionId;	// session id equals to socket fd.
	unsigned char buffer[MAX_BUFFER_LENGTH];
	sockaddr_in addr;	// socket addr
};

#endif
