#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
#include<time.h>

void sig_handler1(int num)
{
    printf("Im signal handler1:%d\n",num);
    exit(EXIT_SUCCESS);
}

void sig_handler2(int num)
{
    printf("Im signal handler1:%d\n",num);
    exit(EXIT_SUCCESS);
}
int main(int argc,char const *argv[])
{
    if(signal(SIGUSR1,sig_handler1)==SIG_ERR)
    {
        fprintf(stderr,"Cannot handle SIGUSR1\n");
        exit(EXIT_FAILURE);
    }

     if(signal(SIGUSR2,sig_handler2)==SIG_ERR)
    {
        fprintf(stderr,"Cannot handle SIGUSR2\n");
        exit(EXIT_FAILURE);
    }

    while(1)
    {
        printf("Hello World\n");
        sleep(2);
    }
}