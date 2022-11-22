//向有名管道中读数据
#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>

int main()
{
    //1.打开管道文件
    int fd = open("test",O_RDONLY);  //如果写端没有打开那么会停滞在这里
    if(fd == -1)
    {
        perror("open");
        exit(0);
    }
    //读数据
    while (1)
    {
        /* code */
        char buf[1024] = {0};
        int len = read(fd,buf,sizeof(buf));
        if(len == 0)
        {
            printf("写端断开连接了...\n");
            break;
        }
        printf("receive buf : %s\n",buf);
    }
    close(fd);
    return 0;
}