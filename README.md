ABOUT
=====
This is collection of C library data structures and a solution for the [fifteen puzzle](http://en.wikipedia.org/wiki/Fifteen_puzzle), using an [A* Search](http://en.wikipedia.org/wiki/A*_search_algorithm).

TODO
====
*   Library:

    *   Better comments, standard format
    
*   Fifteen Puzzle:
    
    *   Must free memory allocated by the a-star-search
    
    *   Must write unit tests for the solver

INSTALL
=======
*   Install [Check](http://check.sourceforge.net/), a C testing framework.

*   Download source code.

*   In the a-star-search directory, compile the source files with:

        $ make
    
*   Also in the a-star-search directory, run the tests and ensure they all pass. To run library tests:

        $ make libcheck
    
*   To use the data structures, include the path to the src folder, and link the library object file directory. Here's an example including the linkedlist.h file and linking the lib/src/* folder

    In hello.c:
    
        /*
         * include the linkedlist header file
         */
        include "../lib/src/linkedlist.h"
        // ...
    
    When compiling:

        $ gcc -o hello hello.c ../lib/src/*.o

USAGE
=====
On the command line in the directory with the solver executable, run it with:

   $ ./solver [--help] [--verbose] [--heuristic <hamming | manhattan>] <dim> <pos 1> <pos 2> ... <pos dim * dim>

Running solver with the --help flag will print this screen:

	   $ arguments summary:
	   $      --help                                        Displays this help text.
	   $      --verbose                                     Displays verbose output when solving. This includes a GUI printout and the value of the distance metric.
	   $      --heuristic <hamming | manhattan>             Heuristic metric to use for the A* search. Manhattan is default.
	   $      <dim>                                         Dimension of the square board. If the dimension is n, then we have an n x n board.
	   $      <pos k>                                       Number at position k, where starting from 1, we count left to right, up to down. Put a 0 to mark the empty spot.

SOURCE
======
    a-star-search/
        README.md
        Makefile
        lib/
            src/
                Collection of data structure libraries, including linkedlist, arraylist, priorityqueue, stack, queue, and heap.
            tests/
                Collection of tests for these data structures, using the Check framework
        fifteen-puzzle/
            src/
                Implementation of an A* Search on the fifteen puzzle.
            tests/
                Tests for the fifteen puzzle solver
            
REFERENCES
==========

#### README Markdown syntax:
*   http://daringfireball.net/projects/markdown/syntax#overview

#### Makefile tutorials:
*   http://www.cs.cf.ac.uk/Dave/C/node35.html
*   http://sunsite.ualberta.ca/Documentation/Gnu/make-3.79/html_chapter/make_3.html
*   http://www.cs.umd.edu/class/fall2002/cmsc214/Tutorial/makefile.html
*   http://web.mit.edu/gnu/doc/html/make_toc.html#SEC15
*   http://www.cprogramming.com/tutorial/makefiles_continued.html
*   http://stackoverflow.com/questions/1139271/makefiles-with-source-files-in-different-directories
*   http://www.gnu.org/s/hello/manual/make/Phony-Targets.html

#### C Macros:
*   http://en.cppreference.com/w/cpp/preprocessor/replace
*   http://publib.boulder.ibm.com/infocenter/comphelp/v7v91/index.jsp?topic=%2Fcom.ibm.vacpp7a.doc%2Flanguage%2Fref%2Fclrc09cpxmac.htm

#### C iterators:
*   http://pine.cs.yale.edu/pinewiki/C/Iterators

#### C auto, static, extern
*   http://knol.google.com/k/auto-static-and-global-variable-c-programming#

#### C arrays:
*   http://c-faq.com/~scs/cclass/int/sx5.html

#### C function pointers:
*   http://www.java2s.com/Tutorial/Cpp/0140__Function/Usetypedeftodefineafunctiontypeforfunctionpointer.htm
*   http://www.newty.de/fpt/fpt.html#r_value
*   http://pine.cs.yale.edu/pinewiki/C/FunctionPointers
*   http://stackoverflow.com/questions/2521927/initializing-a-global-struct-in-c

#### Functional programming in C
*   http://stackoverflow.com/questions/216037/what-tools-are-there-for-functional-programming-in-c
*   http://gcc.gnu.org/onlinedocs/gcc/Nested-Functions.html
*   http://www.haible.de/bruno/packages-ffcall-README.html
*   http://sourceforge.net/mailarchive/forum.php?thread_name=svd3mc9m1o.fsf%40tbox.wtc.algo&forum_name=clisp-list
*   http://cvs.savannah.gnu.org/viewvc/libffcall/ffcall/

#### Common C errors:
*   http://www.drpaulcarter.com/cs/common-c-errors.php

#### C error handling:
*   http://en.wikibooks.org/wiki/C_Programming/Error_handling
*   http://stackoverflow.com/questions/385975/error-handling-in-c-code

#### C Enums:
*   http://gnuvince.wordpress.com/2009/09/08/enums-in-c/
*   http://msdn.microsoft.com/en-us/library/whbyts4t.aspx

#### Dereferencing Void Pointers:
*   http://forums.devshed.com/c-programming-42/dereference-void-pointer-229122.html

#### Printing with color
*   http://cc.byexamples.com/2007/01/20/print-color-string-without-ncurses/

#### C Command Line Options
*   Argtable library: http://argtable.sourceforge.net/example/index.html
*   http://www.cs.caltech.edu/courses/cs11/material/c/mike/misc/cmdline_args.html

#### Fifteen Puzzle Parity
*   http://www.cs.bham.ac.uk/~mdr/teaching/modules04/java2/TilesSolvability.html
*   http://www.policyalmanac.org/games/aStarTutorial.htm

