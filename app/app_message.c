
#include"log/log.h"
#include "cJSON/cJSON.h"
#include "app_common.h"
#include <string.h>
#include <stdlib.h>

//chars格式： conn_type, id_len,msg_len,id,msg   
//eg:1 2 4 XX abcd  conn_type=1, id_len=2, msg_len=4, id=XX, msg=abcd
/*
    1 2 4是十进制，直接强转成字符串后，十进制1 2 4对应ascii码的字符显示不出来， 所以需要转成16进制的数字形式存在字符串里
    为什么不能直接写成'1' '2' '4',用的时候-'0'解析 呢？
    因为不一定十进制只有一位，可能有两位甚至三位，二16进制都是两位， 解析时，格式比较统一，方便

*/
//对应 json格式: {conn_type:1, id_hex:5858,msg_hex:61626364}

char* app_message_chars2Json(char* chars, int chars_len)
{
    // 1. 从chars中读取出conn_type, id_len, msg_len, id  msg
    int conn_type = chars[0];
    int id_len = chars[1];
    int msg_len =chars [2];

    // 检查chars_len是否正确
    if(chars_len != 3 + id_len + msg_len)
    {
        log_error("chars_len不正确!");
        return NULL;
    }


    char id[id_len];
    memcpy(id,chars+3,id_len);
    char msg[msg_len];
    memcpy(msg,chars+3+id_len,msg_len);

    // 2. 生成16进制的id和msg字符串
    char* id_hex = app_common_chars2Hex(id,id_len);
    char* msg_hex = app_common_chars2Hex(msg,msg_len);

    // 3. 生成json格式消息 ---拼接
    cJSON * root_obj = cJSON_CreateObject();
    cJSON_AddNumberToObject(root_obj,"conn_type",conn_type);
    cJSON_AddStringToObject(root_obj,"id",id_hex);
    cJSON_AddStringToObject(root_obj,"msg",msg_hex);
    char* json = cJSON_PrintUnformatted(root_obj);          //这也是malloc出来的，外部用完后也得释放
    
    //释放内存
    cJSON_Delete(root_obj);
    free(id_hex);
    free(msg_hex);

    //返回json格式消息
    return json;
}


int app_message_json2Chars(char* json,char* chars_buf,int buf_size)
{
    //1. 解析json， 取出conn_type,id_hex,msg_hex
    cJSON*root_obj = cJSON_Parse(json);
    int conn_type = cJSON_GetObjectItem(root_obj,"conn_type")->valueint;
    char* id_hexstr =cJSON_GetObjectItem(root_obj,"id")->valuestring;
    char* msg_hexstr =cJSON_GetObjectItem(root_obj,"msg")->valuestring;
    
    //2.将16进制的id和msg字符串转为chars类型的id和msg  app_common_hex2Chars
    int id_len =-1;
    int msg_len =-1;
    char* id = app_common_hex2Chars(id_hexstr,&id_len);
    char* msg = app_common_hex2Chars(msg_hexstr,&msg_len);
    
    // 检查buf_size是否足够

    //3. 向chars_buf中拼接字符数组消息
    chars_buf[0]=conn_type;
    chars_buf[1]=id_len;
    chars_buf[2]=msg_len;
    memcpy(chars_buf+3,id,id_len);
    memcpy(chars_buf+3+id_len,msg,msg_len);

    
    //4. 释放内存
    cJSON_Delete(root_obj);
    free(id);
    free(msg);

    //5. 返回buf有效数据的总长度
    return 3+id_len+msg_len;



}

