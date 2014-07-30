#include <iostream>
#include "PlaySsengerCore.h"

int main()
{
	PlaySsengerCore serverCore = PlaySsengerCore::GetInstance();

	if(serverCore.Initialize())
	{
		serverCore.Run();
	}

	serverCore.CleanUp();

	std::cout << "PlaySsenger Terminated." << std::endl;
	return 0;
}
