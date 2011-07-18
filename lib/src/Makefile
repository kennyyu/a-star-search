CC = gcc
CFLAGS = -g -std=c99 -Wall
SLIBS =
OBJECTS = linkedlist.o arraylist.o linkedqueue.o linkedstack.o arrayheap.o heappriorityqueue.o
INCLUDES = priorityqueue.h list.h queue.h stack.h heap.h
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
