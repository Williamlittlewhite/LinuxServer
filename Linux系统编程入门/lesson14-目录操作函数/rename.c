#include <stdio.h>
int rename(const char *oldpath, const char *newpath);

int main()
{
    int ret = rename("aaa","bbb");
    if(ret == -1)
    {
        perror("rename");
        return -1;
    }
    return 0;
}