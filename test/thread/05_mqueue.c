
#include <mqueue.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

static char* mq_name = "/my_mq"; // /代表:  /dev/mqueue目录,  所有的队列文件只能在mqueue里面
static  mqd_t mq_fd;              // 队列描述符,   description 描述符

// first线程函数
void *first_thread_fun(void* arg)
{
    printf("first线程正在执行,发送消息 \n");
    //发送消息
    mq_send(mq_fd,"hello",6,0);    //消息队列描述符, 消息, 消息长度, 消息优先级
    return NULL;

}

// second线程函数
void *second_thread_fun(void* arg)
{
    sleep(1);

    printf("second线程正在执行,接收消息\n");

    // 接收消息
    char buf[100];
    ssize_t len = mq_receive(mq_fd,buf,100,NULL); //消息队列描述符, 消息, 消息长度, 消息优先级
    printf("接收到的消息是:%s,长度是:%ld\n",buf,len);

    return NULL;

}

int main(int argc, char const *argv[])
{
    printf("主线程开始执行\n");

    //创建队列
    struct mq_attr attr;            // attribute 属性
    attr.mq_maxmsg = 10;            // 最大消息数
    attr.mq_msgsize = 100;         // 每个消息的最大字节数

    /*
    创建消息队列
    0_RDWD:  可读可写
    0_CREAT:  如果不存在,就创建
    0666:  八进制写法的文件权限组合
    &attr:  指向消息队列的指针
    返回 队列的文件描述符
    */
   mq_fd = mq_open(mq_name, O_RDWR|O_CREAT,0644,&attr);

   if(mq_fd == -1)
   {
    printf("创建消息队列失败");
    return -1;
   }




    pthread_t pt1,pt2;   //声明线程标识变量
    pthread_create(&pt1,NULL,first_thread_fun,NULL);               //线程标识变量, 线程属性指针 eg:优先级等内容  , 线程函数, 线程函数参数
    pthread_create(&pt1,NULL,second_thread_fun,NULL);


    // 等待2个分线程执行完毕
    pthread_join(pt1,NULL);   //线程标识,用来接收子线程返回值的函数


    printf("主线程执行完毕\n");


    //关闭并删除队列
    mq_close(mq_fd);
    mq_unlink(mq_name);

    return 0;
}
