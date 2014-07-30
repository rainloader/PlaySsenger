#ifndef _PLAYSSENGERCORE_H
#define _PLAYSSENGERCORE_H

#include "NetworkManager.h"
#include "Room.h"
#include <vector>

class PlaySsengerCore
{
public:
	~PlaySsengerCore();
	static PlaySsengerCore& GetInstance();
	bool Initialize();
	void Run();
	void MainLogic();
	void CleanUp();
	static void* RunNetworkThread(void* context);
	static void* RunLogicThread(void* context);

private:
	PlaySsengerCore();

	NetworkManager* m_pNetworkManager;
	static PlaySsengerCore* sm_instance;
	std::vector<Room> m_roomList;
};

#endif
