#include "log/log.h"
#include "cJSON/cJSON.h"
#include <stdlib.h>
int main(int argc, char const *argv[])
{
    
    //1. 生成json字符串
    cJSON* root_obj = cJSON_CreateObject();   //cJSON 对象
    cJSON_AddStringToObject(root_obj,"name","tom");
    cJSON_AddNumberToObject(root_obj,"age",18);
    char *json = cJSON_PrintUnformatted(root_obj);  //把cjson对象 转换为字符串 ---这是malloc的内存，需要free
    log_debug("json:%s",json);

    //2. 解析json字符串
    cJSON* root_obj2 = cJSON_Parse(json);       //把json字符串 转化为cjson对象
    if(root_obj2 == NULL){
        log_error("解析json字符串失败");
        return -1;
    }
    char* name = cJSON_GetObjectItem(root_obj2,"name")->valuestring;
    int age = cJSON_GetObjectItem(root_obj2,"age")->valueint;
    log_debug("解析json字符串： name=%s,age=%d",name,age);
    
    //3. 释放内存
    cJSON_Delete(root_obj);
    cJSON_Delete(root_obj2);
    free(json);
    
    return 0;
}
