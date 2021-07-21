// stack to hold operands

#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include <stdlib.h>

typedef struct node_t {
	int key;
	struct node_t* next;
} Node;
typedef Node* Stack;

int push(Stack* s, const int token);
Node* pop(Stack* s);

#endif
