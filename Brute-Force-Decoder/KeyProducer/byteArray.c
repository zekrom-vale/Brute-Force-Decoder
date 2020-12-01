#include "byteArray.h"
/**
* Incriments the array by the given value
* @param arr the byte array to inciment
* @param inc the value to incriment by
* @param size the size of the array
*/
bool byte_array_inc(byte* arr, int inc, size_t size, size_t* prevSize){
	assert(inc>0); //There is no support for decrementing
	//Add the value
	int val=((int)*arr)+inc;
	//If there is overflow roll it over
	if(val<=MAX){
		*arr=val;
		return true;
	}
	//Set the value that will fit
	*arr=val%(MAX+1);
	//Get the overflow for the next space
	int overflow=val/MAX;
	for(int i=1; i<size; i++){
		//Add the overflow
		val=(int)(*(arr+i))+overflow;
		//If there is no current overflow
		if(val<=MAX){
			//Set the value
			*(arr+i)=val;
			if(*prevSize<i+1)*prevSize=i+1;
			return true;
		}
		//Set the value that will fit
		*(arr+i)=val%(MAX+1);
		//Find the next oveflow value
		overflow=val/MAX;
	}
	//Ran out of array space
	return false;
}
