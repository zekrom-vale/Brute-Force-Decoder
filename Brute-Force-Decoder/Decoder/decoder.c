#include "decoder.h"
#define TRD "Decoder"

void rc4( byte* key,  int key_len,
	char* buff, int len);

/**
 * Copies the cypher text and sets up the size wrapper
 * Also, sets the proper null terminator for strings `\0`
 * @return The size wrapped copy of the cypher text to decode
 */
struct sizeWrapper* decode_copy(){
	struct sizeWrapper* txt=malloc(sizeof(struct sizeWrapper));
	size_t textSize=cypherText->size;
	//Copy the text so we can modify the text itself
	char* text=calloc(textSize-1, sizeof(byte));
	memcpy(text, cypherText->arr, textSize);
	//Add the `\0`
	text[textSize-1]='\0';
	txt->arr=text;
	txt->size=textSize-1; //strlen does not inclue `\0`
	return txt;
}

struct sizeWrapper* decode_decode(struct sizeWrapper* wrp){
	//Unwrap
	byte* key=wrp->arr;
	size_t keySize=wrp->size;
	struct sizeWrapper* txt=decode_copy();
	
	rc4(wrp->arr, wrp->size, txt->arr, txt->size);

	return txt;
}

void* decoder_main(void* v){
	//Standard thread start
	//decodeArgs* args=v;

	print_id(TRD, "Starting Thread");

	//Loop until told to stop
	while(!halt){
		//Fetch the key to decode
		sem_wait(&semKey);
		struct sizeWrapper* wrp=queue_pop(keyQueue);
#if KEY_MAX!=0
		sem_post(&semKeyMax);
#endif

		if(wrp==NULL)continue;
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
	//if(args)free(args);
	return NULL;
}

void swap( byte *p1, byte *p2){
	byte t = *p1;
	*p1 = *p2;
	*p2 = t;
}

void rc4_init( byte *key, int key_len, byte s[], byte t[]){
	int   i,j=0;
	char* k=key;
	//Initial values of both vectors
	for (i=0;i<256;i++){
		s[i] = i;
		t[i] = k[i%key_len];
	}
	//Initial permutation 
	for (i=0;i<256;i++){
		j = (j + s[i] + t[i])%256;
		swap(&s[i],&s[j]);
	}
}

void rc4( byte* key,  int key_len, char* buff, int len){
	byte s[256];
	byte t[256];
	rc4_init(key,key_len, s, t);
	//process a byte at a time
	unsigned long t1=0,t2=0;
	for (int i=0;i<len;i++){     
		t1 = (t1 + 1)%256;
		t2 = (t2 + s[t1])%256;
		swap(&s[t1],&s[t2]);
		byte val = (s[t1] + s[t2])%256;
		byte out = *buff ^ val;
		*buff=out;        
		buff++;        
	}
}