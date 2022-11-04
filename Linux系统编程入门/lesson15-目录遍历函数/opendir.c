/*
        //打开一个目录
        #include <sys/types.h>
        #include <dirent.h>
        DIR *opendir(const char *name);
            参数：
                - name: 需要打开的目录的名称
            返回值：
                DIR*类型， 目录流信息
                错误返回NULL

        //读取目录中的数据
        #include <dirent.h>
        struct dirent *readdir(DIR *dirp);
            -参数： dirp是opendir返回的结果
            -返回值：struct dirent 代表读取到的文件的信息
                    读取到了末尾或者失败了，返回NULL
        
        //关闭目录
        #include <sys/types.h>
        #include <dirent.h>
        int closedir(DIR *drip);
*/
#include<sys/types.h>
#include<dirent.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
//读取某个目录下所有的普通文件的个数 ./a.out lesson15
int getFileNum(const char* path);
int main(int argc,char** argv)
{
    if(argc<2)
    {
        printf("%s path\n",argv[0]);
        return -1;
    }
    int num = getFileNum(argv[1]);
    printf("普通文件的个数为:%d\n",num);
    return 0;
}

//用于获取目录下所有普通文件的个数
int getFileNum(const char* path)
{
    //1.打开目录
    DIR* dir = opendir(path);

    if(dir == NULL)
    {
        perror("opendir");
        exit(0);
    }
    //记录普通文件的个数
    int total = 0;
    struct dirent* ptr;
    while ((ptr = readdir(dir))!=NULL)
    {
        //获取名称
        char* dname = ptr->d_name;
      
        //忽略.和..
        if(strcmp(dname,".") == 0 || strcmp(dname,"..")==0)
            continue;
        
        if(ptr->d_type == DT_DIR)
        {
            char newpath[256];
            sprintf(newpath,"%s/%s",path,dname);
            total += getFileNum(newpath);
        }
        if(ptr->d_type == DT_REG)
            ++total;
        
    }
    //关闭目录
    closedir(dir);
    return total;
    
    
}