/*
       #include <unistd.h>
       int pipe(int pipefd[2]);
            功能:创建一个匿名管道，用来进行进程间通信。
            参数:int pipefd[2] 这个数组是一个传出参数
                pipefd[0]对应的是管道的读端
                pipefd[1]对应的是管道的写端
            返回值:
                成功 0
                失败 -1
        管道默认是阻塞的，如果管道中没有数据:read阻塞(pipefd[0]),如果管道满了，Write阻塞(pipefd[1])
        注意:匿名管道只能用于具有关系的进程之间的通信(父子进程，兄弟进程)
*/
// 子进程发送数据给父进程，父进程读取到数据输出
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
    // 在fork之前创造管道！
    int pipefd[2];
    int ret = pipe(pipefd);
    if (ret == -1)
    {
        perror("pipe");
        exit(0);
    }
    // 创建子进程
    pid_t pid = fork();
    if (pid > 0)
    {
        // 父进程
        // 从管道的读取端读取数据
        // 关闭写端
        close(pipefd[1]);
        while (1)
        {
            char buf[1024] = {0};
            int len = read(pipefd[0], buf, sizeof(buf));
            printf("parent recv : %s, pid :%d\n", buf, getpid());

            // 向管道中写入数据
            //  char*str = "hello, i am parent";
            //  write(pipefd[1],str,strlen(str));
            sleep(1);
        }
    }

    else if (pid == 0)
    {
        // 子进程
        // 关闭读端
        close(pipefd[0]);
        while (1)
        {
            char buf[1024] = {0};
            // 向管道中写入数据
            char *str = "hello, i am child\n";
            write(pipefd[1], str, strlen(str)); // 这里没有写入数组结束符0是因为管道中会有0
            sleep(1);
            // int len = read(pipefd[0],buf,sizeof(buf));
            // printf("parent recv : %s, pid :%d\n",buf,getpid());
        }
    }
    return 0;
}