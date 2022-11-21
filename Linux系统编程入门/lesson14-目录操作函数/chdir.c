/*
#include <unistd.h>
int chdir(const char *path);
    作用：修改进程的工作目录
    比如在home/williamwhites 启动一个可执行程序a.out 进程的工作目录/home/williamwhites
    参数：
        path: 需要修改的工作目录
#include <unistd.h>
char *getcwd(char *buf, size_t size);
    作用：获取当前的工作目录
    参数：
        - buf:  存储的路径，指向的是一个数组(传出参数)
        - size: 数组的大小
    返回值:
        返回值指向一块内存，这个数据就是第一个参数
*/
#include<unistd.h>
#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
int main()
{
    //获取当前的工作目录
    char buf[128];
    getcwd(buf,sizeof(buf));
    printf("当前的工作目录是:%s\n",buf);

    // 修改工作目录
    int ret = chdir("/home/williamwhites/LinuxServer/lesson13-文件属性操作");
    if(ret == -1)
    {
        perror("chdir");
        return -1;
    }

    //创建一个新的文件
    int fd = open("chdir.txt",O_RDWR|O_CREAT,0664);
    if(fd == -1)
    {
        perror("open");
        return -1;
    }
    close(fd);

    //获取当前的工作目录
    char buf1[128];
    getcwd(buf,sizeof(buf));
    printf("当前的工作目录是:%s\n",buf1);
    return 0;
}