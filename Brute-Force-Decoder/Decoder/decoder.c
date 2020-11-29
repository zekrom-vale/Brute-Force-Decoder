#include "decoder.h"
#define TRD "Decoder"

/**
 * Copies the cypher text and sets up the size wrapper
 * Also, sets the proper null terminator for strings `\0`
 * @return The size wrapped copy of the cypher text to decode
 */
struct sizeWrapper* decode_copy(){
	struct sizeWrapper* txt=malloc(sizeof(struct sizeWrapper));
	size_t textSize=cypherText->size;
	//Copy the text so we can modify the text itself
	char* text=calloc(textSize+1, sizeof(byte));
	memcpy(text, cypherText->arr, textSize);
	//Add the `\0`
	text[textSize]=0;
	txt->arr=text;
	txt->size=textSize; //strlen does not inclue `\0`
	return txt;
}

struct sizeWrapper* decode_decode(struct sizeWrapper* wrp){
	//Unwrap
	byte* key=wrp->arr;
	size_t keySize=wrp->size;
	struct sizeWrapper* txt=decode_copy();
	//Access with
	//txt->arr
	//txt->size (This now includes `\0`)
	
	//Literaly just apply the XOR to each character
	//EXCEPT the last one, that must be `\0`
	//You should be able to set that after if you want to
		//But update the one above

	//Decode



	return txt;
}

void* decoder_main(void* v){
	//Standard thread start
	struct decodeArgs* args=v;

	print_id(TRD, "Starting Thread");

	//Loop until told to stop
	while(!halt){
		//Fetch the key to decode
		sem_wait(&semKey);
		struct sizeWrapper* wrp=queue_pop(keyQueue);
#if KEY_MAX!=0
		sem_post(&semKeyMax);
#endif
		//End fetch
		
		struct keyTextWrap* keyTextWrap=malloc(sizeof(struct keyTextWrap));
		keyTextWrap->text=decode_decode(wrp);
		keyTextWrap->key=wrp;

		//Put text into the queue for next
#if TEXT_MAX!=0
		sem_wait(&semTextMax);
#endif
		queue_push(textQueue, keyTextWrap);
		sem_post(&semText);
		//End put
	}

	print_id(TRD, "Ending Thread");

	//Standard thread end
	if(args)free(args);
	return NULL;
}