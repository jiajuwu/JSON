CC=gcc
CFLAGS=-g -Wall -ljson-c
INCLUDE = /usr/include/json-c

.PHONY:all
all:example test

example:example.o
	$(CC) $(CFLAGS) -I$(INCLUDE) example.o -o example

example.o:example.c

test:test.o
	$(CC) $(CFLAGS) -I$(INCLUDE) test.o -o test

test.o:test.c

help:
	@echo "... all(example/test)"
	@echo "... example"
	@echo "... test"

.PHONY:clean
clean:
	-rm -f *.o
	-rm -f example
	-rm -f test
