void* decoder_main(void* v){
	struct decodeArgs* args=v;


	free(args);
	return NULL;
}
