#include "ClientCore.h"

#include <pthread.h>
#include <stdio.h>

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

	pthread_t writeThread;
	pthread_t readThread;

	for(;;)
		m_networkManager.ReadAndDispatch();
}

ClientCore::ClientCore()
{
	m_networkManager = NetworkManager::GetInstance();
}
