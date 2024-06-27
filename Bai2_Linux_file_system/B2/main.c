#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<unistd.h>
int main()
{
    int fd,number_write,x;
    char buf1[15]="I am from UET!";
    char buf2[16]="I am from PTIT!";

    fd=open("./hello.txt",O_RDWR|O_APPEND|O_CREAT);
    if(fd==-1)
    {
        printf("Unable to open file!");
        return 0;;
    }else{
        printf("Open file hello.txt!\n");
    }

    number_write=write(fd,buf1,strlen(buf1));
    if(number_write==-1)
    {
        printf("Unable to write to file!\n");
        return 0;
    }
    printf("Write %d bytes to hello.txt\n", number_write);
    
    x=lseek(fd,SEEK_SET,0);
    if(x==-1)
    {
        printf("Unable to seek file!\n");
        return 0;
    }else{
        printf("x=%d\n",x);
    }

    number_write=write(fd,buf2,strlen(buf2));
    if(number_write==-1)
    {
        printf("Unable to write to file!\n");
        return 0;
    }
    printf("Write %d bytes to hello.txt\n", number_write);

    printf("When you open a file with the O_APPEND flag, any data written to the file will always be appended to the end of the file, regardless of where you use lseek to change the file pointer position\n");
    printf("In the above program, although lseek has been used to set the file pointer to the beginning of the file (position 0), when writing is called, the data will still be written to the end of the file.");
    close(fd);
    return 0;
}
