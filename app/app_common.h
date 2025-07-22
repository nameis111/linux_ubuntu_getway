#if !defined(__APP_COMMON_H)
#define __APP_COMMON_H


/**
 * @brief 获取当前时间戳    ms
 * @return long 当前时间戳
 */
long app_common_getCurrentTime();



/**
 * @brief 字符数组转16进制  字符串     [abcd] -> "61626364\0"
 * @param chars 字符数组
 * @param chars_len 字符数组长度
 * @return 16进制字符串
 */
char *app_common_chars2Hex(char* chars, int chars_len);

/**
 * @brief 16进制字符串转字符数组   "61626364" ->[a,b,c,d]
 * @param hexstr  16进制字符串
 * @param char_len 用来接收转成字符数组后的长度
 * @return 16进制字符串转成正常的数据
 */
char* app_common_hex2Chars(char *hexstr,int* char_len);


#endif // __APP_COMMON_H
