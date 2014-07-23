#ifndef _ROOM_H
#define _ROOM_H

#include "Member.h"
#include <vector>

class Room
{
public:
	Room();
	int EnterMember(Member member);
protected:
	std::vector<Member> m_memberList;
};

#endif
