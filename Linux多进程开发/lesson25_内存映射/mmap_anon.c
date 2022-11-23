/*
    匿名映射:不需要文件实体进程进行内存映射
*/
#include<stdio.h>
#include<unistd.h>
#include<sys/mman.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
#include<string.h>
#include<wait.h>
int main()
{
    //1.创建匿名内存映射区
    int length = 4096;
    void* ptr = mmap(NULL,length,PROT_READ|PROT_WRITE,MAP_SHARED|MAP_ANONYMOUS,-1,0);
    if(ptr == MAP_FAILED){
        perror("mmap");
        exit(0);
    }

    //2.父子进程间通信
    pid_t pid = fork();
    if(pid > 0)
    {
        //父进程
        strcpy((char*)ptr, "hello,world");
        wait(NULL);
    }
    else if(pid == 0)
    {
        //子进程
        sleep(1);
        printf("%s\n",(char*)ptr);
    }
    
    // 释放内存映射区
    int ret = munmap(ptr,length);

    if(ret == -1)
    {
        perror("mumap");
        exit(0);
    }
    return 0;
}
