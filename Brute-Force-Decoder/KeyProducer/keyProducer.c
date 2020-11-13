#include "keyProducer.h"

char getChar(byte i){
  if(i<=9)return 0x30+i;
  if(i<=36)return 0x41-9+i;
}

char* toChar(byte arr[]){
  size_t size=sizeof(arr)/sizeof(arr[0]);
  char str[size];
  for(int i=0; i<size; i++){
    str[i]=getChar(arr[i]);
  }
  return str;
}

byte* toByte(char str[]){
  size_t size=sizeof(str)/sizeof(str[0]);
  char arr[size];
  for(int i=0; i<size; i++){
    arr[i]=getChar(str[i]);
  }
  return arr;
}

byte getByte(char i){
  if(0x30<=i&&i<=0x39)return i-0x30;
  if(0x41<=i&&i<=0x5A)return i-0x41+10;
}

#define AMT 36
byte* generateKey(int size, long value){
  byte arr[size];
  for(int i=0; i<size; i++){
    arr[i]=value%(AMT+1);
    value/=AMT;
  }
  return arr;
}
