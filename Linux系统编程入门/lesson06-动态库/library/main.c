#include <stdio.h>
#include "head.h"

int main()
{
    int a = 20;
    int b = 12;
    printf("a = %d, b = %d\n", a, b);
    printf("a + b = %d\n", add(a, b));
    printf("a - b = %d\n", subtract(a, b));
    printf("a * b = %d\n", multiply(a, b));
    printf("a / b = %f\n", divide(a, b));
    return 0;
}

//动态库制作gcc fpic -c xxx.c   gcc -shared xxx.o -o libxxx.so
//使用动态库 gcc main.c -o main -I ./include/ -l calc -L ./lib/ 会报错
//动态库依赖list dynamic dependencies检查动态库依赖 ldd main
//
/*当系统加载可执行代码时候，能够知道其所依赖的库的名字，但是还需要知道绝对路径。此时就需要系统的动态载入器来获取该绝对路径。
对于elf格式的可执行程序，是由ld-linux.so来完成的，它先后搜索elf文件的 DT_RPATH段(虚拟地址空间用户不能改～) 
——> 环境变量LD_LIBRARY_PATH(用户级即.bashrcsource .bashrc 系统级即sudo vim /etc/profile 然后 source /etc/profile) 
——> /etc/ld.so.cache文件列表(sudo vim /etc/ld.so.conf然后sudo ldconfig) 
——> /lib/，/usr/lib目录找到库文件后将其载入内存(这种不推荐用)*/
