/*************************************************************************
    > File Name: time.c
    > Author: Wu Jiaju
    > Mail: jiaju.wu@nokia.com 
    > Created Time: Tue 10 May 2016 10:56:21 AM CST
 ************************************************************************/

#include<stdio.h>  
#include<time.h>  
  
int main()  
{  
    /* 获取当前日历时间 */
    time_t t;  
    t = time(&t);  
    printf("the current time of seconds:[%d], string is:[%s]\n",t, ctime(&t));  

    /* 日历时间转成本地tm结构时间 */
    struct tm* tm_t = localtime(&t);  
    char buf[100];  
    strftime(buf, 100,"%F %T",tm_t);   
    printf("get struct tm tm_t from seconds is:[%s]\n", buf);  

    /* tm结构时间转成日历时间 */
    time_t t1 = mktime(tm_t);  
    printf("get seconds from struct tm:[%d]\n",t);  

    /* 自定义tm结构时间 */
    struct tm tm_t1;  
    tm_t1.tm_year=2012-1900;  
    tm_t1.tm_mon=0;  
    tm_t1.tm_mday=16;  
    tm_t1.tm_hour=0;  
    tm_t1.tm_sec=0;  
    tm_t1.tm_min=0;  
    strftime(buf, 100,"%F %T",&tm_t1);   
    printf("the struct tm tm_t1 is:[%s]\n", buf);  

}
