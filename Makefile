CC = gcc
CFLAGS = -Wall -pedantic -std=c11 -I. -g

all: ListTest

list.o: list.c list.h
	$(CC) $(CFLAGS) -c list.c

ListTest.o: ListTest.c list.h
	$(CC) $(CFLAGS) -c ListTest.c

ListTest: list.o ListTest.o
	$(CC) $(CFLAGS) list.o ListTest.o -o ListTest

test: ListTest
	./ListTest

clean:
	rm -f *.o ListTest
