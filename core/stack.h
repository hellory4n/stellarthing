#pragma once
#include "core/core.h"

struct StStackNode {
	void* val;
	struct StStackNode* next;
};

/// It's a linked list disguised as a linked list
typedef struct {
	nint length;
	struct StStackNode* top;
} StStack;

/// Makes a new stack
StStack* StStack_new(void);

/// Frees the stack. You can also automatically free everything with `free()` using `StStack_free_all()`
void StStack_free(StStack* s);

/// Frees the stack and all of its items. If your items are a bit more complicated than just calling
/// `free()` on everything, manually free everything and then call `StStack_free()`
void StStack_free_all(StStack* s);

/// Pushes an item to the top of the stack
void StStack_push(StStack* s, void* val);

/// Removes the item at the top of the stack and returns it. If the stack is empty, it returns null.
void* StStack_pop(StStack* s);

/// Returns the item at the top of the stack without removing it. If the stack is empty, it returns null.
void* StStack_peek(StStack* s);
