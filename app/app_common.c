#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
long app_common_getCurrentTime()
{

    struct timeval tv;
    gettimeofday(&tv,NULL);
    return tv.tv_sec*1000+tv.tv_usec/1000;
}


/**
 * [abcd] ->"60626364"     
 * 传进来的是字符数组，需要把他转成16进制的字符串，然后直接return出去被别人接收，  所以需要malloc空间， 所以需要free
 * 
 * 因为数据是按照长度直接从字符串里面截取出来的，所以没有'\0' 是字符数组
 * 
 * 字符数组与字符串的区别：结尾'\0'
 */
char *app_common_chars2Hex(char* chars, int chars_len)
{
    // 1. 为16进制字符串申请空间
    char* hexstr = (char*)malloc(chars_len*2+1);            /* a->61 一位变两位， 结尾‘\0’ 所以要+1 */
    
    // 2. 遍历chars的每个字符，转成16进制存入 hexstr
    for(int i=0;i<chars_len;i++)
    {
        sprintf(hexstr+i*2,"%02X",chars[i]);
    }

    // 3. 向hexstr添加'\0'
    hexstr[chars_len*2]='\0';

    //4. 返回hexstr
    return hexstr;
    
}


/**
 * "60626364" -> [abcd]      
 */
char* app_common_hex2Chars(char *hexstr,int* char_len)
{

    //1. malloc空间 存16进制变成的正常数据     strlen算的长度已经去掉了'\0'
    char* chars= (char*)malloc(strlen(hexstr)/2);

    unsigned int values=0;
    //2.遍历hexstr 把两个16进制字符变成1个对应字符 存到chars中
    for(int i=0;i<strlen(hexstr);i+=2)
    {
        sscanf(hexstr+i,"%02X",&values);  /*源，读取源的格式，写入目标。因为chars是char类型的， 
                                                                    所以16进制写进取后 自动变成char了*/
        
        chars[i/2]=values;
    }

    //3. 把chars的长度赋值给char_len
    *char_len = strlen(chars);
    
    //4. 返回chars
    return chars;
}



