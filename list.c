#include <stdlib.h>
#include <stdio.h>

#include "list.h"

typedef struct Node {
	struct Node *next;
	void *data;
} Node;

typedef struct List_t {
	Node *head;
	Node* last;
	int size;
} list_t;

Node* create_node(void *data) {
	Node* n = malloc(sizeof(Node));
	n->next = NULL;
	n->data = data;
	return n;
}

List list_create() {
	List list = malloc(sizeof(list_t));
	list->head = NULL;
	list->last = NULL;
	list->size = 0;
	return list;
}

int list_size(List list) {
	return list->size;
}

void list_push(List list, void *data) {
	Node* new_node = create_node(data);
	if(!list->head) {
		list->head = new_node;
		list->last = list->head;
		list->size = 1;
		return;
	}

	list->last->next = new_node;
	list->last = list->last->next;
	list->size++;
}

void *list_at(List list, int index) {
	if(index < 0 || index > list->size - 1)
		return NULL;

	int curr_pos = 0;
	Node* curr_node = list->head;
	while(curr_pos < index) {
		curr_node = curr_node->next;
		curr_pos++;
	}
	return curr_node->data;
}

void *list_contains(List list, void* value, int (*fun_equals)(void*, void*)) {
	Node* current = list->head;
	while(current) {
		if(fun_equals(current->data, value))
			return current;
		current = current->next;
	}
	return NULL;
}

void *list_pop(List list, int index) {
	
	printf("Popping %d with size %d\n", index, list->size);
	if(index < 0 || index > list->size - 1)
		return NULL;

	if(index == 0) {
		Node *tmp = list->head;
		void *data = tmp->data;
		list->head = list->head->next;
		free(tmp);
		if(list->size == 1) {
			list->last = NULL;
		}
		list->size--;
		return data;
	}

	Node *previous = list->head;
	Node *current = list->head->next;
	int curr_pos = 1;
	while(curr_pos != index) {
		previous = current;
		current = current->next;
		curr_pos++;
	}
	Node *tmp = current->next;
	void *data = current->data;
	previous->next = tmp;
	free(current);
	if(index == list->size-1) {
		list->last = previous;
	}
	list->size--;
	return data;
}

void *list_pop_front(List list) {
	if(!list->head)
		return NULL;
	Node *next = list->head->next;
	void *data = list->head->data;
	free(list->head);
	return data;
}

void *list_pop_value(List list, void *value, int (*fun_equals)(void*, void*)) {
	if(!list->head)
		return NULL;
	Node *current = list->head->next;
	Node *previous = list->head;
	if(fun_equals(previous->data, value)) {
		Node *tmp = list->head;
		void *data = tmp->data;
		free(tmp);
		list->head = current;
		return data;
	}

	while(current) {
		if(fun_equals(current->data, value)) {
			previous->next = current->next;
			void *data = current->data;
			free(current);
			return data;
		}
		previous = current;
		current = current->next;
	}

	return NULL;
}

void list_apply(List list, void (*fun_apply)(void*)) {
	Node* current = list->head;
	while(current) {
		fun_apply(current->data);
		current = current->next;
	}
}

List list_map(List list, void *(*fun_map)(void*)) {
	List new_list = list_create();
	Node *current = list->head;
	while(current) {
		list_push(new_list, fun_map(current->data));
		current = current->next;
	}
	new_list->size = list->size;
	return new_list;
}

List list_filter(List list, int (*fun_filter)(void*), void *(*fun_dup)(void*)) {
	List new_list = list_create();
	Node *current = list->head;
	while(current) {
		if(fun_filter(current->data)) {
			list_push(new_list, fun_dup(current->data));
			new_list->size++;
		}
		current = current->next;
	}
	return new_list;
}

void list_destroy(List *list, void (*fun_destroy)(void*)) {
	Node *current = (*list)->head;

	while(current) {
		Node* tmp = current->next;
		fun_destroy(current->data);
		free(current);
		current = tmp;
	}

	free(*list);
	*list = NULL;
}