/*
#include <stdlib.h>
void exit(int status);


#include <unistd.h>
void _exit(int status);

status参数:是进程退出的一个状态信息，父进程回收子进程资源的时候可以获取到
*/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
int main()
{
    printf("hello\n");
    printf("world");

    // exit(0); //C库exit会刷新缓冲
    _exit(0); //系统exit不会刷新IO缓冲
    return 0;
}