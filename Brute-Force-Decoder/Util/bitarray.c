#include <limits.h>
typedef ulong unsigned long long;

bool bit_add(ulong arr[], ulong num){
	ulong org;
	size_t size=sizeof(arr)/sizeof(arr[0]);
	unsigned int i=0;
	if(num==ULONG_MAX){
		//Skip if using the max size
		i++;
		num=0;
	}
	do{
		org=arr[i];
		arr[i]+=num;
		if(arr[i]>org)return true;
		i++;
	}while(i<size);
	return false;
}

bool bit_sub(ulong arr[], ulong num){
	ulong org;
	size_t size=sizeof(arr)/sizeof(arr[0]);
	unsigned int i=size-1;
	if(num==ULONG_MAX){
		//Skip if using the max size
		i--;
		num=0;
	}
	do{
		org=arr[i];
		arr[i]-=num;
		if(arr[i]<org)return true;
		i--;
	}while(i>=0);
	return false;
}

bool bit_inc(ulong arr[]){
	return bit_add(arr, 1UL);
}

bool bit_dec(ulong arr[]){
	return bit_sub(arr, 1UL);
}
