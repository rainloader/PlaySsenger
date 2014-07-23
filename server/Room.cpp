#include "Room.h"

Room::Room()
{
	
}

int Room::EnterMember(Member member)
{
	m_memberList.push_back(member);
	return 0;
}

