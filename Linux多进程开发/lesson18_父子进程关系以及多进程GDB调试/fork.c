/*
#include <sys/types.h>
#include <unistd.h>

pid_t fork(void);
    作用：用于创建子进程
    返回值：
        fork()的返回值返回2次，一次是在父进程，一次是在子进程
        在父进程中返回创建的子进程的ID，
        在子进程中返回0
        如何区分父进程和子进程：通过fork的返回值。
        在父进程中返回-1，表示创建子进程失败，并且设置errno

    父子进程之间的关系：
    区别：
        1.fork()函数的返回值不同
            父进程中: >0 返回的是子进程的ID
            子进程中: =0
        2.pcb中的一些数据
            当前进程的id pid
            当前进程的父进程的id ppid
            信号集
    共同点:
        某些状态下：子进程刚被创建出来，还没有执行任何的写数据的操作
            - 用户区的数据
            - 文件描述符表

    父子进程对变量是不是共享的？
        - 刚开始的时候，是一样的，共享的。如果修改了数据，不共享了。
        - 读时共享（子进程被创建，两个进程没有进行任何写的操作），写时拷贝。
*/
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
int main()
{
    int num = 10;
    // 创建子进程
    pid_t pid = fork();

    // 判断是父进程还是子进程
    if (pid > 0)
    {
        // 如果大于0，返回的是创建的子进程的进程号  是父进程的返回值
        printf("pid : %d\n", pid);
        printf("I am parent process, pid : %d, ppid : %d\n", getpid(), getppid());
        printf("parent num : %d\n", num);
        num += 10;
        printf("parent num : %d\n", num);
    }
    else if (pid == 0) // 等于0是子进程的返回值
    {
        // 当前是子进程
        printf("I am child process, pid : %d, ppid : %d\n", getpid(), getppid());
        printf("child num : %d\n", num);
        num += 100;
        printf("chid num : %d\n", num);
    }

    for (int i = 0; i < 5; ++i)
    {
        printf("i : %d, pid : %d\n", i, getpid()); // 证明父子进程是交替进行的
        sleep(1);
    }
    return 0;
}

/*
实际上，更准确来说，Linux的fork()使用是通过写时拷贝(copy-on-write)实现的
写时拷贝是一种可以推迟甚至避免拷贝数据的技术
内核此时并不复制整个进程的地址空间，而是让父子进程共享同一个地址空间
只用在需要写入的时候才会复制地址空间，从而使得各个进程拥有各自的地址空间
也就是说，资源的复制是在需要写入的时候才会进行，在此之前，只有以只读方式共享
注意：fork之后的父子进程共享文件
fork产生的子进程与父进程相同的文件描述符指向相同的文件表，引用计数增加，共享文件偏移指针。
*/