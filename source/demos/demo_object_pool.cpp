#include "Demo.h"
#include "Logging.h"
#include "MutexLock.h"
#include <boost/noncopyable.hpp>
#include <map>
#include <string>
#include <memory>   //weak_ptr, shared_ptr

class Object : boost::noncopyable
{
    mutable MutexLock mutex_;
    string key_;
public:
    Object(string name) : key_(name)
    {
        MutexLockGuard lock(mutex_);
        DEMO_DEBUG("Contruct[%s]\n", key_.c_str());
    }
    ~Object()
    {
        MutexLockGuard lock(mutex_);
        DEMO_DEBUG("Destruct[%s]\n", key_.c_str());
    }
    string key()
    {
        MutexLockGuard lock(mutex_);
        return key_;
    }
};

class ObjectPool : boost::noncopyable
{
    mutable MutexLock mutex_;
    map<string, weak_ptr<Object>> objects_;
public:
    shared_ptr<Object> get(string name)
    {
        shared_ptr<Object> pObject;
        MutexLockGuard lock(mutex_);
        weak_ptr<Object>& wkObject = objects_[name];
        pObject = wkObject.lock();
        if(!pObject)
        {
            pObject.reset(new Object(name));
            wkObject = pObject;
        }
        return pObject;
    }
    unsigned int ObjectCount()
    {
        return objects_.size();
    }
};


void demo_object_pool()
{
    shared_ptr<Object> test;
    {
        ObjectPool pool;
        test = pool.get("test");
        cout << "count:" << pool.ObjectCount() << endl;
        pool.get("single");
        cout << "count:" << pool.ObjectCount() << endl;
    }
    cout << "test->key: " << test->key() << endl;
}