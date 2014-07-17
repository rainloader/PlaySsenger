#include "SpinLock.h"
#include <stdio.h>
SpinLock::SpinLock()
{
	pthread_spin_init(&m_lock, PTHREAD_PROCESS_SHARED);
}

SpinLock::SpinLock(int pshared)
{
	pthread_spin_init(&m_lock, pshared);
}

SpinLock::~SpinLock()
{
	pthread_spin_destroy(&m_lock);
}

void SpinLock::Lock()
{
	pthread_spin_lock(&m_lock);
}

void SpinLock::Unlock()
{
	pthread_spin_unlock(&m_lock);
}

