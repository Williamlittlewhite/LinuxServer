/*

    网络通信时,需要将主机字节序转换成网络字节序(大端),
    另外一段获取数据以后根据情况将网络字节序转换成主机字节序。

    #include <arpa/inet.h>
    // 转换端口
    uint16_t htons(uint16_t hostshort);     // 主机字节序 - 网络字节序
    uint16_t ntohs(uint16_t netshort);      // 网络字节序 - 主机字节序
    // 转IP
    uint32_t htonl(uint32_t hostlong);      // 主机字节序 - 网络字节序
    uint32_t ntohl(uint32_t netlong);       // 网络字节序 - 主机字节序
*/

#include<stdio.h>
#include<arpa/inet.h>

int main()
{
    //htons 转换端口
    unsigned short a = 0x0102;
    unsigned short b = htons(a);
    printf("%x\n",b);

    //htonl 转换ip
    char buf[4] =  {192,168,1,100};
    int num = *(int*)buf;
    int sum  = htonl(num);
    unsigned char *p = (char*)&sum;
    printf("%d %d %d %d\n",*p,*(p+1),*(p+2),*(p+3));

    //ntohs
    unsigned char buf1[4] = {1,1,168,192};
    int num1 = *(int*)buf1;
    int sum2 = ntohl(num1);
    unsigned char* p1 = (unsigned char*)&sum2;
    printf("%d %d %d %d\n",*p1,*(p1+1),*(p1+2),*(p1+3));
    //ntohl
}