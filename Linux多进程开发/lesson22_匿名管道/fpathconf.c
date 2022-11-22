#include<sys/types.h>
#include<sys/wait.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int main()
{
    int pipefd[2];
    int ret = pipe(pipefd);
    //获取管道的大小
    long size = fpathconf(pipefd[0],_PC_PIPE_BUF);
    printf("pipe size: %ld\n",size);
    return 0;
}