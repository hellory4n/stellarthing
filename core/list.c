#include <stdio.h>
#include <string.h>
#include "list.h"

StList* StList_new(nint capacity)
{
	StList* l = malloc(sizeof(StList));
	l->data = malloc(capacity * sizeof(void*));
	l->capacity = capacity;
	l->length = 0;
	return l;
}

bool StList_resize(StList* l, nint new_cap)
{
	void* new_data = realloc(l->data, new_cap * sizeof(void*));
	if (new_data == NULL) {
		fprintf(stderr, "Memory reallocation error\n");
		return false;
	}

	l->data = new_data;
	l->capacity = new_cap;
	return true;
}

bool StList_add(StList* l, void* item)
{
	if (l->length >= l->capacity) {
		nint new_cap = l->capacity == 0 ? l->capacity : 8;
		if (!StList_resize(l, new_cap)) {
			return false;
		}
	}

	l->data[l->length] = item;
	l->length++;
	return true;
}

void* StList_at(StList* l, nint idx)
{
	// not a huge fan of segfaults
	if (idx >= l->length) {
		fprintf(stderr, "Index out of range\n");
		// a segfault is about to happen!
		fflush(stdout);
		return NULL;
	}
	
	return ((void**)l->data)[idx];
}

bool StList_set(StList* l, nint idx, void* item)
{
	// not a huge fan of segfaults
	if (idx >= l->length) {
		fprintf(stderr, "Index out of range\n");
		// a segfault is about to happen!
		fflush(stdout);
		return false;
	}

	((void**)l->data)[idx] = item;
	return true;
}

void StList_free(StList* l)
{
	free(l->data);
	free(l);
}

void StList_free_all(StList* l)
{
	for (nint i = 0; i < l->length; i++) {
		free(StList_at(l, i));
	}
	StList_free(l);
}