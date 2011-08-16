CC = gcc
CFLAGS = -g -std=c99 -Wall
SLIBS =
LIBRARY = ../lib/src
OBJECTS = solver.o board.o a-star-search.o
PROGINCLUDES = board.h
LIBINCLUDES = $(LIBRARY)/*.h
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
