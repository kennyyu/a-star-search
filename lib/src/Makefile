CC = gcc
CFLAGS = -g -std=c99 -Wall
SLIBS =
OBJECTS = list.o linkedlist.o arraylist.o queue.o linkedqueue.o stack.o linkedstack.o heap.o arrayheap.o priorityqueue.o heappriorityqueue.o set.o treeset.o hashset.o map.o treemap.o hashmap.o
INCLUDES = list.h linkedlist.h arraylist.h queue.h linkedqueue.h stack.h linkedstack.h heap.h arrayheap.h priorityqueue.h heappriorityqueue.h set.h treeset.h hashset.h map.h treemap.h hashmap.h
PROGRAM =

%.o : %.c $(INCLUDES)
	$(CC) $(CFLAGS) -c -o $@ $<

all: $(OBJECTS)

clean:
	rm -f $(PROGRAM) $(OBJECTS)

help:
	@echo "make" or "make all" to build src
