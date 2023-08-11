#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
int main()
{
    // 1.创建套接字
    int fd = socket(PF_INET, SOCK_STREAM, 0);
    if (fd == -1)
    {
        perror("socket");
        exit(-1);
    }
    // 2.连接服务器
    struct sockaddr_in serveraddr;
    serveraddr.sin_family = AF_INET;
    inet_pton(AF_INET, "192.168.17.132", &serveraddr.sin_addr.s_addr);
    serveraddr.sin_port = htons(9999);
    int ret = connect(fd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    if (ret == -1)
    {
        perror("connect");
        exit(-1);
    }
    char recvBuf[1024] = {0};
    while (1)
    { // 3.通信

        char *data = "hello, I am client";
        // 给服务端发送数据
        write(fd, data, strlen(data));
        sleep(1);
        // 读取服务端发送来的数据
        int len = read(fd, recvBuf, sizeof(recvBuf));
        if (len == -1)
        {
            perror("read");
            exit(-1);
        }
        else if (len > 0)
        {
            printf("recv server data : %s\n", recvBuf);
        }
        else if (len == 0)
        {
            // 表示服务器端断开了连接
            printf("server closed...");
            break;
        }
    }
    close(fd);
    return 0;
}