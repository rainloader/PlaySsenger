#ifndef _NETWORKMANAGER_H
#define _NETWORKMANAGER_H

#define MAX_EVENT_NUM 500
#define NETWORK_THREAD_NUM 2

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
	void OnRead();
	int m_serverFd;
	int m_epollFd;
	int m_epollFdList[NETWORK_THREAD_NUM];
	epoll_event* m_epollEvent2DList[NETWORK_THREAD_NUM];
	epoll_event m_epollEvents[MAX_EVENT_NUM];
	std::map<int, Session> m_sessionMap;
};

#endif
