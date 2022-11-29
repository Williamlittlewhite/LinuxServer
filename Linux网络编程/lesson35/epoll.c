#include<stdio.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/epoll.h>
#include<string.h>
#include<stdlib.h>

int main()
{
    int lfd = socket(PF_INET,SOCK_STREAM,0);
    struct sockaddr_in saddr;
    saddr.sin_port = htons(9999);
    saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = INADDR_ANY;

    bind(lfd,(struct sockaddr*)&saddr,sizeof saddr);
    listen(lfd,8);

    //调用epoll_create()创建一个epoll实例
    int epfd = epoll_create(100);

    // 将监听的文件描述符相关的检测信息添加到epoll实例当中
    struct epoll_event epev;
    epev.events = EPOLLIN;
    epev.data.fd = lfd;
    epoll_ctl(epfd,EPOLL_CTL_ADD,lfd,&epev);

    struct epoll_event epevs[1024];


    while (1)
    {
        int ret = epoll_wait(epfd,epevs,1024,-1);
        if(ret == -1)
        {
            perror("epoll_wait");
            exit(-1);
        }

        printf("ret = %d\n",ret);

        for (int i = 0; i < ret; ++i)
        {

            int curfd = epevs[i].data.fd;

            if(curfd == lfd){
                //监听的文件描述符有数据到达，有客户端连接
                //表示有新的客户端连接进来了
                struct sockaddr_in cliaddr; 
                int len = sizeof cliaddr;
                int cfd = accept(lfd, (struct sockaddr *)&cliaddr, &len);

                epev.events = EPOLLIN;
                epev.data.fd = cfd;
                epoll_ctl(epfd, EPOLL_CTL_ADD, cfd, &epev);
            }else{
                //有数据到达，需要通信
                char buf[5] = {0};
                int len = read(curfd,buf,sizeof(buf));
                if(len == -1)
                {
                    perror("read");
                    exit(-1);
                }
                else if(len == 0)
                {
                    printf("client closed...\n");
                    epoll_ctl(epfd,EPOLL_CTL_DEL,curfd,NULL);
                    close(curfd);
                }else if(len > 0)
                {
                    printf("read buff = %s\n",buf);
                    write(curfd,buf,strlen(buf)+1);
                }
            }
            
        }
    }
    close(lfd);
    close(epfd);

    return 0;
    
}