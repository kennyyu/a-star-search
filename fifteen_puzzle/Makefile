CC = gcc
CFLAGS = -g -std=c99 -Wall
SLIBS =
LIBRARY = ../lib/src
OBJECTS = solver.o
INCLUDES = $(LIBRARY)/*.h
PROGRAM = solver

%.o : %.c $(INCLUDES)
	$(CC) $(CFLAGS) -c -o $@ $<

solver : $(OBJECTS) $(LIBRARY)/*.o
	$(CC) $(CFLAGS) -o $@ $+

all: $(PROGRAM)

clean:
	rm -f $(PROGRAM) $(OBJECTS)

help:
	@echo "make" or "make all" to build src
