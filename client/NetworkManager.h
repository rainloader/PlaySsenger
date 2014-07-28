#ifndef _NETWORKMANAGER_H
#define _NETWORKMANAGER_H


class NetworkManager
{
public:
	void Initialize();
	void Connect();
	void ReadAndDispatch();

private:
	int sessionId;
	int socketFd;
	
};

#endif
