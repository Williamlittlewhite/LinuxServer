//使用内存映射实现文件拷贝的功能

/*
    思路：
        1.对原始的文件进行内存映射
        2.创建一个新的文件(拓展该文件)
        3.把新文件的数据映射到内存当中
        4.通过内存拷贝将第一个文件的内存数据拷贝到新的文件内容中
        5.释放资源
*/
#include<stdio.h>
#include<unistd.h>
#include<sys/mman.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
#include<string.h>
int main()
{
    //1.对原始的文件进行内存映射
    int fd = open("english.txt",O_RDWR);
    if(fd == -1){
        perror("oepn");
        exit(0);
    }
    // 获取原始文件的大小
    int len = lseek(fd,0,SEEK_END);
    //2.创建一个新文件(拓展该文件)
    int fd1 = open("cpy.txt",O_RDWR|O_CREAT,0664);
    if(fd1 == -1)
    {
        perror("open");
        exit(0);
    }
    //对新创建的文件进行拓展
    truncate("cpy.txt",len);
    write(fd1," ",1);

    //3.分别做内存映射
    void* ptr = mmap(NULL,len,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    void* ptr1 = mmap(NULL,len,PROT_READ|PROT_WRITE,MAP_SHARED,fd1,0);

    if(ptr == MAP_FAILED){
        perror("mmap");
        exit(0);
    }
    if(ptr1 == MAP_FAILED){
        perror("mmap");
        exit(0);
    }

    // 内存拷贝
    memcpy(ptr1,ptr,len);

    //释放资源
    munmap(ptr1,len);
    munmap(ptr,len);

    close(fd);
    close(fd1);
    return 0;
}