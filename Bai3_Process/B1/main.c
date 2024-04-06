#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

int main(){
    pid_t child_pid;
    
    child_pid=fork();

    if(child_pid>=0){
        if(0==child_pid){
            printf("I am child process,my PID %d,my parent PID %d\n",getpid(),getppid());
        }else{
            printf("I am parent process,PID %d\n",getpid());
            while(1);
        }
    }else{
        printf("Fork() unsucessfully\n");
    }
    return 0;
}