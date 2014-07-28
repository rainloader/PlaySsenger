#include "PacketDispatcher.h"
#include "../common/Packets.h"

#include "NetworkManager.h"

PacketHandler g_handlerTable[HANDLER_TABLE_SIZE];

HANDLE(PT_SESSION_U)
{
	NetworkManager::GetInstance().SetSessionId(packet.sessionId);
}
