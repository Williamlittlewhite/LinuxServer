/*
#include <unistd.h>
int execlp(const char *file, const char *arg, ...);
    会到环境变量查找指定的可执行文件，如果找到了就执行，找不到就执行不成功
    - 参数:
        - file:需要执行的文件的文件名(不写路径)
            a.out  ps
            ./a.out hello world
        - arg:是执行可执行文件所需要的参数列表
            第一个参数一般没有什么作用，为了方便，一般写的是可执行程序的名称
            从第二个参数开始 就是程序执行所需要的列表。
            参数最后需要以NULL结束(哨兵)
    - 返回值：
        只有调用失败时候，才会有返回值，返回-1并设置errno

int execv(const char* path,char *const argv[]);
    argv是需要的参数的一个字符串数组
    char *argv[] = {"ps","aux",NULL};
    execv("/bin/ps",argv);

int execve(const char* filename, char* const argv[],char* const envp[]);
    char* envp[] = {"/home/williamwhites/","/home/bbb","/home/aaa"};
*/

#include <unistd.h>
#include <stdio.h>
int main()
{
    // 创建一个子进程，在子进程执行exec函数族中的函数
    pid_t pid = fork();
    // 父进程
    if (pid > 0)
    {
        // 父进程
        printf("I am parent process, pid : %d\n", getpid());
    }
    else if (pid == 0)
    {
        // 子进程
        //  execl("hello","hello",NULL);
        execlp("ps", "ps", "aux", NULL);
        printf("I am child process, pid = %d\n", getpid());
    }

    for (int i = 0; i < 3; ++i)
    {
        printf("i = %d, pid = %d\n", i, getpid());
    }
    return 0;
}