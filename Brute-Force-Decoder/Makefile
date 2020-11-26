#Set the shell to bash because it has more features
shell := /bin/bash

gcc=gcc -Wall
lib=-lpthread
bin=bin/

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
option=$(lvl) $(opt) $(def) -std=c18

obj=.o
out=bruteForceDecider$(obj)

#define obj files
ofiles=$(bin)main$(obj) $(bin)queue$(obj) \
$(bin)Decoder/decoder$(obj) $(bin)KeyProducer/byteArray$(obj) \
$(bin)KeyProducer/keyProducer$(obj) $(bin)file$(obj) \
$(bin)Validator/validator$(obj)
#define c files for compile
cfiles=main.c queue.c Decoder/decoder.c KeyProducer/byteArray.c \
KeyProducer/keyProducer.c file.c Validator/validator.c
#define h files to rquire
hfiles=main.h queue.h Decoder/decoder.h KeyProducer/byteArray.h \
KeyProducer/keyProducer.h file.h Validator/validator.h Util/size.h

all: build run

build: $(cfiles) $(hfiles)
	$(gcc) $(cfiles) -o $(out) $(option) $(lib)

run: build
	$(Run) ./$(out) $(RunEnd)

clean:
	rm $(out)
	#rm $(ofiles)


$(bin)%$(obj): %.c $(hfiles)
	$(gcc) $< -c -o $@ $(option) $(lib)

link: $(ofiles)
	$(gcc) $^ -o $(out) $(option) $(lib)