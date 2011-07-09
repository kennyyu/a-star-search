SOURCES.c = main.c priorityqueue.c linkedlist.c
INCLUDES = priorityqueue.h linkedlist.h
CFLAGS = -g -std=c99
SLIBS = 
PROGRAM = main

OBJECTS= $(SOURCES.c:.c=.o)

all: $(PROGRAM)

$(PROGRAM): $(INCLUDES) $(OBJECTS)
	$(LINK.c) -o $@ $(OBJECTS) $(SLIBS)

clean:
	rm -f $(PROGRAM) $(OBJECTS)

help:
	@echo Type "make all" to build
