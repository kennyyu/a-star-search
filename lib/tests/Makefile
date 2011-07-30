CC = gcc
CFLAGS = -g -std=c99 -Wall
SLIBS = -lcheck
SRC = ../src
INCLUDES = list.h linkedlist.h arraylist.h queue.h listqueue.h stack.h linkedstack.h heap.h arrayheap.h priorityqueue.h heappriorityqueue.h set.h treeset.h hashset.h map.h treemap.h hashmap.h
OBJECTS = check_linkedlist.o check_arraylist.o check_listqueue.o check_linkedstack.o check_arrayheap.o check_heappriorityqueue.o check_treemap.o check_treeset.o
TESTS = check_linkedlist check_arraylist check_listqueue check_linkedstack check_arrayheap check_heappriorityqueue check_treemap check_treeset

%.o : %.c $(INCLUDES)
	$(CC) $(CFLAGS) -c -o $@ $<
	
check_linkedlist: check_linkedlist.o $(SRC)/linkedlist.o 
	$(CC) $(CFLAGS) -o $@ $^ $(SLIBS)

check_arraylist: check_arraylist.o $(SRC)/arraylist.o
	$(CC) $(CFLAGS) -o $@ $^ $(SLIBS)
	
check_listqueue: check_listqueue.o $(SRC)/linkedlist.o $(SRC)/listqueue.o 
	$(CC) $(CFLAGS) -o $@ $^ $(SLIBS)

check_linkedstack: check_linkedstack.o $(SRC)/linkedlist.o $(SRC)/linkedstack.o
	$(CC) $(CFLAGS) -o $@ $^ $(SLIBS)
	
check_arrayheap: check_arrayheap.o $(SRC)/arraylist.o $(SRC)/arrayheap.o
	$(CC) $(CFLAGS) -o $@ $^ $(SLIBS)
	
check_heappriorityqueue: check_heappriorityqueue.o $(SRC)/arraylist.o $(SRC)/arrayheap.o $(SRC)/heappriorityqueue.o
	$(CC) $(CFLAGS) -o $@ $^ $(SLIBS)

check_treemap: check_treemap.o $(SRC)/treemap.o
	$(CC) $(CFLAGS) -o $@ $^ $(SLIBS)

check_treeset: check_treeset.o $(SRC)/treeset.o $(SRC)/treemap.o
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