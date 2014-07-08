#include "Member.h"

Member::Member(Session session)
: m_session(session)
{
}

Session Member::GetSession()
{
	return m_session;
}
