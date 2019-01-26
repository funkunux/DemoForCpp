#include "MutexLock.h"

MutexLock::MutexLock()
    : holder_(0)
{
    pthread_mutex_init(&mutex_, NULL);
}
MutexLock::~MutexLock()
{
    pthread_mutex_destroy(&mutex_);
}

void MutexLock::lock()
{
    pthread_mutex_lock(&mutex_);
    holder_ = pthread_self();
}

void MutexLock::unlock()
{
    holder_ = 0;
    pthread_mutex_unlock(&mutex_);
}

bool MutexLock::isHoldByCurrentThread()
{
    return pthread_equal(pthread_self(), holder_);
}

MutexLockGuard::MutexLockGuard(MutexLock m)
    : mutex_(m)
{
    mutex_.lock();
}
MutexLockGuard::~MutexLockGuard()
{
    mutex_.unlock();
}