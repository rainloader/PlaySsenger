#ifndef _STRUCTURES_H
#define _STRUCTURES_H

#define MAX_PACKET_SIZE 4096*4
#define MAX_BUFFER_LENGTH 4096*4

struct Packet
{
	char buffer[MAX_PACKET_SIZE];
	int size;
};

#endif
