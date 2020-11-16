#include "keyProducer.h"

char key_getChar(byte i){
  if(i<=9)return 0x30+i;
  if(i<=36)return 0x41-9+i;
}

char* key_toChar(byte* arr, size_t size){
  char* str=calloc(size, sizeof(byte));
  for(int i=0; i<size; i++){
    *(str+i)=getChar(*(arr+i));
  }
  return str;
}

byte* key_toByte(char* str, size_t size){
  char* arr=calloc(size, sizeof(char));
  for(int i=0; i<size; i++){
    *(arr+i)=getChar(*(str+i));
  }
  return arr;
}

byte key_getByte(char i){
  if(0x30<=i&&i<=0x39)return i-0x30;
  if(0x41<=i&&i<=0x5A)return i-0x41+10;
}



byte* key_generateKey(byte* arr, size_t size){
	/*byte* clone=calloc(size, sizeof(byte));
	byte* cur=arr;
	byte* curClone=clone;
	while(cur<arr+size){
		*(curClone++)=*(cur++);
	}
	return clone;
	*/
	return memcpy(calloc(size, sizeof(byte), arr, size));
}

void* key_main(void* v){
	struct keyArgs* args=v;
	byte arr[args->size];
	arr[0]=args->start;
	while(byte_array_inc(arr, args->num, args->size)){
#if KEY_MAX!=0
		sem_wait(&semKeyMax);
#endif
		keyQueue->push(key_generateKey(arr, args->size));
		sem_post(&semKey);
	}
	free(args);
	return NULL;
}
