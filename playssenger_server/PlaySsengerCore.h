#include "NetworkManager.h"

class PlaySsengerCore
{
public:
	static PlaySsengerCore* GetInstance();
	bool Initialize();
	void Run();
	void CleanUp();

private:
	PlaySsengerCore();
	~PlaySsengerCore();

	NetworkManager* m_pNetworkManager;
	static PlaySsengerCore* m_instance;
};
