#ifndef _SPINLOCK_H
#define _SPINLOCK_H

#include <pthread.h>

class SpinLock
{
public:
	SpinLock();
	SpinLock(int pshared);
	~SpinLock();
	void Lock();
	bool IsLocked();
	void Unlock();
private:
	pthread_spinlock_t m_lock;
	int m_isLocked;
};

#endif
