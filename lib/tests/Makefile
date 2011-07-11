CC = gcc
CFLAGS = -g -std=c99 -Wall
SLIBS = -lcheck
SRC = ../src
INCLUDES = linkedlist.h
OBJECTS = check_linkedlist.o
TESTS = check_linkedlist

%.o : %.c $(INCLUDES)
	$(CC) $(CFLAGS) -c -o $@ $<

check_%: check_%.o $(SRC)/%.o
	$(CC) $(CFLAGS) -o $@ $^ $(SLIBS)

all: $(TESTS)

check: $(TESTS)
	for t in $(TESTS); \
	do \
		./$$t; \
	done

clean:
	rm -f $(TESTS) $(OBJECTS)

help:
	@echo "make" or "make all" to build tests
	@echo "make check" to run tests