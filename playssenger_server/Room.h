#include "Member.h"
#include <vector>

#ifndef _ROOM_H
#define _ROOM_H

class Room
{
public:
	Room();
	int EnterMember(Member member);
	bool ApplyDisconnectedMember(int sessionId);
protected:
	std::vector<Member> m_memberList;
};

#endif
