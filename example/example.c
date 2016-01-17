#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#include "json-c/json.h"
#include "json-c/json_tokener.h"

typedef unsigned int word;
typedef unsigned char byte;


typedef struct  {
             word  next_record [2] ;
             word  prev_record ;
             byte  prev_element ;
             byte  this_rec_type ; 
}  ganfil_t ;


json_bool get_ganfil_t_struct(json_object *json_jobj, ganfil_t *ganfil);


char *string = "{\"ganfil\":{ \"next_record\": [2,3],\"prev_record\": 1,\"prev_element\": 1,\"this_rec_type\": 1,},\"prev_record\" : 100   }";


int main(int argc, char **argv)
{
	
	struct json_object  *new_obj = NULL;
	ganfil_t ganfil;
	new_obj = json_tokener_parse(string);
	get_ganfil_t_struct(new_obj, &ganfil);
	printf("ganfil struct: \n");
	printf("      next record[0] :  %d \n",ganfil.next_record[0]);
	printf("      next record[0] :  %d \n",ganfil.next_record[1]);
	printf("      prev_record    :  %d \n",ganfil.prev_record);
	printf("      prev_element   :  %d \n",ganfil.prev_element);
	printf("      this_rec_type  :  %d \n",ganfil.this_rec_type);

    return 0;
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

json_bool fill_data_in_array(json_object *json_jobj, int *int_field, char *field_name)
{
	json_object *new_jobj = NULL;
	json_object *array_jobj = NULL;
	json_bool res = false;	
	int array_len = 0;
	int index = 0;
	if ((res = json_object_object_get_ex(json_jobj, field_name, &new_jobj))) {
        array_len = json_object_array_length(new_jobj);
        for (index = 0; index < array_len; index++)
        {
            array_jobj = json_object_array_get_idx(new_jobj, index);
            int_field[index] = json_object_get_int(array_jobj);
        }
    }
	return res;
}

json_bool get_ganfil_t_struct(json_object *json_jobj, ganfil_t *ganfil)
{
	json_bool res = false;
	struct json_object *prev_jobj = NULL;

	if ((res = json_object_object_get_ex(json_jobj, (char*)"ganfil", &prev_jobj))) {
		fill_int_field_in_node(prev_jobj, (int*)&ganfil->prev_record, (char *)"prev_record");
		fill_int_field_in_node(prev_jobj, (int*)&ganfil->prev_element, (char *)"prev_element");
		fill_int_field_in_node(prev_jobj, (int*)&ganfil->this_rec_type, (char *)"this_rec_type");	
		fill_data_in_array(prev_jobj, (int*)(&ganfil->next_record), (char*)"next_record");
	}
	return res;
}

