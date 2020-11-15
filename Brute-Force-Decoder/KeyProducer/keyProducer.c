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



#define AMT 36
byte* key_generateKey(int size, unsiged long long value){
	assert(size>0);
  byte* arr= calloc(size, (size_t)size);
  for(int i=0; i<size; i++){
    arr[i]=value%(AMT+1);
    value/=AMT;
  }
  return arr;
}

void* key_main(void* v){
	struct keyArgs* args=v;
	for(unsigned long long i=0; i<args->max){
#if KEY_MAX!=0
		sem_wait(&semKeyMax);
#endif
		keyQueue->push(key_generateKey(args->size, i));
		sem_post(&semKey);
	}
	free(args);
	return NULL;
}
