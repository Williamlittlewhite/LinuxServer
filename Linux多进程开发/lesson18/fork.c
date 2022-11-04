/*
#include <sys/types.h>
#include <unistd.h>

pid_t fork(void);
    作用：用于创建子进程
    返回值：
        fork()的返回值返回2次，一次是在父进程，一次是在子进程
        在父进程中返回创建的子进程的ID，
        在子进程中返回0
        如何区分父进程和子进程：通过fork的返回值。
        在父进程中返回-1，表示创建子进程失败，并且设置errno
*/
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
        printf("pid : %d\n",pid);
        printf("I am parent process, pid : %d, ppid : %d\n",getpid(),getppid());
        printf("parent num : %d\n",num);
        num += 10;
        printf("parent num : %d\n",num);
    }
    else if(pid == 0)  //等于0是子进程的返回值
    {
        //当前是子进程
        printf("I am child process, pid : %d, ppid : %d\n",getpid(),getppid());
         printf("child num : %d\n",num);
        num += 100;
        printf("chid num : %d\n",num);
    }

    for(int i = 0; i < 5; ++i)
        {
            printf("i : %d, pid : %d\n",i,getpid());  //证明父子进程是交替进行的
            sleep(1);
        }
    return 0;
}