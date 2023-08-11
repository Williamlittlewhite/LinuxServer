#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

int main()
{
    // 1.创建一个通信的socket
    int fd = socket(PF_INET, SOCK_DGRAM, 0);
    if (fd == -1)
    {
        perror("socket");
        exit(-1);
    }

    // 2.设置广播属性
    int op = 1;
    setsockopt(fd, SOL_SOCKET, SO_BROADCAST, &op, sizeof op);

    // 3.创建一个广播的地址
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(9999);
    inet_pton(AF_INET, "192.168.17.255", &addr.sin_addr.s_addr);

    // 4.通信
    int num = 0;
    while (1)
    {
        // 发送数据
        char sendbuf[128];
        sprintf(sendbuf, "hello, client....%d\n", num++);
        sendto(fd, sendbuf, strlen(sendbuf) + 1, 0, (struct sockaddr *)&addr, sizeof addr);
        printf("广播的数据: %s\n", sendbuf);
        sleep(1);
    }

    close(fd);

    return 0;
}