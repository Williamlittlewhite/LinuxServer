#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <signal.h>
#include "ThreadPool/cond.h"
#include "ThreadPool/sem.h"
#include "ThreadPool/locker.h"
#include "ThreadPool/threadpool.h"
#include "http_conn/http_conn.h"
#define MAX_FD 65535 //最大的文件描述符个数
#define MAX_EVENT_NUMBER 10000 //监听的最大事件的数量
//注册信号捕捉
void addsig(int sig, void(*handler)(int))
{
    struct sigaction sa;
    memset(&sa , 0 ,sizeof sa);
    sa.sa_handler = handler;
    sigemptyset(&sa.sa_mask);
    sigaction(sig,&sa,NULL);
}
//添加文件描述符到epoll当中
extern void addfd(int epollfd, int fd, bool oneshot);
//从epoll中删除文件描述符
extern void removefd(int epollfd, int fd);
//从epoll中修改文件描述符
extern void modfd(int epollfd, int fd, int ev);
int main(int argc,char** argv)
{
    if(argc <= 1)
    {
        printf("按照如下格式运行: %s port_number\n",basename(argv[0]));
        exit(-1);
    }

    //获取端口号
    int port = atoi(argv[1]);

    //对SIGPIPE信号进行处理
    addsig(SIGPIPE,SIG_IGN);//SIGPIPE信号直接忽略

    //创建线程池，初始化线程池
    threadpool<http_conn>* pool = NULL;

    try{
        pool = new threadpool<http_conn>;
    }catch(...){
        exit(-1);
    }

    //创建一个数组用于保存所有的客户端信息
    http_conn* users = new http_conn[MAX_FD];
    int listenfd = socket(PF_INET,SOCK_STREAM,0);
    if(listenfd == -1)
    {
        perror("listenfd");
        exit(-1);
    }

    //设置端口复用,一定在绑定之前去设置，防止挥手期间的等待时间
    int reuse = 1;
    setsockopt(listenfd,SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof reuse);

    //绑定
    struct sockaddr_in saddr;
    saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = INADDR_ANY;
    saddr.sin_port = htons(port);
    int ret = bind(listenfd,(struct sockaddr*)&saddr,sizeof saddr);
    if(ret == -1)
    {
        perror("bind");
        exit(-1);
    }

    //监听
    listen(listenfd,8);

    //创建epoll对象和事件数组
    epoll_event events[MAX_EVENT_NUMBER];
    int epollfd = epoll_create(1000);

    //将监听的文件描述符添加到epoll对象中
    addfd(epollfd,listenfd,false);
    http_conn::m_epollfd = epollfd;

    while(1)
    {
        int num = epoll_wait(epollfd,events,MAX_EVENT_NUMBER,-1);
        if(num == -1 && errno != EINTR){  //系统调用被捕获信号中断时候会设置EINTR错误 需要特殊处理
            printf("epoll failure\n");
            break;
        }
        //循环遍历事件数组
        for(int i = 0; i < num; ++i)
        {
            int sockfd = events[i].data.fd;
            if(sockfd == listenfd){
                //有客户端连接进来
                struct sockaddr_in client_addr;
                socklen_t client_addr_len = sizeof client_addr;
                int connfd = accept(listenfd,(struct sockaddr*)&client_addr,&client_addr_len);
                if(connfd == -1)
                {
                    perror("connect");
                    exit(-1);
                }
                if(http_conn::m_user_count >= MAX_FD)
                {
                    //目前连接数满了
                    //给客户端写一个信息:服务器内部正在忙碌
                    close(connfd);
                    continue;
                }
                //将新的客户的数据接受并且更新后，放到数组中
                users[connfd].update(connfd,client_addr);   
            }else if(events[i].events & (EPOLLRDHUP | EPOLLHUP | EPOLLERR))
            {
                //对方异常断开或者发生错误等事件
                users[sockfd].close_conn();
            }else if(events[i].events & EPOLLIN)
            {
                if(users[sockfd].read())
                    //一次性读完所有数据
                    pool->append(users+sockfd);
                else
                    users[sockfd].close_conn();
            }else if(events[i].events & EPOLLOUT)
            {
                if(!users[sockfd].write())
                    //一次性写完所有数据
                    users[sockfd].close_conn();
            }
        }
    }
    close(epollfd);
    close(listenfd);
    delete[] users;
    delete pool;
    return 0;
}