OBJECTS=priorityqueue.o
CDFLAGS=
CC=gcc

all: priorityqueue

priorityqueue.o: priorityqueue.c priorityqueue.h
	gcc -c priorityqueue.c

priorityqueue: priorityqueue.o
	gcc -o priorityqueue priorityqueue.o

clean:
	rm $(OBJECTS)

help:
	@echo Type "make all" to build
