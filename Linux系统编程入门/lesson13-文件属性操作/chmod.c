/*
        #include <sys/stat.h>
        int chmod(const char *pathname, mode_t mode);
            作用：修改文件的权限
            参数：
                - pathname: 需要修改的文件的路径
                - mode:需要修改的权限值，八进制的数
            返回：
                成功返回0 失败返回-1
*/      
#include<sys/stat.h>
#include<unistd.h>
#include<stdio.h>
int main()
{
    int ret = chmod("a.txt",0775);
    if(ret == -1)
    {
        perror("chmod");
        return -1;
    }
    return 0;
}