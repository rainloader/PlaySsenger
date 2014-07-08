#include "Session.h"
#include <string>

#ifndef _MEMBER_H
#define _MEMBER_H

class Member
{
public:
	Member(Session session);
	Session GetSession();

private:
	std::string m_id;
	Session m_session;
};

#endif
