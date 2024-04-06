#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<signal.h>

void func(int signum){
    printf("I am in func()\n");
    wait(NULL);
}

int main(int argc,char const *argv[]){
    pid_t child_pid=fork();

    if(child_pid>=0){
        if(child_pid==0){
            printf("I am Child,my PID:%d\n",getpid());
            //while(1);
        }else{
            /**When a child is terminated, a corresponding SIGCHLD signal 
             * is delivered to the parent
            */

           signal(SIGCHLD,func);
           printf("I am Parent,my PID:%d\n",getpid());
           while(1);
        }
    }else{
        printf("Fork unsucessfully\n");
    }
}