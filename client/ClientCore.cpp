#include "ClientCore.h"

#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <cstring>

#define CONSOLE_BUFFER_LENGTH 512

ClientCore* ClientCore::sm_instance = NULL;

ClientCore& ClientCore::GetInstance()
{
	if(sm_instance == NULL)
		sm_instance = new ClientCore();
	return *sm_instance;
}

void ClientCore::Run()
{
	m_networkManager.Initialize();
	m_networkManager.Connect();

	pthread_t readThread;
	pthread_t logicThread;

	pthread_create(&readThread, NULL, &ClientCore::RunReadThread, this);
	pthread_create(&logicThread, NULL, &ClientCore::RunLogicThread, this);

	while(!m_exitFlag)
	{
		sleep(2);
	}
}

void* ClientCore::RunReadThread(void* context)
{
	for(;;)
		((ClientCore*)context)->m_networkManager.ReadAndDispatch();
	return 0;
}

void* ClientCore::RunLogicThread(void* context)
{
	((ClientCore*)context)->RunLogic();
	return 0;
}

void ClientCore::RunLogic()
{
	char consoleInputBuffer[CONSOLE_BUFFER_LENGTH];


	char choice;
	// read id first
	while(choice != 'l' && choice != 'j')
	{
		printf("Login(l), Join(j), exit(e)\n");
		scanf("%c", &choice);
	
		switch(choice)
		{
			case 'l':
				break;
			case 'j':
				break;
			case 'e':
				printf("wait....\n");
				m_exitFlag = true;
				return;
			default:
				break;
		}
		getchar();
	}

	for(;;)
	{
		bzero(consoleInputBuffer, CONSOLE_BUFFER_LENGTH);
		scanf("%s", consoleInputBuffer);
		int length = strlen(consoleInputBuffer);
		if(strcmp(consoleInputBuffer, "exit") == 0)
			break;
		m_networkManager.SendMessage(consoleInputBuffer, length);
	}
	printf("wait....\n");
	m_exitFlag = true;
}

ClientCore::ClientCore()
: m_networkManager(NetworkManager::GetInstance())
{
	m_exitFlag = false;
}
