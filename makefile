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
