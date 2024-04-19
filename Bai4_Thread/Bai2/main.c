#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>
#include<fcntl.h>

pthread_t thread1,thread2,thread3;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t producer = PTHREAD_COND_INITIALIZER,consumer = PTHREAD_COND_INITIALIZER;
int check=0;
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

human data={"",0,0,0,"",""};

void destring(char x[]){
    size_t len=strlen(x);
    if(x[len-1]=='\n'){
        x[len-1]='\0';
    }
}
static void *thread_handle1(void *args){
    if(check==0){
        //human *data=(human *)args;
        //Mutex
        pthread_mutex_lock(&lock);

        //ready in advance when pthread_cond_signal() is called
        //pthread_cond_wait(&consumer,&lock);
        //Nhap du lieu
        memset(&data,0x0,sizeof(data));
        char n[30];
        printf("My name: ");
        fflush(stdin),fgets(n,sizeof(n),stdin);destring(n);
        strncpy(data.name,n,sizeof(data.name));

        int a,b,c;printf("My birthday: ");scanf("%d %d %d",&a,&b,&c);getchar();
        data.d.day=c,data.d.month=b,data.d.year=a;

        char p[30];
        printf("My phonenumber: ");
        fflush(stdin),fgets(p,sizeof(p),stdin);destring(p);
        strncpy(data.phonenumber,p,sizeof(data.phonenumber));

        char h[30];
        printf("My home town: ");
        fflush(stdin),fgets(h,sizeof(h),stdin);destring(h);
        strncpy(data.hometown,h,sizeof(data.hometown));
        //Khoa
        pthread_cond_signal(&producer);
        pthread_mutex_unlock(&lock);
    }else{
        //human *data=(human *)args;
        //Mutex
        pthread_mutex_lock(&lock);
        pthread_cond_wait(&consumer,&lock);
        //ready in advance when pthread_cond_signal() is called
        
        //Nhap du lieu
        memset(&data,0x0,sizeof(data));
        char n[30];
        printf("My name: ");
        fflush(stdin),fgets(n,sizeof(n),stdin);destring(n);
        strncpy(data.name,n,sizeof(data.name));

        int a,b,c;printf("My birthday: ");scanf("%d %d %d",&a,&b,&c);getchar();
        data.d.day=c,data.d.month=b,data.d.year=a;

        char p[30];
        printf("My phonenumber: ");
        fflush(stdin),fgets(p,sizeof(p),stdin);destring(p);
        strncpy(data.phonenumber,p,sizeof(data.phonenumber));

        char h[30];
        printf("My home town: ");
        fflush(stdin),fgets(h,sizeof(h),stdin);destring(h);
        strncpy(data.hometown,h,sizeof(data.hometown));
        //Khoa
        pthread_cond_signal(&producer);
        pthread_mutex_unlock(&lock);
    }

}

static void *thread_handle2(void *args){
    human *data=(human *)args;
    //Xu ly mutex va condition variable
    pthread_mutex_lock(&lock);
    pthread_cond_wait(&producer,&lock);
    //Tao/Mo file va ghi file
    int fd;
    int numbwrite,x;
    fd=open("/home/manhjerry04/working_space/BTVN4/Bai2/thongtinsinhvien.txt",O_CREAT|O_RDWR|O_APPEND);
    if(fd==-1){
        printf("Can not open file\n");
    }
    char buf[1000];
    sprintf(buf, "%s %d/%d/%d %s %s\n", data->name,data->d.day,data->d.month,data->d.year,data->phonenumber,data->hometown);
    numbwrite=write(fd,buf,strlen(buf));
    close(fd);

    //Khoa
    pthread_cond_signal(&consumer);
    pthread_mutex_unlock(&lock);

}

static void *thread_handle3(void *args){
    pthread_mutex_lock(&lock);
    pthread_cond_wait(&consumer,&lock);

    char read[1000];
    FILE *fptr;
    fptr=fopen("./thongtinsinhvien.txt","r");
    fscanf(fptr,"%s",read);
    printf("%s\n",read);
    fclose(fptr);
    //Khoa
    check=1;
    pthread_cond_signal(&consumer);
    pthread_mutex_unlock(&lock);

}

int main(int argc,char const *argv[])
{
    int ret;
    while(1){
        if(ret=pthread_create(&thread1,NULL,&thread_handle1,NULL)){
            printf("pthread_create() error number: %d\n",ret);
            return -1;
        }
        if(ret=pthread_create(&thread2,NULL,&thread_handle2,&data)){
            printf("pthread_create() error number: %d\n",ret);
            return -1;
        }
        if(ret=pthread_create(&thread3,NULL,&thread_handle3,NULL)){
            printf("pthread_create() error number: %d\n",ret);
            return -1;
        }
    }
    // pthread_join(thread1,NULL);
    // pthread_join(thread2,NULL);
    // pthread_join(thread3,NULL);
    // pthread_exit(NULL);
    // return 0;
}
