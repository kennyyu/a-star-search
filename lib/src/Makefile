CC = gcc
CFLAGS = -g -std=c99 -Wall
SLIBS =
OBJECTS = linkedlist.o arraylist.o listqueue.o liststack.o arrayheap.o heappriorityqueue.o treeset.o hashset.o treemap.o hashmap.o
INCLUDES = list.h linkedlist.h arraylist.h queue.h listqueue.h stack.h liststack.h heap.h arrayheap.h priorityqueue.h heappriorityqueue.h set.h treeset.h hashset.h map.h treemap.h hashmap.h
PROGRAM =

%.o : %.c $(INCLUDES)
	$(CC) $(CFLAGS) -c -o $@ $<

all: $(OBJECTS)

clean:
	rm -f $(PROGRAM) $(OBJECTS)

help:
	@echo "make" or "make all" to build src
