#include "Room.h"

Room::Room()
{
	
}

int Room::EnterMember(Member member)
{		
	m_memberList.push_back(member);
	return 0;
}

bool Room::ApplyDisconnectedMember(int sessionId)
{
	for(std::vector<Member>::iterator it = m_memberList.begin(); it!=m_memberList.end(); ++it)
	{
		if(it->GetSession().sessionId == sessionId)
		{
			m_memberList.erase(it);
			return true;
		}
	}
	return false;
}

