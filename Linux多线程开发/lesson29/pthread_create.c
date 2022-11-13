/*
       一般情况下,main函数所在的线程我们称之为主线程(main线程),其余创建的线程称之为子线程。
       程序中默认只有一个进程,fork()函数调用，2个进程
       程序中默认只有一个线程,pthread_create()函数调用,2个线程
       #include <pthread.h>

       int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
                          void *(*start_routine) (void *), void *arg);
       功能:创建一个子线程
       参数:
            - thread:传出参数，线程创建成功后，子线程的线程id被写到该变量中
            - attr:设置线程的属性，一般使用默认值,NULL
            - start_routine : 函数指针,这个函数是子线程需要处理的逻辑代码
            - arg : 给第三个参数使用,传参
        返回值:
            成功:0
            失败:返回错误号。这个错误号和之前的errno不太一样。
            获取错误号的信息: char *strperror(int errnum)

        第三方库:gcc pthread_create.c -o create -pthread
*/
#include <stdio.h>
#include<pthread.h>
#include<string.h>
#include<unistd.h>
void* callback(void* arg)
{
    printf("child thread...\n");
    printf("arg value: %d\n",*(int*)arg);
    return NULL;
}
int main()
{
    pthread_t tid;
    //创建一个子线程
    int num = 10;
    int ret = pthread_create(&tid,NULL,callback,(void*)&num);
    if(ret != 0)
    {
        char* errstr = strerror(ret);
        printf("error : %s\n",errstr);
    }

    for(int i = 0; i < 5; ++i)
    {
        printf("%d\n",i);
    }

    sleep(10);
    return 0;
}