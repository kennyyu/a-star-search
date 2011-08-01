ABOUT
=====
This is collection of C library data structures and a solution for the [fifteen puzzle](http://en.wikipedia.org/wiki/Fifteen_puzzle), using an [A* Search](http://en.wikipedia.org/wiki/A*_search_algorithm).

TODO
====
*   A* Search

*   Library:

    *   Implement hashmap and hashset (with hash tables)
    
    *   Have a queue (or list) bucket changes to allow for random access, to array functions
    
    *   Add a free_items function to all data structures to optionally free the items
    
    *   Algorithms (Sorts, Graph algorithms)

*   Documentation
    
    *   Find an automatic C documentation generator, or manually add docs
    
    *   Or write a script and use regular expressions to parse

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