#include "PacketDispatcher.h"
#include "../common/Packets.h"

PacketHandler g_handlerTable[HANDLER_TABLE_SIZE];

HANDLE(PT_MESSAGE)
{
	char message[1024];
	memcpy(message, &packet.message[0], packet.message.size());
	message[packet.message.size()] = '\0';
	printf("%d : %s\n", packet.sessionId, message);
}
