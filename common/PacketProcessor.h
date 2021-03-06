#ifndef _PACKETPROCESSOR_H
#define _PACKETPROCESSOR_H

#include "Structures.h"

class PacketProcessor
{
public:
	PacketProcessor();
	~PacketProcessor();

	static bool ReadBuffer(int& idxPacket, char* packetBuffer, char* readBuffer, const int& byteTransferred);
	static bool FetchPacket(int& protocol, char* packet, int& packetBodyLength, int& idxPacket, char* packetBuffer);
	static int WriteBuffer(const int& protocol, char* packetBuffer, char* packet, const int& packetBodyLength);
};

#endif
