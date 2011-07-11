#include <stdio.h>
#include <stdlib.h>

#include "linkedlist.h"
#include "priorityqueue.h"

int main(int argc, char *argv[]) {
	printf("Hello World\n");
	linkedlist list = list_create();
	printf("%d\n",list_size(list));
	int *num = malloc(sizeof(int));
	*num = 5;
	list_add_first(list, num);
	printf("%d\n",list_size(list));
	int *item;
	item = (int *) list_get_first(list);
	printf("%d\n",*item);
	item = (int *) list_get_last(list);
	printf("%d\n",*item);
	
	int *num2 = malloc(sizeof(int));
	*num2 = 6;
	list_add_first(list, num2);
	printf("%d\n",list_size(list));
	item = (int *) list_get_first(list);
	printf("%d\n",*item);
	item = (int *) list_get_last(list);
	printf("%d\n",*item);
}