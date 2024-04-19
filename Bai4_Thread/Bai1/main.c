#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>

pthread_t thread1,thread2;
typedef struct{
    int year;
    int month;
    int day;
}date;

typedef struct{
    char name[30];
    date d;
    char phonenumber[12];
    char hometown[30];
}human;

static void *thread_handle(void *args){
    pthread_t tid=pthread_self();
    human *data=(human *)args;

    if(pthread_equal(tid,thread1)){
        printf("I am thread1\n");
        sleep(3);
    }else{
        printf("I am thread2\n");
        printf("My name is %s.My birthday is %d/%d/%d.My phonenumber is %s.I live in %s\n",data->name,data->d.day,data->d.month,data->d.year,data->phonenumber,data->hometown);

    }
}

void destring(char x[]){
    size_t len=strlen(x);
    if(x[len-1]=='\n'){
        x[len-1]='\0';
    }
}
int main(int argc,char const *argv[])
{
    int ret;

    human data;

    memset(&data,0x0,sizeof(data));

    char n[30];
    printf("My name: ");
    fflush(stdin),fgets(n,sizeof(n)+1,stdin);destring(n);
    strncpy(data.name,n,sizeof(data.name));

    int a,b,c;printf("My birthday: ");scanf("%d %d %d",&a,&b,&c);getchar();
    data.d.day=c,data.d.month=b,data.d.year=a;

    char p[30];
    printf("My phonenumber: ");
    fflush(stdin),fgets(p,sizeof(p)+1,stdin);destring(p);
    strncpy(data.phonenumber,p,sizeof(data.phonenumber));

    char h[30];
    printf("My home town: ");
    fflush(stdin),fgets(h,sizeof(h)+1,stdin);destring(h);
    strncpy(data.hometown,h,sizeof(data.hometown));

    if(ret=pthread_create(&thread1,NULL,&thread_handle,NULL)){
        printf("pthread_create() error number: %d\n",ret);
        return -1;
    }
    if(ret=pthread_create(&thread2,NULL,&thread_handle,&data)){
        printf("pthread_create() error number: %d\n",ret);
        return -1;
    }

    return 0;
}