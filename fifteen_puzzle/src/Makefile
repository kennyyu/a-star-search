CC = gcc
CFLAGS = -g -std=c99 -Wall
SLIBS =
LIBRARY = ../../lib/src
OBJECTS = solver.o board.o a-star-search.o
PROGINCLUDES = options.h board.h a-star-search.h
LIBINCLUDES = $(LIBRARY)/*.h
INCLUDES = $(PROGINCLUDES) $(LIBINCLUDES)
PROGRAM = solver

ifndef V
        QUIET_CC        = @echo '   ' CC $@;
        QUIET_AR        = @echo '   ' AR $@;
        QUIET_LINK      = @echo '   ' LINK $@;
        QUIET_GEN       = @echo '   ' GEN $@;
        QUIET_RM        = @echo '   ' RM  $@;
        QUIET_OBJCPY    = @echo '   ' OBJCPY $@;
endif

%.o : %.c $(INCLUDES)
	$(QUIET_CC) $(CC) $(CFLAGS) -c -o $@ $<

solver : $(OBJECTS) $(LIBRARY)/*.o
	$(QUIET_GEN) $(CC) $(CFLAGS) -o $@ $+

all: $(PROGRAM)

clean:
	rm -f $(PROGRAM) $(OBJECTS)

help:
	@echo "make" or "make all" to build src
