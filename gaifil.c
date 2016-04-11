/*************************************************************************
    > File Name: gaifil.c
    > Author: Wu Jiaju
    > Mail: jiaju.wu@nokia.com 
    > Created Time: Wed 23 Dec 2015 01:51:54 PM CST
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

//char *gaifil_json = "{\"gaifil\":{\"continue_index\":1,\"result_index\":2,\"indicator\":{\"ctn_in_ganfil\":3,\"ctn_in_reserved\":4,\"result_in_gtr\":5,\"reserve\":6,\"record_in_use\":7,},\"prev_element\":8,\"prev_record\":9,\"gan_link_count\":10,\"reserve\":11}}";

json_bool fill_int_field_in_node(json_object *node_json_obj, int *int_field, char *field_name)
{
    json_object *new_json_object = NULL;
    json_bool result = false;

    if (true == (result = json_object_object_get_ex(node_json_obj, field_name, &new_json_object)))
    {
        *int_field = json_object_get_int(new_json_object);
    }

    return result;
}

json_bool get_indicator_struct(json_object *prev_obj, gaifil_t *gaifil)
{
    json_object *indicator_obj = NULL;
    json_bool result = false;

    if (true == (result = json_object_object_get_ex(prev_obj, (char *)"indicator", &indicator_obj))) {
        fill_int_field_in_node(indicator_obj, (int *)&(gaifil->indicator.ctn_in_ganfil), (char *)"ctn_in_ganfil");
        fill_int_field_in_node(indicator_obj, (int *)&(gaifil->indicator.ctn_in_reserved), (char *)"ctn_in_reserved");
        fill_int_field_in_node(indicator_obj, (int *)&(gaifil->indicator.result_in_gtr), (char *)"result_in_gtr");
        fill_int_field_in_node(indicator_obj, (int *)&(gaifil->indicator.reserve), (char *)"reserve");
        fill_int_field_in_node(indicator_obj, (int *)&(gaifil->indicator.record_in_use), (char *)"record_in_use");
    }
    return result;
}

json_bool get_gaifil_t_struct(json_object *gaifil_obj, gaifil_t *gaifil)
{
    json_object *prev_obj = NULL;
    json_bool result = false;

    if (true == (result = json_object_object_get_ex(gaifil_obj, (char *)"gaifil", &prev_obj))) {
        fill_int_field_in_node(prev_obj, (int *)&gaifil->continue_index, (char *)"continue_index");
        fill_int_field_in_node(prev_obj, (int *)&gaifil->result_index, (char *)"result_index");
        get_indicator_struct(prev_obj, gaifil);
        fill_int_field_in_node(prev_obj, (int *)&gaifil->prev_element, (char *)"prev_element");
        fill_int_field_in_node(prev_obj, (int *)&gaifil->prev_record, (char *)"prev_record");
        fill_int_field_in_node(prev_obj, (int *)&gaifil->gan_link_count, (char *)"gan_link_count");
        fill_int_field_in_node(prev_obj, (int *)&gaifil->reserve, (char *)"reserve");
    }
    return result;
}

void get_redis(char *result)
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
    redisReply* r = (redisReply*)redisCommand(c, "get gaifil");
    if (NULL == r) {
        redisFree(c);
        return;
    }

    memcpy(result, r->str, r->len);
    freeReplyObject(r);
    redisFree(c);
    return;
}

int main(int argc, char *argv[])
{
    struct json_object *new_obj = NULL;
    gaifil_t gaifil;
    char gaifil_json[1024];

    get_redis(gaifil_json);
    new_obj = json_tokener_parse(gaifil_json);
    get_gaifil_t_struct(new_obj, &gaifil);
    printf("gaifil:\n");
    printf("      continue_index: %d\n", gaifil.continue_index);
    printf("      result_index: %d\n", gaifil.result_index);
    printf("      indicator:\n");
    printf("               ctn_in_ganfil: %d\n", gaifil.indicator.ctn_in_ganfil);
    printf("               ctn_in_reserved: %d\n", gaifil.indicator.ctn_in_reserved);
    printf("               result_in_gtr: %d\n", gaifil.indicator.result_in_gtr);
    printf("               reserve: %d\n", gaifil.indicator.reserve);
    printf("               record_in_use: %d\n", gaifil.indicator.record_in_use);
    printf("      prev_element: %d\n", gaifil.prev_element);
    printf("      prev_record: %d\n", gaifil.prev_record);
    printf("      gan_link_count: %d\n", gaifil.gan_link_count);
    printf("      prev_reserve: %d\n", gaifil.reserve);

    return 0;   
}
