bool byte_array_inc(byte* arr, byte inc, size_t size){
	*arr+=inc;
	if(*arr>MAX)*arr%=(MAX+1);
	else return true;
	for(int i=0; i<size; i++){
		if(++*(arr+i)>MAX)*(arr+i)=0;
		else return true;
	}
	return false;
}
