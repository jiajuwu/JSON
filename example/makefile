
INCLUDE = /usr/include/json-c

example:
	gcc -I$(INCLUDE) example.c -o example -ljson-c

test:
	gcc -I$(INCLUDE) test.c -o test -ljson-c

clean:
	rm -rf *.o
	rm -rf example
	rm -rf test
