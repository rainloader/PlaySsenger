#ifndef _CLIENTCORE_H
#define _CLIENTCORE_H

#include "NetworkManager.h"

class ClientCore
{
	public:
		static ClientCore& GetInstance();
		void Run();
	private:
		ClientCore();
		static ClientCore* sm_instance;
		NetworkManager m_networkManager;
};

#endif
