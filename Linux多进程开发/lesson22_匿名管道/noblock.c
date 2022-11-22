#include<unistd.h>
#include<sys/types.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
/*
    设置管道非阻塞
    int flags = fcntl(fd[0],F_GETFL);//获取原来的flag
    flags |= O_NONBLOCK;  //修改flag的值
    fcntl(fd[0],F_SETFL,flags);//设置新的flag
*/
int main()
{
    //在fork之前创造管道！
    int pipefd[2];
    int ret = pipe(pipefd);
    if(ret == -1)
    {
        perror("pipe");
        exit(0);
    }     
    //创建子进程
    pid_t pid = fork();
    if(pid > 0)
    {
        //父进程
        //从管道的读取端读取数据
        //关闭写端 
        int flags = fcntl(pipefd[0],F_GETFL);//获取原来的flag
        flags |= O_NONBLOCK;  //修改flag的值
        fcntl(pipefd[0],F_SETFL,flags);//设置新的flag
        close(pipefd[1]);
        while (1)
        {
            char buf[1024] = {0};
            int len = read(pipefd[0],buf,sizeof(buf));
            printf("len : %d\n",len);
            printf("parent recv : %s, pid :%d\n",buf,getpid());
            sleep(2);
        }
    }
    
    else if(pid == 0)
    {
        //子进程
        //关闭读端
        close(pipefd[0]);
        while(1)
        {
            char buf[1024] = {0};
            //向管道中写入数据
            char*str = "hello, i am child";
            write(pipefd[1],str,strlen(str));
            sleep(5);
        }
    }
    return 0;
}