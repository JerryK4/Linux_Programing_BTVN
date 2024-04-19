#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
#include<time.h>


void sig_handler(int num)
{
    printf("Im signal handler :%d\n",num);
    exit(EXIT_SUCCESS);
}

int main(int argc,char const *argv[])
{
    if(signal(SIGINT,sig_handler)==SIG_ERR)
    {
        fprintf(stderr,"Cannot handle SIGINT\n");
        exit(EXIT_FAILURE);
    }
    sigset_t mask_old,mask_new;
    sigemptyset(&mask_old);
    sigemptyset(&mask_new);
    //sigaddset(&mask_new,SIGINT);//Block truoc khi ktra
    sigprocmask(SIG_SETMASK,&mask_new,&mask_old);

    
    //Kiểm tra xem SIGINT có bị block hay không.
    if(sigismember(&mask_new,SIGINT)==0){
        printf("SIGINT khong bi Block\n");
        sigprocmask(SIG_BLOCK,&mask_new,&mask_old);//Block
        sigaddset(&mask_new,SIGINT);
        sigprocmask(SIG_SETMASK,&mask_new,&mask_old);
    }else if(sigismember(&mask_new,SIGINT)==1){
        // sigaddset(&mask_new,SIGINT);
        sigprocmask(SIG_SETMASK,&mask_new,&mask_old);
        printf("SIGINT bi Block\n");
        sleep(10);
        sigprocmask(SIG_UNBLOCK,&mask_new,&mask_old);
        //sigemptyset(&mask_new);
    }
    while(1);
}