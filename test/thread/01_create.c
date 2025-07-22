
#define _GNU_SOURCE
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

// first线程函数
void *first_thread_fun(void* arg)
{
    printf("first线程%d正在执行\n",gettid());
    return NULL;

}

// second线程函数
void *second_thread_fun(void* arg)
{
    printf("second线程%d正在执行\n",gettid());
    return NULL;

}

int main(int argc, char const *argv[])
{
    printf("主线程%d开始执行\n",gettid());

    pthread_t pt1,pt2;   //声明线程标识变量
    pthread_create(&pt1,NULL,first_thread_fun,NULL);               //线程标识变量, 线程属性指针 eg:优先级等内容  , 线程函数, 线程函数参数
    pthread_create(&pt1,NULL,second_thread_fun,NULL);
    
    
    // 等待2个分线程执行完毕
    pthread_join(pt1,NULL);   //线程标识,用来接收子线程返回值的函数     
    //pthread_join(pt2,NULL);   
    
    printf("主线程%d执行完毕 pt1=%ld  pt2=%ld   \n",gettid(),pt1,pt2);
    //printf("主线程%d执行完毕\n",gettid());
    return 0;
}
