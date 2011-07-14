CC = gcc
CFLAGS = -g -std=c99 -Wall
SLIBS = -lcheck
SRC = ../src
INCLUDES = list.h queue.h stack.h
OBJECTS = check_linkedlist.o check_arraylist.o check_queue.o check_stack.o
TESTS = check_linkedlist check_arraylist check_queue check_stack

%.o : %.c $(INCLUDES)
	$(CC) $(CFLAGS) -c -o $@ $<

#check_%: check_%.o $(SRC)/%.o
#	$(CC) $(CFLAGS) -o $@ $^ $(SLIBS)
	
check_linkedlist: check_linkedlist.o $(SRC)/linkedlist.o
	$(CC) $(CFLAGS) -o $@ $^ $(SLIBS)

check_arraylist: check_arraylist.o $(SRC)/arraylist.o
	$(CC) $(CFLAGS) -o $@ $^ $(SLIBS)
	
check_queue: check_queue.o $(SRC)/queue.o $(SRC)/linkedlist.o
	$(CC) $(CFLAGS) -o $@ $^ $(SLIBS)

check_stack: check_stack.o $(SRC)/stack.o $(SRC)/linkedlist.o
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