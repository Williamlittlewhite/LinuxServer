#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

int main()
{
    //1.创建一个通信的socket
    int fd = socket(PF_INET,SOCK_DGRAM,0);
    if(fd == -1)
    {
        perror("socket");
        exit(-1);
    }

    // 服务器的地址信息
    struct sockaddr_in saddr;
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(9999);
    inet_pton(AF_INET,"192.168.17.131",&saddr.sin_addr.s_addr);
    
    int num = 0;
    //2.通信
    while (1)
    {
        char sendbuf[128];
        sprintf(sendbuf,"hello , i am client %d\n",num++);
        //发送数据
        sendto(fd,sendbuf,strlen(sendbuf)+1,0,(struct sockaddr*)&saddr,sizeof saddr);
        //接受数据
        int len = sizeof saddr;
        int num = recvfrom(fd,sendbuf,sizeof sendbuf,0,(struct sockaddr*)&saddr, &len);

        printf("server say : %s\n",sendbuf);

        sleep(1);
    }

    close(fd);
    
    return 0;
}