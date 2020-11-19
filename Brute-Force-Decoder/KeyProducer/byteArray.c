#include "byteArray.h"
/**
* Incriments the array by the given value
* @param arr the byte array to inciment
* @param inc the value to incriment by
* @param size the size of the array
*/

bool byte_array_inc(byte* arr, byte inc, size_t size){
	assert(inc>0);
	//Requires more logic and not needed
	assert(inc<2*MAX-1);
	//Add the value
	*arr+=inc;
	//If there is overflow roll it over
	if(*arr>MAX)*arr%=(MAX+1);

	else return true;
	for(int i=1; i<size; i++){
		//Add the overflow
		if(++*(arr+i)>MAX)*(arr+i)%=(MAX+1);
		else return true;
	}
	return false;
}
