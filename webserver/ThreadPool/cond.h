#ifndef __COND_H
#define __COND_H
#include<pthread.h>
#include<exception>
//线程同步机制封装类
//条件变量类
class cond{
public:
    cond(){
        if(pthread_cond_init(&m_cond,NULL) != 0)
            throw std::exception();
    }
    ~cond()
    {
        pthread_cond_destroy(&m_cond);
    }
    bool wait(pthread_mutex_t *mutex)//条件变量没有被唤醒，一直阻塞
    {
        return pthread_cond_wait(&m_cond, mutex) == 0; 
    }
    bool timewait(pthread_mutex_t *mutex,const struct timespec* t) //条件变量没有被唤醒，阻塞多长时间
    {
        return pthread_cond_timedwait(&m_cond,mutex,t) == 0;
    }
    bool signal()  //唤醒某个条件变量
    {
        return pthread_cond_signal(&m_cond) == 0;
    }
    bool broadcast() //唤醒所有条件变量
    {
        return pthread_cond_broadcast(&m_cond) == 0;
    }
private:
    pthread_cond_t m_cond;
};

#endif