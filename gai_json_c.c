/*************************************************************************
    > File Name: gai_json_c.c
    > Author: Wu Jiaju
    > Mail: jiaju.wu@nokia.com 
    > Created Time: Fri 08 Apr 2016 12:43:35 PM CST
 ************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <json-c/json.h>
#include <json-c/json_tokener.h>
#include <hiredis/hiredis.h>

typedef unsigned short word;
typedef unsigned char byte;
typedef word gan_rec_number_t;

typedef struct  {
    gan_rec_number_t  continue_index ;
    word  result_index ;
    struct  {
        /* byte*/ unsigned  ctn_in_ganfil;
        /* byte*/ unsigned  ctn_in_reserved;
        /* byte*/ unsigned  result_in_gtr;
        /* byte*/ unsigned  reserve;
        /* byte*/ unsigned  record_in_use;
    }  indicator ;
    byte  prev_element ;
    gan_rec_number_t  prev_record ;
    word  gan_link_count ;
    word  reserve ;
}  gaifil_t ;
char *gaifil_json = "{\"gaifil\":{\"continue_index\":1,\"result_index\":2,\"indicator\":{\"ctn_in_ganfil\":3,\"ctn_in_reserved\":4,\"result_in_gtr\":5,\"reserve\":6,\"record_in_use\":7,},\"prev_element\":8,\"prev_record\":9,\"gan_link_count\":10,\"reserve\":11}}";

void save_redis(json_object *gaifil_object)
{
    int timeout = 1000;
    struct timeval tv;
    tv.tv_sec = timeout / 1000;
    tv.tv_usec = timeout * 1000;
    redisContext* c = redisConnectWithTimeout("127.0.0.1", 6379, tv);
    if (c->err) {
        redisFree(c);
        return;
    }

    //const char* command1 = "set stest1 value1";
    redisReply* r = (redisReply*)redisCommand(c, "set gaifil %s", json_object_to_json_string(gaifil_object));
    if (NULL == r) {
        redisFree(c);
        return;
    }

    freeReplyObject(r);
    redisFree(c);
    printf("Succeed to execute command[%s].\n", json_object_to_json_string(gaifil_object));
    return;
}

int main(int argc, char *argv[])
{
    struct json_object *gaifil_object = NULL;
    gaifil_object = json_object_new_object();
    if (NULL == gaifil_object)
    {
        printf("new json object gaifil failed.\n");
        return;
    }

    struct json_object *gai_object = NULL;
    gai_object = json_object_new_object();
    if (NULL == gai_object)
    {
        printf("new json object gai failed.\n");
        return;
    }

    struct json_object *ind_object = NULL;
    ind_object = json_object_new_object();
    if (NULL == ind_object)
    {
        json_object_put(gai_object);//free
        printf("new json object ind failed.\n");
        return;
    }
    json_object_object_add(ind_object, "ctn_in_ganfil", json_object_new_string("3"));
    json_object_object_add(ind_object, "ctn_in_reserved", json_object_new_string("4"));
    json_object_object_add(ind_object, "result_in_gtr", json_object_new_string("5"));
    json_object_object_add(ind_object, "reserve", json_object_new_string("6"));
    json_object_object_add(ind_object, "record_in_use", json_object_new_int(7));

    json_object_object_add(gai_object, "continue_index", json_object_new_int(1));
    json_object_object_add(gai_object, "result_index", json_object_new_int(2));
    json_object_object_add(gai_object, "prev_element", json_object_new_int(8));
    json_object_object_add(gai_object, "prev_record", json_object_new_int(9));
    json_object_object_add(gai_object, "gan_link_count", json_object_new_int(10));
    json_object_object_add(gai_object, "reserve", json_object_new_int(11));

    json_object_object_add(gaifil_object, "gaifil", gai_object);
    json_object_object_add(gai_object, "indicator", ind_object);
    
    printf("%s\n", json_object_to_json_string(gaifil_object));
    save_redis(gaifil_object);
}
