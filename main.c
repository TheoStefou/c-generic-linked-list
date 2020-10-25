#include <stdio.h>
#include <stdlib.h>

#include "list.h"


void myprint(void *data) {
	printf("%d\n", *((int*) data));
}

void *map(void *data) {
	int *int_data = (int*) data;
	int* new_int = malloc(sizeof(int));
	*new_int = *int_data;
	return new_int;
}

int filter_evens(void *data) {
	int *int_data = (int*) data;
	if(*int_data % 2 == 0)
		return 1;
	return 0;
}

int equals(void *value1, void *value2) {
	int *v1 = (int*) value1;
	int *v2 = (int*) value2;

	if(*v1 == *v2)
		return 1;
	return 0;
}

void destroy(void *data) {
	free(data);
}

int* createint(int x) {
	int* ret = malloc(sizeof(int));
	*ret = x;
	return ret;
}

int main() {
	List list = list_create();
	for(int i = 0; i < 10; i++) {
		list_push(list, createint(i));
	}
	for(int i = 9; i >= 0; i--) {
		int *value = createint(1);
		void* data = list_pop_value(list, value, equals);
		free(value);
		if(data != NULL) {
			myprint(data);
			free(data);
		}

	}
	printf("--------\n");
	list_apply(list, myprint);
	list_destroy(&list, destroy);
}