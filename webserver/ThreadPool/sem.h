#ifndef __SEM_H
#define __SEM_H
#include <pthread.h>
#include <semaphore.h>
#include <exception>
// 线程同步机制封装类

class sem
{
public:
    sem()
    {
        if (sem_init(&m_sem, 0, 0) != 0)
            throw std::exception();
    }
    sem(int num)
    {
        if (sem_init(&m_sem, 0, num) != 0)
            throw std::exception();
    }
    ~sem()
    {
        sem_destroy(&m_sem);
    }
    // 等待信号量
    bool wait() // 信号量加锁，减一为0时阻塞
    {
        return sem_wait(&m_sem) == 0;
    }
    // 增加信号量
    bool post() // 信号量解锁，信号量加1
    {
        return sem_post(&m_sem) == 0;
    }

private:
    sem_t m_sem;
};

#endif