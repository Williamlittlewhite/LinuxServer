// #include <sys/types.h> 包含flags宏定义
// #include <sys/stat.h>
// #include <fcntl.h>  函数名在此

// int open(const char *pathname, int flags, mode_t mode);
        // 参数：
        //     -pathname： 要创建的文件的路径
        //     -flags：对文件的操作权限和其他的设置 
        //         -必选项  O_RDONLY, O_WRONLY, or O_RDWR 这三个设置是互斥的
        //         -可选项  O_CREATE 文件不存在创建新文件
        //     -mode：八进制的数，表示创建出的新的文件的操作权限 比如：0775
                // 最终的权限是： mode & ~umask  rwx 111->7 
                // ~umask = 0777-0002(umask=0002)=0775 
                // 0777&0775=0775  
                //umask的作用就是抹去某些权限使得权限合理 可以在linux终端改变 也可以在程序设置
        //      flags参数是一个int类型的数据，占四个字节，32位
        //      flags 32个位，每1位就是标志位，所以按位或。

#include <sys/types.h> 
#include <sys/stat.h>
#include <fcntl.h>  
#include <unistd.h>
#include<stdio.h>
int main(){
    //创建一个新的文件
    int fd = open("create.txt",O_RDWR | O_CREAT,0777);
    if(fd == -1)
        {
            perror("open");
        }
    //关闭
    close(fd);
    return 0;
}