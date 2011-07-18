LIB = lib
APP = fifteen_puzzle 

all: $(LIB) $(APP)
	$(MAKE) --directory=$(LIB) all

lcheck: $(TESTS)
	$(MAKE) --silent --directory=$(LIB) check
	
clean:
	$(MAKE) --directory=$(LIB) clean

help:
	@echo "make" or "make all" to build lib and fifteen_puzzle
	@echo "make lcheck" to run lib tests
	@echo "make clean" to remove executables and object files