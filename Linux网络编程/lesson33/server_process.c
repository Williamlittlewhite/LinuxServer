#include<stdio.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<errno.h>
void recycleChild(int arg)
{
    while (1)
    {
        int ret = waitpid(-1,NULL,WNOHANG);
        if(ret == -1)
        {
            //所有的子进程都回收完了
            break;
        }
        else if(ret == 0)
        {
            //还有子进程活着
            break;
        }
        else
        {
            printf("子进程 %d 被回收了\n",ret);
        }
    }
    
}
int main()
{
    //注册信号捕捉回收子进程资源
    struct sigaction act;
    act.sa_flags = 0;
    sigemptyset(&act.sa_mask);
    act.sa_handler = recycleChild;

    
    sigaction(SIGCHLD,&act,NULL);


    //创建socket
    int lfd = socket(AF_INET,SOCK_STREAM,0);
    if(lfd == -1)
    {
        perror("socket");
        exit(-1);
    }
    //绑定
    struct sockaddr_in saddr;
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(9999);
    saddr.sin_addr.s_addr = INADDR_ANY;
    int ret = bind(lfd,(struct sockaddr*)&saddr,sizeof saddr);
    if(ret == -1)
    {
        perror("bind");
        exit(0);
    }

    //监听
    ret = listen(lfd,5);
    if(ret == -1)
    {
        perror("listen");
        exit(-1);
    }

    //不断循环等待客户端连接
    while (1)
    {
        struct sockaddr_in cliaddr;
        int len = sizeof cliaddr;
        //接受连接
        int cfd = accept(lfd,(struct sockaddr*)&cliaddr,&len); //软中断执行完成以后再连接会有EINTR错误，必须处理该错误才能再次连接
        if(cfd == -1)
        {
            if(errno == EINTR)
                continue;
            perror("accept");
            exit(-1);
        }

        //每一个连接进来，创建一个子进程跟用户通信
        pid_t pid = fork();
        if(pid == 0)
        {
            //子进程
            //获取客户端的信息
            char cliIP[16];
            inet_ntop(AF_INET,&cliaddr.sin_addr.s_addr,cliIP,sizeof cliIP);
            unsigned short cliport = ntohs(cliaddr.sin_port);   

            printf("client ip is : %s, prot is %d\n",cliIP,cliport);

            //接受客户端发来的数据
            char recvBuff[1024] = {0};
            while (1)
            {
                int len = read(cfd,recvBuff,sizeof recvBuff);
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

                write(cfd,recvBuff,strlen(recvBuff)+1);
            
            }
            close(cfd);
            exit(0); //退出当前子进程
        }
    }
    close(lfd);
    return 0;
}