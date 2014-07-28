#ifndef _PACKETDISPATCHER_H
#define _PACKETDISPATCHER_H

enum
{
	HANDLER_TABLE_SIZE = 0x1000
};

typedef void (*PacketHandler)(char*, int);

extern PacketHandler g_handlerTable[HANDLER_TABLE_SIZE];

#endif
