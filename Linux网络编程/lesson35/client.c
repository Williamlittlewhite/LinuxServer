#include<stdio.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
int main()
{
    //创建socket
    int fd = socket(PF_INET,SOCK_STREAM,0);
    if(fd == -1)
    {
        perror("socket");
        return -1;
    }

    struct sockaddr_in saddr;
    inet_pton(AF_INET,"192.168.17.131",&saddr.sin_addr.s_addr);
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(9999);

    //连接服务器
    int ret = connect(fd,(struct sockaddr*)&saddr,sizeof saddr);

    if(ret == -1)
    {
        perror("connect");
        return -1;
    }

    int num = 0;
    while (1)
    {
        char sendBuf[1024] = {0};
        sprintf(sendBuf,"send data %d",num);

        write(fd,sendBuf,strlen(sendBuf)+1);

        //接收
        int len = read(fd,sendBuf,strlen(sendBuf)+1);
        if(len == -1)
        {
            perror("read");
            return -1;
        }
        else if(len > 0)
            printf("read buf = %s\n",sendBuf);
        else{
            printf("服务器已经断开连接...\n");
            break;
        }
        num++;
        sleep(1);
    }
    
    close(fd);
    return 0;
}