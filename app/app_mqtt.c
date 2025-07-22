#include "app_mqtt.h"
#include "string.h"
#include "log/log.h"
#include <MQTTClient.h>




static MQTTClient_message pubmsg = MQTTClient_message_initializer;
MQTTClient client;
MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;

static int (*recv_callback)(char* json) = NULL;   //函数指针变量, 用于接收回调函数  -用来收数据  

// 发送消息回调函数
static void delivered(void *context, MQTTClient_deliveryToken dt)
{
    log_debug("消息发送成功!");
}
 

// 收到远程消息回调函数
// 返回1表示消息处理成功,0表示消息处理失败  而回调函数返回1表示失败,0表示成功,所以得取反
static int msgarrvd(void *context, char *topicName, int topicLen, MQTTClient_message *message)
{
    int result = 0;

    if(recv_callback)
    {
        result = recv_callback(message->payload) ==0? 1:0;
    }
   
    MQTTClient_freeMessage(&message);
    MQTTClient_free(topicName);
    return result;
}
 
//连接断开回调函数
static void connlost(void *context, char *cause)
{
   log_error("MQTT连接断开,原因:%s",cause);
}
 

/**
 * 初始化mqtt客户端
 */
int app_mqtt_init()
{
    // 初始化mqtt客户端
    //MQTTClient_create(&client,ADDRESS,CLIENTID,MQTTCLIENT_PERSISTENCE_NONE,NULL); --创建客户端
    if( MQTTClient_create(&client,ADDRESS,CLIENTID,MQTTCLIENT_PERSISTENCE_NONE,NULL)!=MQTTCLIENT_SUCCESS) //创建失败就返回-1
    {
        log_error("创建MQTT客户端失败");
        return -1;
    }

    // 设置回调函数
    if(MQTTClient_setCallbacks(client,NULL,connlost,msgarrvd,delivered)!= MQTTCLIENT_SUCCESS)
    {
        //销毁已经创建的客户端
        MQTTClient_destroy(&client);

        log_error("设置徽调函数失败");
        return -1;
    }

    // 连接到MQTT服务器
    if(MQTTClient_connect(client,&conn_opts)!= MQTTCLIENT_SUCCESS)
    {
        //销毁已经创建的客户端
        MQTTClient_destroy(&client);
        log_error("连接MQTT服务器失败");
        return -1;
    }


    // 订阅主题
    if(MQTTClient_subscribe(client,TOPIC_R2G,QOS) != MQTTCLIENT_SUCCESS)
    {
        //此时已经连接成功了, 所以需要先断开连接再销毁
        MQTTClient_disconnect(client,TIMEOUT);
        MQTTClient_destroy(&client);

        log_error("订阅主题失败");
        return -1;
    }

    log_debug("MQTT客户端初始化成功");
    return 0;

}


/**
 * 关闭mqtt客户端
 */
void app_mqtt_close()
{
    MQTTClient_disconnect(client,TIMEOUT);
    MQTTClient_destroy(&client);
}


/**
 * 发送消息给远程服务器
 */
int app_mqtt_send(char* json)
{
    // 指定要发送的数据
    pubmsg.payload = json;
    pubmsg.payloadlen = strlen(json) +1;
    pubmsg.qos = QOS;

    
    if(MQTTClient_publishMessage(client,TOPIC_G2R,&pubmsg,NULL) != MQTTCLIENT_SUCCESS )
    {
        log_error("发送消息失败");
        return -1;
    }

    log_debug("发送消息成功:%s",json);
    return 0;
}

/**
 * 注册接收处理远程消息的函数
 */
void app_mqtt_registerRecvCallback(int (*callback) (char *json))
{
    recv_callback = callback;
}
