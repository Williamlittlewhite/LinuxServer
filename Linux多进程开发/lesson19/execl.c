/*
#include <unistd.h>
int execl(const char *path, const char *arg, ...);
    - 参数:
        - path:需要执行的文件的路径
            a.out /home/williamwhites/a.out 推荐使用绝对路径
            ./a.out hello world
        - arg:是执行可执行文件所需要的参数列表
            第一个参数一般没有什么作用，为了方便，一般写的是可执行程序的名称
            从第二个参数开始 就是程序执行所需要的列表。
            参数最后需要以NULL结束(哨兵)
    - 返回值：
        只有调用失败时候，才会有返回值，返回-1并设置errno
*/

#include<unistd.h>
#include<stdio.h>  
int main()
{
    //创建一个子进程，在子进程执行exec函数族中的函数
    pid_t pid = fork();
    //父进程
    if(pid > 0){
        //父进程
        printf("I am parent process, pid : %d\n",getpid());
    }else if(pid == 0){
        //子进程
        // execl("hello","hello",NULL);
        execl("/bin/ps","ps","aux",NULL);
        printf("I am child process, pid = %d\n",getpid());
    }

    for(int i = 0; i < 3; ++i)
    {
        printf("i = %d, pid = %d\n",i,getpid());
    }
    return 0;
}