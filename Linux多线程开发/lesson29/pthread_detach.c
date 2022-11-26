/*
       #include <pthread.h>

       int pthread_detach(pthread_t thread);    
            功能:分离一个线程,被分离的线程在终止的时候会自动释放资源返回给系统。
            1. 不能多次分离,会产生不可预料的行为。
            2. 不能去连接一个已经分离的进程,如果去连接会报错。
            参数：需要分离的线程的ID
            返回值: 分离失败返回错误号，成功返回0
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
    //创建一个子线程
    pthread_t tid;
    int ret = pthread_create(&tid,NULL,callback,NULL);
    if(ret)
    {
        char* errstr = strerror(ret);
        printf("error1: %s\n",errstr);
    }

    //输出主线程和子线程的id、
    printf("tid : %ld, main thread id : %ld\n",tid,pthread_self());


    //设置子线程分离,子线程分离后，子线程结束时对应的资源就不需要主线程释放了
    ret = pthread_detach(tid);
    if(ret)
    {
        char* errstr = strerror(ret);
        printf("error2 : %s\n",errstr);
    }
    //设置分离后，对分离的子线程进行连接 pthread_join() 会报错
    ret = pthread_join(tid,NULL);
    if(ret)
    {
        char* errstr = strerror(ret);
        printf("error3 : %s\n",errstr);
    }
    pthread_exit(NULL);
    return 0;
}