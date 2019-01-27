#include "Demo.h"
#include "Logging.h"
#include "MutexLock.h"
#include <boost/noncopyable.hpp>
#include <map>
#include <string>
#include <memory>   //weak_ptr, shared_ptr
#include <functional>   //bind function
#include <assert.h>

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

class ObjectPool : boost::noncopyable, public enable_shared_from_this<ObjectPool>
{
    mutable MutexLock mutex_;
    map<string, weak_ptr<Object>> objects_;
    void deleteObject(Object* pObject)
    {
        if(pObject);
        {
            DEMO_DEBUG("key:%s\n", pObject->key().c_str());
            MutexLockGuard lock(mutex_);
            objects_.erase(pObject->key());
        }
    }

    static void weakDeleteObject(const weak_ptr<ObjectPool>& wkObjPool, Object* pObject)
    {
        shared_ptr<ObjectPool> pObjPool = wkObjPool.lock();
        if(pObjPool)
        {
            pObjPool->deleteObject(pObject);
        }
        delete pObject;
    }

public:
    shared_ptr<Object> get(string name)
    {
        shared_ptr<Object> pObject;
        MutexLockGuard lock(mutex_);
        weak_ptr<Object>& wkObject = objects_[name];
        pObject = wkObject.lock();
        if(!pObject)
        {
            pObject.reset(new Object(name), bind(&ObjectPool::weakDeleteObject, weak_ptr<ObjectPool>(shared_from_this()), placeholders::_1));
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
        shared_ptr<ObjectPool> pool(new ObjectPool);
        test = pool->get("test");
        cout << "count:" << pool->ObjectCount() << endl;
        pool->get("single");
        cout << "count:" << pool->ObjectCount() << endl;
    }
    cout << "test->key: " << test->key() << endl;
}