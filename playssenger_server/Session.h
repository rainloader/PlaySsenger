#include <sys/socket.h>
#include <netinet/in.h>

#ifndef _SESSION_H
#define _SESSION_H

enum SessionState
{
	SS_CONNECTED, SS_LOGINED, SS_JOINED, SS_DISCONNECTED
};

class Session
{
public:
	Session(int sessionId, sockaddr_in addr);
	
	int GetSessionId() { return m_sessionId; }
	SessionState GetState() { return m_state; }
	void SetState(SessionState state) { m_state = state; }
private:
	SessionState m_state;
	int m_sessionId;	// session id equals to socket fd.
	sockaddr_in m_addr;	// socket addr
};

#endif
