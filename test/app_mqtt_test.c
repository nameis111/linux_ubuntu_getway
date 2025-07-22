#include "app_mqtt.h"
#include "log/log.h"
#include "unistd.h"


int app_mqtt_recv(char *json)
{
    log_debug("准备处理受到的远程消息数据:%s",json); 
}

int main(int argc, char const *argv[])
{
    app_mqtt_init();

    app_mqtt_registerRecvCallback(app_mqtt_recv);

    app_mqtt_send("{\"conn_type\":1,\"id\":\"5858\",\"msg\":\"61626364\"}");

    sleep(50);

    app_mqtt_close();
    return 0;
}
