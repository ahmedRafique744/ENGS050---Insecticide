CFLAGS=-Wall -pedantic -std=c11 -I. -g

all: new_test

new_test: queue.o new_test.o
	$(CC) $(CFLAGS) queue.o new_test.o -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o new_test

run: new_test
	./new_test
