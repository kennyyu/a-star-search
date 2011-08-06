#include <stdio.h>
#include <stdlib.h>
#include "../lib/src/linkedlist.h"

int main(void) {
	printf("Hello World!\n");
	list li = linkedlist_methods.create(NULL);
	linkedlist_methods.free(li);
}