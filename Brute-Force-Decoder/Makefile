#Set the shell to bash because it has more features
shell := /bin/bash

gcc=gcc -Wall -fthreadsafe-statics
lib=-lpthread
bin=bin/

#Set up debug configuration
ifdef $(dbg)
	gcc=$(gcc) -g
	Run=gdb
	lvl=-O0
else
	Run=
	lvl=-O0
endif

RunEnd=
def=-DN_KEYS=3 -DN_DECS=6 -DN_VALS=10
option=$(lvl) $(opt) $(def) -std=c18

obj=.o
out=bruteForceDecoder$(obj)

files=\
Decoder/decoder \
KeyProducer/byteArray \
KeyProducer/keyProducer \
Print/print \
Util/mutex \
Validator/validator \
file \
main \
queue


#define obj files
ofiles = $(foreach file, $(files), $(bin)$(file)$(obj))

#define c files for compile
cfiles = $(foreach file, $(files), $(file).c)
#define h files to rquire
hfiles = $(foreach file, $(files), $(file).h) \
Util/config.h \
Util/size.h

all: build

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