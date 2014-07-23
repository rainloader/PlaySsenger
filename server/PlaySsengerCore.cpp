#include "PlaySsengerCore.h"
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#include "SpinLock.h"

#define LOGIC_THREAD_NUM 2

int g_threadCount = 0;
SpinLock g_threadCountLock = SpinLock();
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
	pthread_t networkThreadList[MAX_EVENT_NUM];
	pthread_t logicThreadList[LOGIC_THREAD_NUM];
	for(int i=0; i<NETWORK_THREAD_NUM; i++)
		pthread_create(&networkThreadList[i], NULL, &PlaySsengerCore::RunNetworkThread, this->m_pNetworkManager);
	for(int i=0; i<LOGIC_THREAD_NUM; i++)
		pthread_create(&logicThreadList[i], NULL, &PlaySsengerCore::RunLogicThread, this);
	
	for(;;)
	{
		sleep(1);
	}
}

void PlaySsengerCore::MainLogic()
{
	int threadId;
	g_threadCountLock.Lock();
	threadId = ++g_threadCount;
	g_threadCountLock.Unlock();
	for(;;)
	{
		sleep(1);
		//printf("ML thread %d\n", threadId);
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

