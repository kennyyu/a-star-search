SOURCE = src
TESTS = tests

all: $(SOURCE) $(TESTS)
	$(MAKE) -C $(SOURCE) all
	$(MAKE) -C $(TESTS) all

check: $(TESTS)
	$(MAKE) -C $(TESTS) check
	
clean:
	$(MAKE) -C $(SOURCE) clean
	$(MAKE) -C $(TESTS) clean

help:
	@echo "make" or "make all" to build src and tests
	@echo "make check" to run tests