#include "PacketProcessor.h"

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
	
	return true;
}

int PacketProcessor::WriteBuffer(const int& protocol, char* packetBuffer, char* packet, const int& packetBodyLength)
{
	int packetSize = 0;
	return packetSize;
}
