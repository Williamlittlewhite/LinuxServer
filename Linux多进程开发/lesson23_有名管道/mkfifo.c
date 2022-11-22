/*
    创建fifo文件
    1.通过命令: mkfifo 名字
    2.通过函数: int mkfifio(const char* pathname, mode_t mode)


    #include <sys/types.h>
    #include <sys/stat.h>
    int mkfifo(const char *pathname, mode_t mode);
        参数:
            -pathname:管道名称的路径
            - mode: 文件的权限和open的mode是一样的
        返回值:
            成功返回0,失败返回-1，设置errno
*/
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<stdio.h>
#include<stdlib.h>
int main()
{
    int ret = mkfifo("fifo1",0664);

    if(ret == -1)
    {
        perror("mkfifo");
        exit(0);
    }
    return 0;
}