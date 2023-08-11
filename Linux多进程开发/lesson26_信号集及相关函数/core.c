#include <stdio.h>
#include <string.h>
/*不生成core文件时候可用该命令sudo service apport stop*/
/*core-file core可以调试core文件信息*/
int main()
{
    char *buf;
    strcpy(buf, "hello");
    return 0;
}