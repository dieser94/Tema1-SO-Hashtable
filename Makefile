CC=gcc
CFLAGS=-Wall

all: Hashtable

Hashtable: Hashtable.o hash.o
	$(CC) $(CFLAGS) Hashtable.o  -o $@ libhash.so -L.

Hashtable.o: Hashtable.c
	$(CC) $(CFLAGS) $^ -c 

hash.o: hash.c
	$(CC) $(CFLAGS) $^ -c 

run: Hashtable
	export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:.
	./Hashtable

.PHONY: clean
clean:
	rm -f Hashtable.o
