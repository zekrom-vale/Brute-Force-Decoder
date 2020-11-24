#Set the shell to bash because it has more features
shell := /bin/bash

gcc=gcc -Wall

#Set up debug configuration
ifdef $(dbg)
gcc=$(gcc) -g
Run=gdb
else
Run=
endif

obj=.o
out=bruteForceDecider$(obj)

#define c files for compile
cfiles=main.c queue.c Decoder/decoder.c KeyProducer/byteArray.c KeyProducer/keyProducer.c Validator/validator.c Util/bitarray.c
#define h files to rquire 
hfiles=main.h queue.h Decoder/decoder.h KeyProducer/byteArray.h KeyProducer/keyProducer.h Validator/validator.h Util/bitarray.h

all: build run

build: $(cfiles) $(hfiles)
	$(gcc) $(cfiles) -o $(out) -lpthread

run: build
	$(Run) ./$(out)

clean:
	rm $(out)