#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct linkedlist linkedlist;

/* constructors and destructors */
linkedlist *list_create();
void list_free(linkedlist *list);

/* getters */
int list_size(linkedlist *list);
int list_contains(linkedlist *list, void *item);
int list_is_empty(linkedlist *list);

/* setters */
void list_add_last(linkedlist *list, void *item);
void list_add_first(linkedlist *list, void *item);
void *list_remove(linkedlist *list, void *item);
void *list_remove_last(linkedlist *list);
void *list_remove_first(linkedlist *list);

#endif