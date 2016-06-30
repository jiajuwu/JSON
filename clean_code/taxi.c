/*************************************************************************
    > File Name: taxi.c
    > Author: Wu Jiaju
    > Mail: jiaju.wu@nokia.com 
    > Created Time: Tue 10 May 2016 10:10:45 AM CST
 ************************************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <time.h>

/* 
 * @ingroup clean_code
 * The function datetime is judge the time of user when use the taxi or truck whether need
 * the night service charge in the night.
 *
 * @param [out]
 *      void
 *
 * @param [in]
 *      struct tm time, the time who begin to use the taxi or truck
 *      struct tm begin_time, the beginning time of billable hours
 *      struct tm end_time, the end time of billable hours
 *
 * @return
 *      true, if return value is true, that means need the nigth service charge
 *      false, not need the night service charge
 */

bool datetime(struct tm time, struct tm begin_time, struct tm end_time)
{
    if (begin_time.tm_hour >= end_time.tm_hour) /* 20:00-5:00 */
    {
        if ((time.tm_hour >= begin_time.tm_hour) || (time.tm_hour < end_time.tm_hour))
            return true;
        else
            return false;
    }
    else /* 1:00-7:00 */
    {
        if ((time.tm_hour >= begin_time.tm_hour) && (time.tm_hour < end_time.tm_hour))
            return true;
        else
            return false;
    }
}

/*
 * main function
 */
int main(int argc, char *argv[])
{
    bool ret = false;
    struct tm time, begin_time, end_time;

    if (argc < 4)
    {
        printf("the argc error\n");
    }
    printf("%s %s %s\n", argv[1], argv[2], argv[3]);

    strptime(argv[1], "%H:%M", &time);
    strptime(argv[2], "%H:%M", &begin_time);
    strptime(argv[3], "%H:%M", &end_time);

    if ((time.tm_hour > 24) || (begin_time.tm_hour > 24) || (end_time.tm_hour > 24))
        printf("Input the hour error\n");
    if ((time.tm_min > 59) || (begin_time.tm_min > 59) || (end_time.tm_min > 59))
        printf("Input the minute error\n");
    printf("%d:%d\n", time.tm_hour, time.tm_min);

    ret = datetime(time, begin_time, end_time);
    if (true == ret)
        printf("Need the night service charge\n");
    else
        printf("Not need the night service charge\n");
    return 0;
}
