#include "Session.h"

#ifndef _MEMBER_H
#define _MEMBER_H

class Member
{
public:
	Member(Session session);
	Session GetSession();
private:
	Session m_session;
};

#endif
