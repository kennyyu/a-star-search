SOURCE = src
TESTS = tests

all: $(SOURCE) $(TESTS)
	$(MAKE) --directory=$(SOURCE) all
	$(MAKE) --directory=$(TESTS) all

check: $(TESTS)
	$(MAKE) --silent --directory=$(TESTS) check

clean:
	$(MAKE) --directory=$(SOURCE) clean
	$(MAKE) --directory=$(TESTS) clean

help:
	@echo "make" or "make all" to build src and tests
	@echo "make check" to run tests