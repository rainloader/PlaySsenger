#include "PacketProcessor.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

PacketProcessor::PacketProcessor()
{
}

PacketProcessor::~PacketProcessor()
{
}

bool PacketProcessor::ReadBuffer(int& idxPacket, char* packetBuffer, char* readBuffer, const int& byteTransferred)
{
	memcpy(packetBuffer + idxPacket, readBuffer, byteTransferred);
	idxPacket += byteTransferred;

	return true;
}

bool PacketProcessor::FetchPacket(int& protocol, char* packet, int& packetBodyLength, int& idxPacket, char* packetBuffer)
{
	int packetSize = 0;

	if(idxPacket < sizeof(int))
	{
		return false;
	}

	if(memcpy(&packetSize, packetBuffer, sizeof(int)) != 0)
	{
		fprintf(stderr, "[ERROR] mem cpy error\n");
		exit(-1);
	}
	if(packetSize >= MAX_PACKET_SIZE || packetSize <= 0)
	{
		fprintf(stderr, "[ERROR] invalid packet\n");
		exit(-1);
	}
	
	if(packetSize <= idxPacket)
	{
		memcpy(&protocol, packetBuffer + sizeof(int)/*LENGTH*/, sizeof(int));

		packetBodyLength = packetSize - sizeof(int)/*LENGTH*/ - sizeof(int)/*PROTOCOL*/;

		if(memcpy(packet, packetBuffer + sizeof(int)/*LENGTH*/ + sizeof(int)/*PROTOCOL*/, packetBodyLength) != 0)
		{
			fprintf(stderr, "[ERROR] mem cpy error\n");
		}

		if(idxPacket - packetSize > 0)
		{
			memmove(packetBuffer, packetBuffer + packetSize, idxPacket - packetSize);
		}
		
		idxPacket -= packetSize;

		if(idxPacket < 0)
		{
			fprintf(stderr, "[ERROR] minus packet??");
		}
	}
	else
	{
		return false;
	}
	return true;
}

int PacketProcessor::WriteBuffer(const int& protocol, char* packetBuffer, char* packet, const int& packetBodyLength)
{
	int packetSize = sizeof(int)/*LENGTH*/ + sizeof(int)/*PROTOCOL*/ + packetBodyLength;
	memcpy(packetBuffer, &packetSize, sizeof(int));	
	memcpy(packetBuffer + sizeof(int)/*LENGTH*/, &protocol, sizeof(int));
	memcpy(packetBuffer + sizeof(int)/*LENGTH*/ + sizeof(int)/*PROTOCOL*/, packet, packetBodyLength);
	return packetSize;
}
