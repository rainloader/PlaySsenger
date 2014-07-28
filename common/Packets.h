#ifndef _PACKETS_H
#define _PACKETS_H

#include "PacketProcessor.h"

#include <string.h>
#include <stdio.h>

#define in
#define out
#define BYTE char

#define PacketName(name)	S_##name
// ------------------------
// PDF_START Enum
//-------------------------
#define PDF_START(name) name,
#define PDF_FIELD(type, name)
#define PDF_FIELD_ARRAY(type, name, length)
#define PDF_FIELD_VARRAY(type, name)
#define PDF_END(name)

enum PROTOCOL
{
#include "PacketDef.h"

	PT_MAX
};

#undef PDF_START
#undef PDF_FIELD
#undef PDF_FIELD_ARRAY
#undef PDF_FIELD_VARRAY
#undef PDF_END

// ------------------------
// PDF_START Structure
//-------------------------
#define PDF_START(name)				struct PacketName(name) {
#define PDF_FIELD(type, name)				type name;
#define PDF_FIELD_ARRAY(type, name, length)		type name[length];
#define PDF_FIELD_VARRAY(type, name)			type name;
#define PDF_END(name)				};

#include "PacketDef.h"


#undef PDF_START
#undef PDF_FIELD
#undef PDF_FIELD_ARRAY
#undef PDF_FIELD_VARRAY
#undef PDF_END

// ------------------------
// PDF_START Read
//-------------------------
#define PDF_START(name)			inline void READ_##name(in BYTE* buffer, out PacketName(name)& param)\
					{\
						unsigned long bufferPos = 0;
#define PDF_FIELD(type, name)			memcpy(&param.name, buffer + bufferPos, sizeof(type));\
						bufferPos += sizeof(type);
#define PDF_FIELD_ARRAY(type, name, length)	memcpy(param.name, buffer + bufferPos, length * sizeof(type));\
						bufferPos += length * sizeof(type);
#define PDF_FIELD_VARRAY(type, name)		int name##size;\
						memcpy(&name##size, buffer + bufferPos, sizeof(int));\
						bufferPos += sizeof(int);\
						param.name.resize(name##size);\
						memcpy(&param.name[0], buffer + bufferPos, param.name.size() * sizeof(type));\
						bufferPos += name##size * sizeof(type);
#define PDF_END(name)			}

#include "PacketDef.h"


#undef PDF_START
#undef PDF_FIELD
#undef PDF_FIELD_ARRAY
#undef PDF_FIELD_VARRAY
#undef PDF_END

// ------------------------
// PDF_START Write Method
//-------------------------
#define PDF_START(name)			inline unsigned int WRITE_##name(out BYTE* buffer, in PacketName(name)& param)\
					{\
						unsigned long bufferPos = 0;
#define PDF_FIELD(type, name)			memcpy(buffer + bufferPos, &param.name, sizeof(type));\
						bufferPos += sizeof(type);
#define PDF_FIELD_ARRAY(type, name, length)	memcpy(buffer, param.name, length * sizeof(type));\
						bufferPos += length * sizeof(type);
#define PDF_FIELD_VARRAY(type, name)		memcpy(buffer + bufferPos, &param.name.size(), sizeof(int));\
						bufferPos += sizeof(int);\
						memcpy(buffer + bufferPos, &param.name[0], param.name.size());\
						bufferPos += name##size * sizeof(type);
#define PDF_END(name)				return bufferPos;\
					}		
#include "PacketDef.h"

#undef PDF_START
#undef PDF_FIELD
#undef PDF_FIELD_ARRAY
#undef PDF_FIELD_VARRAY
#undef PDF_END

// ------------------------
// PDF_START Make packet method
//-------------------------
#define PDF_START(name)			inline void MAKE_##name(out char* packet, out int& packetSize, in S_##name& data)\
					{\
						char packetBody[MAX_PACKET_SIZE];\
						int packetBodyLength = WRITE_##name(packetBody, data);\
						packetSize = PacketProcessor::WriteBuffer(name, packet, packetBody, packetBodyLength);\
					}
#define PDF_FIELD(type, name)
#define PDF_FIELD_ARRAY(type, name, length)
#define PDF_FIELD_VARRAY(type, name)
#define PDF_END(name)

#include "PacketDef.h"

#undef PDF_START
#undef PDF_FIELD
#undef PDF_FIELD_ARRAY
#undef PDF_FIELD_VARRAY
#undef PDF_END

#endif

// ------------------------
// Packet Dispatch Handler Stub Generator
//-------------------------
#define HANDLE(name)\
	void DispatchPacket_##name(char* bytes, int length);\
	void Handle_##name(const S_##name& packet);\
	static struct RegisterDispatchPacket_##name\
	{\
		RegisterDispatchPacket_##name()\
		{\
			g_handlerTable[name] = DispatchPacket_##name;\
		}\
	} __register_DispatchPacket_##name;\
	void DispatchPacket_##name(char* bytes, int length)\
	{\
		S_##name packet;\
		READ_##name(bytes, packet);\
		Handle_##name(packet);\
	}\
	void Handle_##name(const S_##name& packet)

