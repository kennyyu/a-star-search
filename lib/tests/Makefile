CC = gcc
CFLAGS = -g -std=c99 -Wall
SLIBS = -lcheck
SRC = ../src
INCLUDES = list.h queue.h stack.h heap.h
OBJECTS = check_linkedlist.o check_arraylist.o check_linkedqueue.o check_linkedstack.o check_arrayheap.o check_heappriorityqueue.o check_treeset.o
TESTS = check_linkedlist check_arraylist check_linkedqueue check_linkedstack check_arrayheap check_heappriorityqueue check_treeset

%.o : %.c $(INCLUDES)
	$(CC) $(CFLAGS) -c -o $@ $<
	
check_linkedlist: check_linkedlist.o $(SRC)/list.o $(SRC)/linkedlist.o 
	$(CC) $(CFLAGS) -o $@ $^ $(SLIBS)

check_arraylist: check_arraylist.o $(SRC)/list.o $(SRC)/arraylist.o
	$(CC) $(CFLAGS) -o $@ $^ $(SLIBS)
	
check_linkedqueue: check_linkedqueue.o $(SRC)/list.o $(SRC)/linkedlist.o $(SRC)/queue.o $(SRC)/linkedqueue.o 
	$(CC) $(CFLAGS) -o $@ $^ $(SLIBS)

check_linkedstack: check_linkedstack.o $(SRC)/list.o $(SRC)/linkedlist.o $(SRC)/stack.o $(SRC)/linkedstack.o
	$(CC) $(CFLAGS) -o $@ $^ $(SLIBS)
	
check_arrayheap: check_arrayheap.o $(SRC)/list.o $(SRC)/arraylist.o $(SRC)/heap.o $(SRC)/arrayheap.o
	$(CC) $(CFLAGS) -o $@ $^ $(SLIBS)
	
check_heappriorityqueue: check_heappriorityqueue.o $(SRC)/list.o $(SRC)/arraylist.o $(SRC)/heap.o $(SRC)/arrayheap.o $(SRC)/priorityqueue.o $(SRC)/heappriorityqueue.o
	$(CC) $(CFLAGS) -o $@ $^ $(SLIBS)

check_treeset: check_treeset.o $(SRC)/set.o $(SRC)/treeset.o 
	$(CC) $(CFLAGS) -o $@ $^ $(SLIBS)

all: $(TESTS)

check: $(TESTS)
	for t in $(TESTS); \
	do \
		echo " "; \
		./$$t; \
	done

clean:
	rm -f $(TESTS) $(OBJECTS)

help:
	@echo "make" or "make all" to build tests
	@echo "make check" to run tests