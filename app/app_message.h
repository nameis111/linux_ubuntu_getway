#if !defined(__APP_MASSAGE_H)
#define __APP_MASSAGE_H


//字符数组消息内容： 连接类型+id长度+消息长度 +id +消息    数据部分用16进制存  
//因为有些字符在字符串中无法显示， eg：十进制为1 2 4对应的字符 就无法显示。所以用16进制传，受到后再解析 保证数据完整性
//json格式是字符串形式，所以当需要通过json格式传输数据时，要注意这点




/**
 * @brief   字符数组消息转json
 * @param   chars   字符数组消息
 * @param   chars_len  字符数组消息的长度
 * @return  返回json消息
 */

char* app_message_chars2Json(char* chars, int chars_len);


/**
 * @brief   json消息转字符数组消息
 * @param   json    json消息
 * @param   chars_buf   字符数组消息的容器
 * @param   buf_size    字符数组容器的容量大小
 * @return  返回字符数组消息的长度
 */
int app_message_json2Chars(char* json,char* chars_buf,int buf_size);



#endif // __APP_MASSAGE_H

