#define MAX_EVENT_NUM 500

#include "Session.h"
#include <sys/epoll.h>
#include <map>

class NetworkManager
{
public:
	NetworkManager();
	~NetworkManager();
	bool Initialize();
	void Run();
	
private:
	void OnEvent(int numOfEvent);
	int m_serverFd;
	int m_epollFd;
	epoll_event m_epollEvents[MAX_EVENT_NUM];
	bool Connect();
	std::map<int, Session> m_sessionMap;
};
