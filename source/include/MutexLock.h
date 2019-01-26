#ifndef _MUTEXLOCK_H_AUTHOR_FUNKUNUX_
#define _MUTEXLOCK_H_AUTHOR_FUNKUNUX_
#include <boost/interprocess/sync/posix/pthread_helpers.hpp>
#include <boost/noncopyable.hpp>
#include <sys/types.h>

class MutexLockGuard;

class MutexLock : boost::noncopyable
{
    pthread_mutex_t mutex_;
    pthread_t holder_;
    void lock();
    void unlock();
    friend MutexLockGuard;
public:
    MutexLock();
    ~MutexLock();
    bool isHoldByCurrentThread();
};

class MutexLockGuard : boost::noncopyable
{
    MutexLock& mutex_;
public:
    MutexLockGuard(MutexLock m);
    ~MutexLockGuard();
};

#endif
