#ifndef _SPINLOCK_H
#define _SPINLOCK_H

class SpinLock
{
public:
	SpinLock();
	void Lock();
	bool IsLocked();
	void Unlock();
private:
	int m_isLocked;
};

#endif
