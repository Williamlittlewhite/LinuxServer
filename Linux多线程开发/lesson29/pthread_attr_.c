/*
    #include <pthread.h>

    int pthread_attr_init(pthread_attr_t *attr);
        - 初始化线程属性变量
    int pthread_attr_destroy(pthread_attr_t *attr);
        - 释放线程属性的资源
    int pthread_attr_setdetachstate(pthread_attr_t *attr, int detachstate);
        - 设置线程分离的状态属性
    int pthread_attr_getdetachstate(const pthread_attr_t *attr, int *detachstate);    
        - 获取线程分离的状态属性
*/
#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<string.h>

void* callback(void* arg)
{
    printf("child thread id : %ld\n",pthread_self());
    return NULL;
}

int main()
{
    // 创建一个线程属性变量
    pthread_attr_t attr;
    //初始化属性变量
    pthread_attr_init(&attr);
    //设置属性
    pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);

    //创建一个子线程
    pthread_t tid;
    int ret = pthread_create(&tid,&attr,callback,NULL);
    if(ret)
    {
        char* errstr = strerror(ret);
        printf("error1: %s\n",errstr);
    }
    //获取线程的栈的大小
    size_t size;
    pthread_attr_getstacksize(&attr,&size);

    printf("thread stack size : %ld\n",size);
    //输出主线程和子线程的id、
    printf("tid : %ld, main thread id : %ld\n",tid,pthread_self());

    //设置分离后，对分离的子线程进行连接 pthread_join()
    ret = pthread_join(tid,NULL);
    if(ret)
    {
        char* errstr = strerror(ret);
        printf("error3 : %s\n",errstr);
    }

    //释放线程属性资源
    pthread_attr_destroy(&attr);
    pthread_exit(NULL);
    return 0;
}