#define MAX_EVENT_NUM 500

#include "Session.h"
#include <sys/epoll.h>
#include <map>

#ifndef _NETWORKMANAGER_H
#define _NETWORKMANAGER_H

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
	std::map<int, Session> m_sessionMap;
};

#endif
