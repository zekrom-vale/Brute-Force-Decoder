#ifndef KEY_PRODUCER_H
#define KEY_PRODUCER_H

typedef byte unsigned char;

char getChar(byte i);
char* toChar(byte arr[]);
byte* toByte(char str[]);
byte getByte(char i);
byte* generateKey(int size, long value);
#endif
