#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <malloc.h>
#include <stdbool.h>

#include "json-c/json.h"
#include "json-c/json_tokener.h"

struct ip_node {
    char   *addr;
    int    mask;
};

struct if_node {
    char  *name;
    char  *state;
    int   mtu;
    struct ip_node  ipaddr;
};


struct unit_node {
	char *name;
	int index;
	struct if_node  ipif;	
};


//char *gisu_json_str = (char *)"{\"name\":\"GISU\",\"index\":0,\"interfaces\":[{\"name\":\"EL7\",\"state\":\"UP\",\"mtu\":\"888\",\"ipaddr\":[{\"addr\":\"192.99.1.100\",\"mask\":\"24\"}]}]}";

//char *json_str = (char*) "{\"name\":\"gisu\",\"index\":1,\"interfaces\" :[{\"name\" : \"eth0\",\"state\" : \"UP\",\"mtu\"   : 1500,\"ipaddr\" : {\"addr\" : \"100\",\"mask\" : 24}}]}";

//char *gisu_json_str = (char*) "{\"name\":\"GISU\",\"index\":0,\"interfaces\" :[{\"name\" : \"eth0\",\"state\" : \"UP\",\"mtu\"   : 1500,\"ipaddr\" : {\"addr\" : \"192.168.1100\",\"mask\" : 24}}]}";


char *gisu_json_str = (char*) "{\"name\":\"GISU\",\"index\":0,\"interfaces\" :{\"name\" : \"eth0\",\"state\" : \"UP\",\"mtu\"   : 1500,\"ipaddr\" : {\"addr\" : \"192.168.1.100\",\"mask\" : 24}}}";

char * test_str = (char*)"{\"state\":\"WO-EX\",\"index\":1}";

#define UNIT_NAME  "name"
#define UNIT_INDEX "index"
#define UNIT_STATE "state"
#define INTERFACE  "interfaces"
#define IF_NAME    "name"
#define IF_STATE   "state"
#define IF_MTU    "mtu"
#define IP        "ipaddr"
#define IP_ADDR   "addr"
#define IP_MASK    "mask"


json_bool fill_str_field_in_node(struct json_object *node_jobj_ptr, char **str_field, char *field_name)
{
    struct json_object *new_jobj = NULL;
    json_bool res = false;
    char *tmp = NULL;
    
    if ((res = json_object_object_get_ex(node_jobj_ptr, field_name, &new_jobj)))
    {
		//printf("get node obj \n");
        tmp = (char *)json_object_get_string(new_jobj);
        *str_field = strdup(tmp);
    }
	//printf("get str:%s \n", *str_field);
    return res;
}


json_bool fill_int_field_in_node(struct json_object *node_jobj_ptr, int *int_field, char *field_name)
{
    struct json_object *new_jobj = NULL;
    json_bool res = false;
    
    if ((res = json_object_object_get_ex(node_jobj_ptr, field_name, &new_jobj)))
    {
        *int_field = json_object_get_int(new_jobj);
    }

    return res;
}



int get_unit_struct(struct  json_object *unit_jobj)
{
    struct unit_node unit ;
	struct json_object *if_jobj = NULL;
	struct json_object *ip_jobj = NULL;
	json_bool res = false;
	
	fill_str_field_in_node(unit_jobj, &unit.name, (char *)UNIT_NAME);
	fill_int_field_in_node(unit_jobj, &unit.index, (char *)UNIT_INDEX);

    if (true == (res = json_object_object_get_ex(unit_jobj, (char *)INTERFACE, &if_jobj))) {
    	fill_str_field_in_node(if_jobj, &unit.ipif.name, (char *)IF_NAME);
   		fill_str_field_in_node(if_jobj, &unit.ipif.state, (char *)IF_STATE);
	    fill_int_field_in_node(if_jobj, &unit.ipif.mtu, (char *)IF_MTU);
	}

	
	if (true == (res = json_object_object_get_ex(if_jobj, (char *)IP, &ip_jobj))) {
		fill_str_field_in_node(ip_jobj, &unit.ipif.ipaddr.addr, (char *)IP_ADDR);
	    fill_int_field_in_node(ip_jobj, &unit.ipif.ipaddr.mask, (char *)IP_MASK);
	}

	printf("unit name:%-5s   index:%d \n", unit.name, unit.index);
	printf("if name:%-5s     state:%s,   mtu:%d \n", unit.ipif.name, unit.ipif.state, unit.ipif.mtu);
	printf("ip addr:%-5s     mask:%d \n", unit.ipif.ipaddr.addr, unit.ipif.ipaddr.mask);

	return 0;
}



int main(int argc, char** argv)
{
    //int str_len = 0;
	json_object *new_obj = NULL;
	//char * test_str1 = (char*)"{\"state\":\"WO-EX\",\"index\":1}";
	printf("json to C test \n");
	printf("json string:%s \n \n \n", gisu_json_str);
		
	
	//str_len = strlen(gisu_json_str);
	new_obj = json_tokener_parse(gisu_json_str);	
    //state_obj = json_object_object_get(new_obj, UNIT_STATE);	
	//state = (char*) json_object_get_string(state_obj);
	get_unit_struct(new_obj);
	return 0;
}


