#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
struct sockInfo
{
    int fd; //通信的文件描述符
    pthread_t tid;
    struct sockaddr_in cliaddr;
};

void* working(void* arg)
{
    //子线程和客户端通信 cfd 客户端的信息 线程号
    //获取客户端的信息
    struct sockInfo* pinfo = (struct sockInfo*)arg;
    printf("传参后的fd:%d\n",pinfo->fd);
    char cliIP[16];
    inet_ntop(AF_INET,&pinfo->cliaddr.sin_addr.s_addr,cliIP,sizeof cliIP);
    unsigned short cliport = ntohs(pinfo->cliaddr.sin_port);   
    printf("%d\n",pinfo->fd);
    printf("client ip is : %s, prot is %d\n",cliIP,cliport);

    //接受客户端发来的数据
    char recvBuff[1024] = {0};
    while (1)
    {
        int len = read(pinfo->fd,recvBuff,sizeof recvBuff);
        if(len == -1)
        {
            perror("read");
            exit(-1);
        }
        else if(len > 0)
        {
            printf("receive client data : %s\n",recvBuff);
        }
        else
        {
            printf("客户端断开连接了...\n");
            break;
        }

        write(pinfo->fd,recvBuff,strlen(recvBuff)+1);
    
    }
    close(pinfo->fd);
    return NULL;
}

struct sockInfo sockinfos[128];
int main()
{
    //初始化数据
    int maxlen = sizeof(sockinfos)/sizeof(sockinfos[0]);
    for(int i = 0; i < maxlen; ++i)
    {
        bzero(&sockinfos[i],sizeof(sockinfos[i]));
        sockinfos[i].fd = -1;
        sockinfos[i].tid = -1;
    }
    int lfd = socket(AF_INET,SOCK_STREAM,0);
    if(lfd == -1)
    {
        perror("socket");
        exit(-1);
    }
    struct sockaddr_in saddr;
    saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = INADDR_ANY;
    saddr.sin_port = htons(9999);

    int ret = bind(lfd,(struct sockaddr*)&saddr,sizeof saddr);
    if(ret == -1)
    {
        perror("bind");
        exit(0);
    }

    ret = listen(lfd,5);
    if(ret == -1)
    {
        perror("listen");
        exit(-1);
    }


    //循环等待客户端连接,一旦一个客户端连接进来,就创建一个子线程进行通信
    while(1)
    {
        struct sockaddr_in cliaddr;
        int len = sizeof cliaddr;
        //接受连接
        int cfd = accept(lfd,(struct sockaddr*)&cliaddr,&len);
        struct sockInfo* pinfo;

        for(int i = 0; i < maxlen; ++i)
        {
            //从这个数组中找到一个可以用的sockInfo元素
            if(sockinfos[i].fd == -1){
                pinfo = &sockinfos[i];
                break;
            }
            if(i == maxlen - 1)
            {
                sleep(1);
                i = 0;
            }
        }
      
        pinfo->fd = cfd;
        printf("传参前的fd:%d\n",pinfo->fd);
        memcpy(&pinfo->cliaddr,&cliaddr,len);
        //创建子线程
        pthread_create(&pinfo->tid,NULL,working,pinfo);
        
        pthread_detach(pinfo->tid);
    }
    close(lfd);
    return 0;
}