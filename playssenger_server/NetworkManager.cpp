#include "NetworkManager.h"
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
NetworkManager::NetworkManager() : m_serverFd(0), m_epollFd(0)
{
}

NetworkManager::~NetworkManager()
{
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

	// Prepare epoll process
	if((m_epollFd = epoll_create(1)) < 0)
	{
		fprintf(stderr, "[ERROR] : EPOLL CREATE ERROR\n");
	}

	struct epoll_event epollEvent;

	epollEvent.events = EPOLLIN | EPOLLOUT | EPOLLERR;
	epollEvent.data.fd = m_serverFd;

	// register server fd to epoll
	if(epoll_ctl(m_epollFd, EPOLL_CTL_ADD, m_serverFd, &epollEvent) < 0)
	{
		fprintf(stderr, "[ERROR] : EPOLL CTL ERROR\n");
		exit(-1);
	}

	printf("epoll Create Success\n");

	return true;
}

void NetworkManager::Run()
{
	struct epoll_event events[100];
	int numOfEvent, n;
	for(;;)
	{
		numOfEvent = epoll_wait(m_epollFd, m_epollEvents, 100, 2000);

		if(numOfEvent < 0){	
			// critical error
			fprintf(stderr, "[ERROR] epoll_wait() ERROR : %s\n", strerror(errno));
			exit(1);
		}
		
		if(numOfEvent == 0)
		{
			continue;
		}
		
		OnEvent(numOfEvent);
	}
	close(m_serverFd);
	close(m_epollFd);
}

void NetworkManager::OnEvent(int numOfEvent)
{
	int strLen = 0;
	char buffer[1024];
	for(int i=0; i<numOfEvent; i++)
	{
		if(m_epollEvents[i].data.fd == m_serverFd) // when clients attempt to connect
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

			Session session (clientFd, clientAddr);
			session.SetState(SS_CONNECTED);
			m_sessionMap.insert(std::pair<int, Session>(clientFd, session));

			struct epoll_event epollEvent;

			epollEvent.events = EPOLLIN | EPOLLERR; //| EPOLLOUT | EPOLLERR;
			epollEvent.data.fd = clientFd;

			// register server fd to epoll
			if(epoll_ctl(m_epollFd, EPOLL_CTL_ADD, clientFd, &epollEvent) < 0)
			{
				fprintf(stderr, "[ERROR] : EPOLL CTL ERROR\n");
				exit(-1);
			}

			printf("%d session connected\n", clientFd);
		}
		else	// when client request service
		{
			strLen = read(m_epollEvents[i].data.fd, buffer, 1024); // Read client request
			if(strLen == 0)	// Client request to disconnect
			{
				epoll_ctl(m_epollFd, EPOLL_CTL_DEL, m_epollEvents[i].data.fd, NULL); // remove client info from epoll instance
				int clientFd = m_epollEvents[i].data.fd;
				close(clientFd); // disconnecd
				m_sessionMap.erase(clientFd);
				printf("%d session disconnected\n", clientFd);
			}
			else if(strLen < 0)
			{
			}
			else
			{
				int clientFd = m_epollEvents[i].data.fd;
				__uint32_t events = m_epollEvents[i].events;
				if(events & EPOLLIN)
				{
					printf("EPOLLIN\n");
					
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
				buffer[strLen] = '\0';
				printf("%s\n", buffer);

				// service that someelse
			}
		}
	}
}

