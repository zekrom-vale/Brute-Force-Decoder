#Set the shell to bash because it has more features
shell := /bin/bash

gcc=gcc -Wall
lib=-lpthread
bin=bin/

#Set up debug configuration
ifdef dbg
	gcc=gcc -Wall -g
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

all: $(ofiles) link

#Patterns
$(bin)%$(obj): %.c $(hfiles) %.h
	mkdir -p $@ || true
	rmdir $@ || true
	$(gcc) $< -c -o $@ $(option) $(lib)

$(bin)%$(obj): %.c $(hfiles)
	mkdir -p $@ || true
	rmdir $@ || true
	$(gcc) $< -c -o $@ $(option) $(lib)

#Test
testOut=test

test1: $(bin)queue$(obj) $(bin)Test/queueTest$(obj) $(bin)Util/mutex$(obj)
	$(gcc) $^ -o $(testOut)1$(obj) $(option) $(lib)

test2: $(bin)queue$(obj) $(bin)Test/queueCritSect$(obj) $(bin)Util/mutex$(obj)
	$(gcc) $^ -o $(testOut)2$(obj) $(option) $(lib)

test: test1 test2

link: $(ofiles)
	$(gcc) $^ -o $(out) $(option) $(lib)

run: link
	$(Run) ./$(out) $(RunEnd)

#Clean
clean:
	rm $(out)
	rm $(ofiles)

#Legacy
build: $(cfiles) $(hfiles)
	$(gcc) $(cfiles) -o $(out) $(option) $(lib)

runAlt:build
	$(Run) ./$(out) $(RunEnd)