#include "NetworkManager.h"

#include "SpinLock.h"
#include "../common/Structures.h"
#include "../common/Packets.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#define PORT_NUM 7554

int g_networkThreadCount = 0;
SpinLock g_networkThreadCountLock = SpinLock();

NetworkManager::NetworkManager() : m_serverFd(0)
{

}

NetworkManager::~NetworkManager()
{
	for(int i=0; i<NETWORK_THREAD_NUM; i++)
	{
		delete m_epollEvent2DList[i];
	}
}

bool NetworkManager::Initialize()
{
	// 1. socket
	if((m_serverFd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
	{
		fprintf(stderr, "[ERROR] : SOCKET ERROR\n");
		return false;
	}

	// 2. bind
	struct sockaddr_in server_addr;
	bzero((char *) &server_addr, sizeof(server_addr));
	server_addr.sin_family		= PF_INET;
	server_addr.sin_addr.s_addr	= INADDR_ANY;
	server_addr.sin_port		= htons(PORT_NUM);
	if((bind(m_serverFd, (struct sockaddr*)&server_addr, sizeof(server_addr))) < 0)
	{
		fprintf(stderr, "[ERROR] : BIND ERROR\n");
		exit(-1);
	}

	// 3. listen
	if(listen(m_serverFd, 10) < 0)
	{
		fprintf(stderr, "[ERROR] : LISTEN ERROR %d\n", errno);
		exit(-1);
	} 

	printf("Socket Init Success\n");



	for(int i=0; i<NETWORK_THREAD_NUM; i++)
	{
		// Prepare epoll process
		if((m_epollFdList[i] = epoll_create(1)) < 0)
		{
			fprintf(stderr, "[ERROR] : EPOLL CREATE ERROR\n");
		}

		m_epollEvent2DList[i] = new epoll_event[MAX_EVENT_NUM];

		printf("epoll Create Success\n");
	}

	struct epoll_event epollEvent;

	epollEvent.events = EPOLLIN | EPOLLOUT | EPOLLERR;
	epollEvent.data.fd = m_serverFd;

	// register server fd to epoll
	if(epoll_ctl(m_epollFdList[m_serverFd%NETWORK_THREAD_NUM], EPOLL_CTL_ADD, m_serverFd, &epollEvent) < 0)
	{
		fprintf(stderr, "[ERROR] : EPOLL CTL ERROR\n");
		exit(-1);
	}

	return true;
}

void NetworkManager::Run()
{
	int threadId;
	struct epoll_event events[100];
	int numOfEvent, n;

	g_networkThreadCountLock.Lock();
	threadId = g_networkThreadCount++;
	g_networkThreadCountLock.Unlock();

	for(;;)
	{
		numOfEvent = epoll_wait(m_epollFdList[threadId], m_epollEvent2DList[threadId], 100, 2000);

		//printf("NW thread %d\n", threadId);
		if(numOfEvent < 0){	
			// critical error
			fprintf(stderr, "[ERROR] epoll_wait() ERROR : %s\n", strerror(errno));
			exit(1);
		}

		if(numOfEvent == 0)
		{
			continue;
		}

		//printf("NT %d activated\n", TC);
		OnEvent(numOfEvent, threadId);
	}
	close(m_serverFd);
	for(int i=0; i<NETWORK_THREAD_NUM; i++)
		close(m_epollFdList[i]);
}

void NetworkManager::OnEvent(int numOfEvent, int threadId)
{
	int strLen = 0;
	char buffer[1024];
	for(int i=0; i<numOfEvent; i++)
	{
		int eventFd = m_epollEvent2DList[threadId][i].data.fd;
		if(eventFd == m_serverFd) // when clients attempt to connect
		{
			OnConnect();
		}
		else	// when client request service
		{
			Session* pSession = m_pSessionMap[eventFd];
			strLen = read(eventFd, pSession->buffer, MAX_BUFFER_LENGTH); // Read client request
			if(strLen == 0)	// Client request to disconnect
			{
				epoll_ctl(m_epollFdList[threadId], EPOLL_CTL_DEL, m_epollEvent2DList[threadId][i].data.fd, NULL); // remove client info from epoll instance
				close(eventFd); // disconnecd
				delete pSession;
				m_pSessionMap.erase(eventFd);
				printf("%d session disconnected\n", eventFd);
			}
			else if(strLen < 0)
			{
	/*			if(errno != EWOULDBLOCK && errno != EAGAIN)
				{
					// critical error
					fprintf(stderr, "[ERROR] read() ERROR : %s\n", strerror(errno));
					exit(1);
				}*/
			}
			else
			{
				__uint32_t events = m_epollEvent2DList[threadId][i].events;
				if(events & EPOLLIN)
				{
					//					OnRead(int id, int strLen);
				}
				if(events & EPOLLOUT)
				{
					printf("EPOLLOUT\n");
				}
				if(events & EPOLLERR)
				{
					fprintf(stderr, "[ERROR] : EPOLL EVENT ERROR\n");
					exit(-1);				
				}
				pSession->buffer[strLen] = '\0';
				printf("%s\n", pSession->buffer);

				// service that someelse
			}
		}
	}
}

void NetworkManager::OnConnect()
{
	// accept client
	// register new client socket to epoll instance
	int clientFd;
	sockaddr_in clientAddr;
	socklen_t addrLen = 0;
	// #4. accept
	if((clientFd = accept(m_serverFd, (struct sockaddr*)&clientAddr, &addrLen)) < 0)
	{
		fprintf(stderr, "[ERROR] : ACCEPT ERROR\n");
		exit(-1);
	}
	// make socket non-blocking
	int flags = fcntl(clientFd, F_GETFL, 0);
	if(flags < 0)
	{
		fprintf(stderr, "[ERROR] : MAKE SOCKET NONBLOCKING ERROR\n");
		exit(-1);
	}
	flags = fcntl(clientFd, F_SETFL, flags | O_NONBLOCK);

	Session* pSession = new Session(clientFd, clientAddr);
	pSession->state = SS_CONNECTED;
	m_pSessionMap.insert(std::pair<int, Session*>(clientFd, pSession));

	struct epoll_event epollEvent;

	epollEvent.events = EPOLLIN | EPOLLERR; //| EPOLLOUT | EPOLLERR;
	epollEvent.data.fd = clientFd;

	// register server fd to epoll
	if(epoll_ctl(m_epollFdList[clientFd%NETWORK_THREAD_NUM], EPOLL_CTL_ADD, clientFd, &epollEvent) < 0)
	{
		fprintf(stderr, "[ERROR] : EPOLL CTL ERROR\n");
		exit(-1);
	}

	// give session to user
	Packet writePacket;
	S_PT_SESSION_U data;
	data.sessionId = clientFd;
	MAKE_PT_SESSION_U(writePacket.buffer, writePacket.size, data);

	TryWrite(clientFd, writePacket);

	printf("%d session connected\n", clientFd);

}

void NetworkManager::OnRead()
{

}

void NetworkManager::TryWrite(int clientFd, const Packet& packet)
{
	int result = write(clientFd, packet.buffer, packet.size);
	if(result < 0 && errno != EWOULDBLOCK && errno != EAGAIN)
	{
		// critical error
		fprintf(stderr, "[ERROR] write() ERROR : %s\n", strerror(errno));
		exit(1);
	}
}
