CC = gcc
CFLAGS = -g -std=c99 -Wall
SLIBS =
OBJECTS = main.o priorityqueue.o linkedlist.o queue.o stack.o
INCLUDES = priorityqueue.h list.h queue.h stack.h
PROGRAM =

%.o : %.c $(INCLUDES)
	$(CC) $(CFLAGS) -c -o $@ $<

all: $(PROGRAM)

$(PROGRAM): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS) $(SLIBS)

clean:
	rm -f $(PROGRAM) $(OBJECTS)

help:
	@echo "make" or "make all" to build src
