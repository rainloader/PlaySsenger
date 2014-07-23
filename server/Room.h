#ifndef _ROOM_H
#define _ROOM_H

#include "Member.h"
#include <map>

class Room
{
public:
	Room(int id, std::string name);
	int EnterMember(Member member);
	void SendMember(int memberId);
	void ChangeRoomsName(std::string roomName);
	
protected:
	int m_id;
	std::string m_name;
	std::map<int, Member> m_memberMap;
};

#endif
