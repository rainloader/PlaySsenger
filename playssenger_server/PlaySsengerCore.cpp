#include "PlaySsengerCore.h"
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

/**/int G_TC = 0;
//-----------------------------------------------------
// initialize static variable
PlaySsengerCore* PlaySsengerCore::m_instance = 0;
PlaySsengerCore* PlaySsengerCore::GetInstance()
{
	if(!m_instance)
	{
		m_instance = new PlaySsengerCore();
	}
	return m_instance;
}

bool PlaySsengerCore::Initialize()
{
	m_pNetworkManager = new NetworkManager();
	m_pNetworkManager->Initialize();
	return true;
}

void PlaySsengerCore::Run()
{
	pthread_t t1, t2, t3, t4;
	pthread_create(&t1, NULL, &PlaySsengerCore::RunNetworkThread, this->m_pNetworkManager);
	pthread_create(&t2, NULL, &PlaySsengerCore::RunNetworkThread, this->m_pNetworkManager);
	pthread_create(&t3, NULL, &PlaySsengerCore::RunLogicThread, this);
	pthread_create(&t4, NULL, &PlaySsengerCore::RunLogicThread, this);
	
	for(;;)
	{
		sleep(1);
	}
//	std::thread t1(&PlaySsengerCore::RunNetworkThread, this);
//	std::thread t2(&PlaySsengerCore::RunNetworkThread, this);
//	t1.join();
//	t2.join();
}

void PlaySsengerCore::MainLogic()
{
	/**/ int TC = G_TC++;
	for(;;)
	{
		sleep(1);
		/**/printf("ML thread %d\n", TC);
	}
}

void* PlaySsengerCore::RunNetworkThread(void *context)
{
	((NetworkManager*)context)->Run();
	return 0;
}

void* PlaySsengerCore::RunLogicThread(void *context)
{
	((PlaySsengerCore*)context)->MainLogic();
	return 0;
}

void PlaySsengerCore::CleanUp()
{
	if(m_pNetworkManager)
		delete m_pNetworkManager;
}

PlaySsengerCore::PlaySsengerCore() : m_pNetworkManager(0)
{

}

PlaySsengerCore::~PlaySsengerCore()
{
	if(m_instance)
		delete m_instance;
}

