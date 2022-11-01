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

#本节课分为测试源文件，lib文件夹里面放libxxx.a静态库文件，src文件夹里放入编写的源文件，include文件夹里放入头文件
#编译本节课的内容的命令gcc main.c -o main -I ./include/ -l calc -L ./lib/
#-o 起另外一个名  -I 指定头文件搜索文件夹 -l 指定使用的静态库 -L 指定使用的静态库的路径
