#include <sys/socket.h>
#include <netinet/in.h>

class Session
{
public:
	Session(int sessionId, sockaddr_in addr);

private:
	int m_sessionId;	// session id equals to socket fd.
	sockaddr_in m_addr;	// socket addr
};
