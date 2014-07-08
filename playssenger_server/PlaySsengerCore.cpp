#include "PlaySsengerCore.h"

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
	m_pNetworkManager->Run();
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

