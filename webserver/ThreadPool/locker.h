#ifndef __LOCKER_H
#define __LOCKER_H
#include<pthread.h>
#include<exception>
//线程同步机制封装类

//互斥锁类
class locker{
public:
    locker(){
        if(pthread_mutex_init(&m_mutex,NULL) != 0)
            throw std::exception();
    }

    ~locker(){
        pthread_mutex_destroy(&m_mutex);
    }

    bool lock()    //上锁
    {
        return pthread_mutex_lock(&m_mutex) == 0;
    }

    bool unlock()  //解锁
    {
        return pthread_mutex_unlock(&m_mutex) == 0;
    }

    pthread_mutex_t& get()  //获得锁这个变量作为参数
    {
        return m_mutex;
    }
private:
    pthread_mutex_t m_mutex;
};


#endif