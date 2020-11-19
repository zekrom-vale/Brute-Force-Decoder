#include "keyProducer.h"

/**
 * Converts bytes to characters
 * 0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ
 * @param i the byte to convert
 * @return the character code
 */
char key_getChar(byte i){
  if(i<=9)return (char)(0x30+i);
  if(i<=36)return (char)(0x41-10+i);
}

/**
 * Array format of #key_getChar
 * @param arr the byte array
 * @param size the size of the array
 */
char* key_toChar(byte* arr, size_t size){
  char* str=calloc(size, sizeof(byte));
  for(int i=0; i<size; i++){
    *(str+i)=getChar(*(arr+i));
  }
  return str;
}

/**
 * Converts characters to bytes
 * @param i the char to convert
 * @return the corisponding byte -1 if invalid
 */

byte key_getByte(char i){
  if(0x30<=i&&i<=0x39)return i-0x30;
  if(0x41<=i&&i<=0x5A)return i-0x41+10;
  return (byte)-1;//Get max value of byte
}

/**
 * Array format of #key_getByte
 * Don't forget to free the str!
 * @param str the string to convert
 * @param size the size of the string
 * @return the byte array
 */

byte* key_toByte(char* str, size_t size){
  char* arr=calloc(size, sizeof(char));
  for(int i=0; i<size; i++){
    *(arr+i)=getChar(*(str+i));
  }
  return arr;
}


/**
 * Generates the given key
 * It simply coppies the array as it will be changing
 * @param arr the byte array
 * @param size the size of the array
 * @param the coppied key
 */

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

/**
 * The main of the keyProducer thread
 * @param v the arguments (needs to be casted)
 * @return NULL
 */
void* key_main(void* v){
	//Get args
	assert(v!=NULL);
	struct keyArgs* args=v;

	//Create key used to ccreate all other keys
	byte arr[args->size];
	arr[0]=args->start;
	//Increment then push to the queue
	while(byte_array_inc(arr, args->num, args->size)){
#if KEY_MAX!=0
		sem_wait(&semKeyMax);
#endif
		keyQueue->push(key_generateKey(arr, args->size));
		sem_post(&semKey);
	}
	//Free the args and return
	free(args);
	return NULL;
}
