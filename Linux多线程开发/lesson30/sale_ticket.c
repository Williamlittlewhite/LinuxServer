/*
    使用多线程实现卖票的案例
    有3个窗口,一共是100张票。
*/

#include<pthread.h>
#include<stdio.h>
#include<unistd.h>
//全局变量，所有的线程都共享这一份资源
int tickets = 100;
void* sellticket(void* arg){
    //卖票
    while (tickets>0)
    {
        usleep(3000);
        printf("%ld 正在卖第 %d 张门票\n",pthread_self(),tickets);
        tickets--;
    }
    return NULL;
}

int main()
{
    //创建3个子线程
    pthread_t tid1,tid2,tid3;
    pthread_create(&tid1,NULL,sellticket,NULL);
    pthread_create(&tid1,NULL,sellticket,NULL);
    pthread_create(&tid1,NULL,sellticket,NULL);

    //回收子线程的资源,阻塞
    pthread_join(tid1,NULL);
    pthread_join(tid2,NULL);
    pthread_join(tid3,NULL);

    // //设置线程分离,不能和join联用
    // pthread_detach(tid1);
    // pthread_detach(tid2);
    // pthread_detach(tid3);

    pthread_exit(NULL); //退出主线程

    return 0;
}
