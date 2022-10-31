#include<stdio.h>
#define PI 3.14
int main(){
    //这是测试代码
    int sum=PI+10;
#ifdef DEBUG
    printf("这个是用来调试的log信息\n");
#endif
    int a=5;
    int b=a;
    int c=b;
    int d=c;
    /*
    编译器会优化为a=5
    b=5
    c=5
    d=5
    防止反编译，不容易看逻辑，而且还有些内存的优化
    */
    printf("hello world\n");
    return 0;
}


