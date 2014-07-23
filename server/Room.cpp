#include "Room.h"

Room::Room(int id, std::string name)
: m_id(id), m_name(name)
{
}

int Room::EnterMember(Member member)
{
	for(std::map<int, Member>::iterator it = m_memberMap.begin(); it != m_memberMap.end(); ++it)
	{
		int sessionId = it->second.GetSessionId();
		// TODO:announce all member`s that a member entered to room
	}
	m_memberMap.insert(std::pair<int, Member>(member.GetSessionId(), member));
	return 0;
}

void Room::SendMember(int memberId)
{
	Member leavingMember = m_memberMap[memberId];
	// TODO:Check if the Member really exists
	m_memberMap.erase(memberId);
	for(std::map<int, Member>::iterator it = m_memberMap.begin(); it != m_memberMap.end(); ++it)
	{
		int sessionId = it->second.GetSessionId();
		// TODO:announce all member`s that a member leaved from room
	}
}

void Room::ChangeRoomsName(std::string name)
{
	m_name = name;
	for(std::map<int, Member>::iterator it = m_memberMap.begin(); it != m_memberMap.end(); ++it)
	{
		int sessionId = it->second.GetSessionId();
		// TODO : announce all member`s session to change room`s name
	}
}
