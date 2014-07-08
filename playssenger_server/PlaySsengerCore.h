#include "NetworkManager.h"
#include "Room.h"
#include <vector>

#ifndef _PLAYSSENGERCORE_H
#define _PLAYSSENGERCORE_H

class PlaySsengerCore
{
public:
	static PlaySsengerCore* GetInstance();
	bool Initialize();
	void Run();
	void MainLogic();
	void CleanUp();
	static void* RunNetworkThread(void* context);
	static void* RunLogicThread(void* context);

private:
	PlaySsengerCore();
	~PlaySsengerCore();

	NetworkManager* m_pNetworkManager;
	static PlaySsengerCore* m_instance;
	std::vector<Room> m_roomList;
	pthread_t m_threadList[4];
};

#endif
