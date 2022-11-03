/*
        #include <unistd.h>
        #include <sys/types.h>
        int truncate(const char *path, off_t length);
            作用:缩减或者扩展文件的尺寸到指定大小
            参数:
                - path: 需要修改的文件路径
                -length: 需要最终文件变成的大小  缩减砍掉最后一部分 扩展用空字符替换
*/
#include<unistd.h>
#include<sys/types.h>
#include<stdio.h>
int main()
{
    int ret = truncate("b.txt",5);
    if(ret==-1)
    {
        perror("truncate");
        return -1;
    }
    return 0;
}