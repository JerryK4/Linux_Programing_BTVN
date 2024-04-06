#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

int main(int argc,char const *argv[])
{
    pid_t child_pid;
    int status;
    int rv;

    child_pid=fork();

    if(child_pid>=0){
        if(0==child_pid){
            printf("Im child process with PID :%d\n",getpid());
            while(1);
            //printf("Child process terminate after 5 seconds\n");
            //sleep(5);
            //exit(0);
        }else{
            //while(1);
            rv=wait(&status);
            if(rv==-1){
                printf("Wait() unsucessfully\n");
            }
            printf("Im parent process with PID:%d\n",getpid());

            printf("My child process with PTD:%d\n",rv);

            if(WIFEXITED(status)){
                printf("Normally termination,status: %d\n",WEXITSTATUS(status));
            }else if(WIFSIGNALED(status)){
                printf("Killed by signal,status:%d\n",WTERMSIG(status));
            }
        }
    }else{
        printf("Fork() unsucessfully");
    }
    return 0;
}