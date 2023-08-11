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

    // 2.设置多播属性，设置外出接口
    struct in_addr imr_multiaddr;
    // 初始化多播地址 不是本地ip地址
    inet_pton(AF_INET, "239.0.0.10", &imr_multiaddr.s_addr);
    setsockopt(fd, IPPROTO_IP, IP_MULTICAST_IF, &imr_multiaddr, sizeof imr_multiaddr);

    // 3.初始化客户端的地址
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(9999);
    inet_pton(AF_INET, "239.0.0.10", &addr.sin_addr.s_addr);

    // 4.通信
    int num = 0;
    while (1)
    {
        // 发送数据
        char sendbuf[128];
        sprintf(sendbuf, "hello, client....%d\n", num++);
        sendto(fd, sendbuf, strlen(sendbuf) + 1, 0, (struct sockaddr *)&addr, sizeof addr);
        printf("组播的数据: %s\n", sendbuf);
        sleep(1);
    }

    close(fd);

    return 0;
}