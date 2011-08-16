CC = gcc
CFLAGS = -g -std=c99 -Wall
SLIBS = -lcheck
SRC = ../src
INCLUDES = 
OBJECTS = 
TESTS = 

%.o : %.c $(INCLUDES)
	$(CC) $(CFLAGS) -c -o $@ $<
	
#check_linkedlist: check_linkedlist.o $(SRC)/linkedlist.o 
#	$(CC) $(CFLAGS) -o $@ $^ $(SLIBS)

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