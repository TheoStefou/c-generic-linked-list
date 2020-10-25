#ifndef __LIST_H__
#define __LIST_H__

typedef struct List_t* List;

List list_create();

int list_size(List list);

void list_push(List list, void *data);

void *list_get(List list, int index);

void *list_contains(List list, void* value, int (*fun_equals)(void*, void*));

void *list_pop(List list, int index);

void *list_pop_front(List list);

void *list_pop_value(List list, void *value, int (*fun_equals)(void*, void*));

/* 	Applies fun_apply to each element of the list. Use this for custom prints or in-place changes. */
void list_apply(List list, void (*fun_apply)(void*));

/* Same as list_apply but returns a new list with the mapped data. */
List list_map(List list, void *(*fun_map)(void*));

/* Returns a new list with just the data that pass from fun_filter. */
/* fun_dup returns the new data (you may map the data, duplicate it, or leave it as it is. */
List list_filter(List list, int (*fun_filter)(void*), void *(*fun_dup)(void*));

void list_destroy(List *list, void (*fun_destroy)(void*));

#endif