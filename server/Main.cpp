#include <iostream>
#include "PlaySsengerCore.h"

int main()
{
	PlaySsengerCore* pCore = PlaySsengerCore::GetInstance();

	if(pCore->Initialize())
	{
		pCore->Run();
	}

	pCore->CleanUp();

	std::cout << "PlaySsenger Terminated." << std::endl;
	return 0;
}
