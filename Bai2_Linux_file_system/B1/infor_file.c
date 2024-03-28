#include <stdio.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
int main()
{
    //Khai bao bien stat
    struct stat fileInfo;

    //Lay thong tin file test.txt
    int status=stat("test.txt",&fileInfo);

    //Kiem tra loi
    if(status!=0)
    {
        perror("Lỗi file");
        return 1;
    }

    //In ra thong tin file
    printf("File Type: ");
    switch(fileInfo.st_mode & S_IFMT){
        case S_IFREG:printf("Regular file\n");break;
        case S_IFDIR:printf("Directory\n"); break;
        case S_IFLNK:printf("Symlink\n"); break;
        case S_IFSOCK:printf("Socket\n"); break;
        case S_IFIFO:printf("FIFO/pipr\n");break;
        case S_IFBLK:printf("Block Device\n");break;
        case S_IFCHR:printf("Character device\n");break;
        default: printf("Unknown\n"); break;
    }
    printf("File name: test.txt\n");
    printf("Last file modification: %s", ctime(&fileInfo.st_mtime));
    printf("File size: %ld bytes\n", (intmax_t)fileInfo.st_size);
  
    return 0;
}