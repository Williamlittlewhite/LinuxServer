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
    /*动态库加载方法： 
1.DT_RPATH段
    DT_RPATH段我们改变不了，直接下一个。
2.将libcalc.so的路径加入到环境变量LD_LIBRARY_PATH中
    2.1在终端直接加 export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/wcj/projec/lesson4/library/lib
    2.2打开.bashrc文件vim ~/.bashrc vi中，shift+G可以跳到最后一行，小写的o可以向下插入一行，在最后一行插入：export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/wcj/projec/lesson4/library/lib
       保存之后，使修改生效：. .bashrc == source .bashrc
    2.3永久配置--系统级别 打开/etc/profile文件 sudo vim /etc/profile 在最后一行添加：export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/wcj/projec/lesson4/library/lib
        使修改生效： source /etc/profile
3.将libcalc.so的路径加入到/etc/ld.so.cache文件列表中
    sudo vi /etc/ld.so.conf
    添加路径：/home/wcj/projec/lesson4/library/lib
    保存之后更新 sudo ldconfig
4.将libcalc.so直接放到/lib/、/usr/lib目录中
    */
}
