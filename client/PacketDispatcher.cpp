#include "PacketDispatcher.h"
#include "../common/Packets.h"

#include "NetworkManager.h"
#include <stdio.h>

PacketHandler g_handlerTable[HANDLER_TABLE_SIZE];

HANDLE(PT_SESSION_U)
{
	NetworkManager::GetInstance().SetSessionId(packet.sessionId);
	printf("My session id is %d\n", packet.sessionId);
}
