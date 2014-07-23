#include "Session.h"
#include <string>

#ifndef _MEMBER_H
#define _MEMBER_H

class Member
{
public:
	Member(int sessionId);

private:
	std::string m_id;
	int m_sessionId;
};

#endif
