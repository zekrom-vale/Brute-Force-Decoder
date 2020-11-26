#Set the shell to bash because it has more features
shell := /bin/bash

gcc=gcc -Wall

#Set up debug configuration
ifdef $(dbg)
	gcc=$(gcc) -g
	Run=gdb
	lvl=-Og
else
	Run=
	lvl=-O3
endif

RunEnd=
def=-DN_KEYS=3 -DN_DECS=6 -DN_VALS=10
option=$(lvl) -Wall $(opt) $(def) -std=c18

obj=.o
out=bruteForceDecider$(obj)

#define c files for compile
cfiles=main.c queue.c Decoder/decoder.c KeyProducer/byteArray.c \
KeyProducer/keyProducer.c file.c Validator/validator.c
#define h files to rquire
hfiles=main.h queue.h Decoder/decoder.h KeyProducer/byteArray.h \
KeyProducer/keyProducer.h file.h Validator/validator.h Util/size.h

all: build run

build: $(cfiles) $(hfiles)
	$(gcc) $(cfiles) -o $(out) $(option) -lpthread

run: build
	$(Run) ./$(out) $(RunEnd)

clean:
	rm $(out)