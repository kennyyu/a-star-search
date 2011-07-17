CC = gcc
CFLAGS = -g -std=c99 -Wall
SLIBS =
OBJECTS = priorityqueue.o linkedlist.o arraylist.o queue.o stack.o arrayheap.o
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
