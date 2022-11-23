/*
    SIGCHILD信号产生的3个条件:
        1.子进程结束
        2.子进程接收到SIGSTOP信号停止时
        3.子进程在停止态，接受SIGCONT继续运行时
        都会给父进程发送该信号,父进程默认忽略该信号。

    使用SIGCHILD信号解决僵尸进程的问题
*/

#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<signal.h>
#include<wait.h>

void myfunc(int num)
{
    printf("捕捉到的信号:%d\n",num);
    // 回收子进程PCB的资源
    // while (1)
    // {
    //     wait(NULL);
    // } 不推荐这么写
    while (1)
    {
        int ret = waitpid(-1,NULL,WNOHANG); //非阻塞
        if(ret > 0)
            printf("child die , pid = %d\n",ret);
        else if(ret == 0)
        //说明还有子进程
            break;
        else if(ret == -1)
        //没有子进程
            break;

    }
    

}

int main()
{
    // 提前设置好阻塞信号集,阻塞SIGCHILD，因为有可能子进程很快结束，父进程还没有进行信号捕捉
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set,SIGCHLD);
    sigprocmask(SIG_BLOCK,&set,NULL);

    //创建一些子进程
    pid_t pid;
    for(int i = 0; i < 20; ++i)
    {
        pid = fork();
        if(pid == 0)
            break;
    }

    if(pid > 0)
    {
        //父进程

        //捕捉子进程死亡时发送的SIGCHILD信号
        struct sigaction act;
        act.sa_flags = 0;
        act.sa_handler = myfunc;
        sigemptyset(&act.sa_mask);
        
        sigaction(SIGCHLD,&act,NULL);
        //注册完信号捕捉以后，解除阻塞
        sigprocmask(SIG_UNBLOCK,&set,NULL);

        while (1)
        {
            printf("parent process pid : %d\n",getpid());
            sleep(2);
        }
        
    }else if(pid == 0)
    {
        //子进程
        printf("child process pid : %d\n",getpid());
    }

    return 0;
}