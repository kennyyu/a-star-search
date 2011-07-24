CC = gcc
CFLAGS = -g -std=c99 -Wall
SLIBS =
OBJECTS = list.o linkedlist.o arraylist.o queue.o linkedqueue.o stack.o linkedstack.o heap.o arrayheap.o priorityqueue.o heappriorityqueue.o
INCLUDES = list.h linkedlist.h arraylist.h queue.h linkedqueue.h stack.h linkedstack.h heap.h arrayheap.h priorityqueue.h heappriorityqueue.h 
PROGRAM =

%.o : %.c $(INCLUDES)
	$(CC) $(CFLAGS) -c -o $@ $<

all: $(OBJECTS)

#$(PROGRAM): $(OBJECTS)
#	$(CC) $(CFLAGS) -o $@ $(OBJECTS) $(SLIBS)

clean:
	rm -f $(PROGRAM) $(OBJECTS)

help:
	@echo "make" or "make all" to build src
