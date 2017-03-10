CC=gcc
CFLAGS=-Wall

all: Hashtable

Hashtable: Hashtable.o
	$(CC) $(CFLAGS) $^ -o $@

Hashtable.o: Hashtable.c
	$(CC) $(CFLAGS) $^ -c 

run: Hashtable
	./Hashtable

.PHONY: clean
clean:
	rm -f Hashtable.o
