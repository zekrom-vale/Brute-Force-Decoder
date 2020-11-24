#include "validator.h"
void* decoder_main(void* v){
	//Standard thread start
	struct decodeArgs* args=v;

	//Loop until told to stop
	while(!halt){
		//Retreve text
		sem_wait(&semText);
		//May need to send the size as well
		//We do need to send the key to print
		char* text=queue_pop(textQueue);
#if TEXT_MAX!=0
		sem_post(&semTextMax);
#endif
		//End retreve
		
		//------------//
		//  Validate  //
		//------------//

		//If a match is found:
		//halt=true;
	}

	//Standard thread end
	if(args)free(args);
	return NULL;
}