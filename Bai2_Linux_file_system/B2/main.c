#include<stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include<string.h>
int main(void){
    int fd;
    int numb_write,x;
    char buf[19]="I am from Vietnam\n";
    fd=open("./hello.txt",O_RDWR|O_APPEND);
    if(fd==-1){
        printf("Can not open file\n");
        return 0;
    }else{
        printf("Open file hello.txt\n");
    }
    x=lseek(fd,0,SEEK_SET);
    if(x==-1){
        printf("Error\n");
        return 0;
    }else{
        printf("Lseek sucessful\n");
    }
    numb_write=write(fd,buf,strlen(buf));
    printf("Write %d bytes to hello.txt\n", numb_write);
    close(fd);
    return 0;
}