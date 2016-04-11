CC=gcc
CFLAGS=-g -Wall -ljson-c

object = gaifil.o

.PHONY:all
all:gaifil example test

gaifil:$(object)
	$(CC) $(CFLAGS) -o $@ $<
#gaifil:$(object)
#	$(CC) $(CFLAGS) -o gaifil $(object)

object:gaifil.c
	$(CC) $(CFLAGS) -c $@ $<

exec:
	cd ~vagrant
	pwd

foo = $(bar)
bar = $(ugh)
ugh = Huh?
foo:
	echo $(foo)

ifeq (0,${MAKELEVEL})
cur-dir := $(shell pwd)
whoami := $(shell whoami)
host-type := $(shell arch)
MAKE := ${MAKE} host-type=${host-type} whoami=${whoami}
cur:
	echo $(cur-dir)
	echo $(whoami)
	echo $(host-type)
	echo $(a)
	echo $(x)
	echo $(y)
	echo $(z)
	echo $(RM)
	echo $(AR)
	echo $(CC)
	echo $(CXX)
endif
x = y
y = z
z = u
a := $($($(x)))



#include ./example/makefile
example test:
	(cd example; make)

help:
	@echo "... all(gaifil/example/test)"
	@echo "... gaifil"
	(cd example; make help)	

.PHONY:clean
clean:
	-rm -f $(object) gaifil a.out
	(cd example; make clean)
