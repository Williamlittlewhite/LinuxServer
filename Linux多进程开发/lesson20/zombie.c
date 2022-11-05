#include <sys/types.h>
#include <unistd.h>
#include<stdio.h>
int main()
{
    int num = 10;
    //创建子进程
    pid_t pid = fork();

    //判断是父进程还是子进程
    if(pid > 0){
        //如果大于0，返回的是创建的子进程的进程号  是父进程的返回值
        while (1)
        {
            printf("I am parent process, pid : %d, ppid : %d\n",getpid(),getppid());
            sleep(1);
        }
        
    }
    else if(pid == 0)  //等于0是子进程的返回值
    {
        //当前是子进程
        sleep(2);//为了让父进程先死，演示孤儿进程，ppid为1
        printf("I am child process, pid : %d, ppid : %d\n",getpid(),getppid());
        //父进程结束后显示终端的原因:运行时候切换到后台，当运行完毕会自动切换回前台
    }

    for(int i = 0; i < 5; ++i)
        {
            printf("i : %d, pid : %d\n",i,getpid());  //证明父子进程是交替进行的
        }
    return 0;
}
