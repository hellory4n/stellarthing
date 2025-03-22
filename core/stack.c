#include "stack.h"

StStack* StStack_new(void)
{
	return malloc(sizeof(StStack));
}

void StStack_free(StStack* s)
{
	free(s);
}

void StStack_free_all(StStack* s)
{
	while (s->length != 0) {
		free(StStack_pop(s));
	}
	free(s);
}

void StStack_push(StStack* s, void* val)
{
	struct StStackNode* n = malloc(sizeof(struct StStackNode));
	n->val = val;
	n->next = s->top;
	s->top = n;
	s->length++;
}

void* StStack_pop(StStack* s)
{
	if (s->top == NULL) {
		return NULL;
	}
	struct StStackNode* temp = s->top;
	void* data = temp->val;
	s->top = s->top->next;
	free(temp);
	s->length--;
	return data;
}

void* StStack_peek(StStack* s)
{
	if (s->top == NULL) {
		return NULL;
	}
	return s->top->val;
}
