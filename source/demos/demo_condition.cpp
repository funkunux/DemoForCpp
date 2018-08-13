#include <pthread.h>
#include <errno.h>
#include <string>
#include <queue>
#include <unistd.h>
#include <sys/time.h>
#include "Logging.h"

pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

class MsgQue
{
    typedef std::queue<int> MsgQuet;
    MsgQuet _que;
public:
    MsgQue():_que(){};
    void Push(const int& msg)
    {
        _que.push(msg);
        DEMO_DEBUG("Push: %d\n", msg);
    }
    int Pop()
    {
        int msg = _que.front();
        DEMO_DEBUG("Pop: %d\n", msg);
        _que.pop();
        return msg;
    }
    bool isEmpty()
    {
        return _que.empty();
    }

};

static void* Consumer(void* queue)
{
    MsgQue *mq = (MsgQue *)queue;
    //struct timespec t = {1, 0};
    int msg = 0;
    struct timespec t = {0};
    struct timeval now;
    t.tv_sec = 1;
    while(msg != 88)
    {
        pthread_mutex_lock(&mutex);
        while(mq->isEmpty())
        {
            gettimeofday(&now, NULL);
            t.tv_sec = now.tv_sec + 1;
            t.tv_nsec = now.tv_usec * 1000;
            if(ETIMEDOUT == pthread_cond_timedwait(&cond, &mutex, &t))
            {
                DEMO_DEBUG("Time out!\n");
            }
        }
        msg = mq->Pop();
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

static void* Producer(void* queue)
{
    MsgQue *mq = (MsgQue *)queue;
    for(int index = 0; index < 10; index++)
    {
        int msg = (9 == index)?88:index;
        pthread_mutex_lock(&mutex);
        mq->Push(msg);
        pthread_mutex_unlock(&mutex);
        pthread_cond_signal(&cond);
        sleep(2);
    }
    return NULL;
}

void demo_condition()
{
    MsgQue mq;
    mq.Push(90);
    pthread_t tid1;
    pthread_t tid2;
    pthread_create(&tid1, NULL,*Consumer, (void *)(&mq));
    pthread_create(&tid2, NULL,*Producer, (void *)(&mq));
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    pthread_cond_destroy(&cond);
    pthread_mutex_destroy(&mutex);
}