

/**************    struct  **************************/
typedef struct  {
             word  next_record [2] ;
             word  prev_record ;
             byte  prev_element ;
             byte  this_rec_type ; 
}  ganfil_t ;
          





/*************   json format   **********************/

          
{
	"ganfil":
	{
	    "next_record": 
	        [
					2,
	                3
			],
        "prev_record": 1,
        "prev_element": 1,
        "this_rec_type": 1,
    }
}



"{\"ganfil\":{ \"next_record\": [2,3],\"prev_record\": 1,\"prev_element\": 1,\"this_rec_type\": 1}}"