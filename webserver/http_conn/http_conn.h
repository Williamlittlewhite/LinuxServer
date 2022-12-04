#ifndef __HTTP_CONN_H
#define __HTTP_CONN_H
#include <sys/epoll.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <stdarg.h>
#include <errno.h>
#include "../ThreadPool/locker.h"
class http_conn
{
private:
    
public:
    http_conn();
    ~http_conn();

    void process();//处理客户端请求
};


#endif