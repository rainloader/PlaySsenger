#ifndef _CLIENTCORE_H
#define _CLIENTCORE_H

#include "NetworkManager.h"

class ClientCore
{
	public:
		static ClientCore& GetInstance();
		void Run();
		static void* RunReadThread(void* context);
		static void* RunLogicThread(void* context);

	private:
		ClientCore();
		void RunLogic();
		static ClientCore* sm_instance;
		NetworkManager& m_networkManager;
		bool m_exitFlag;
};

#endif
