#ifndef _MEMBER_H
#define _MEMBER_H

#include "Session.h"

#include <string>

class Member
{
public:
	Member() {}
	Member(int sessionId);
	void SetId(std::string id) { m_id = id; }
	std::string GetId() { return m_id; }
	int GetSessionId() { return m_sessionId; }

private:
	std::string m_id;
	int m_sessionId;
};

#endif
