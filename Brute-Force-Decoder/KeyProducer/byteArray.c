#include "byteArray.h"
/**
* Incriments the array by the given value
* @param arr the byte array to inciment
* @param inc the value to incriment by
* @param size the size of the array
*/
bool byte_array_inc(byte* arr, int inc, size_t size){
	assert(inc>0);
	//Add the value
	int val=((int)*arr)+(int)inc;
	//If there is overflow roll it over
	if(val<=MAX)return true;

	*arr=val%(MAX+1);
	int overflow=val/MAX;
	for(int i=1; i<size; i++){
		//Add the overflow
		val=(int)(*(arr+i))+overflow;
		if(val<=MAX)return true;
		*(arr+i)=val%(MAX+1);
		overflow=val/MAX;
	}
	return false;
}
