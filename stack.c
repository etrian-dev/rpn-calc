#include "stack.h"

// pushes a string token of type tok_type to the stack, alloc done in the procedure
int push(Stack* s, const int token) {
	// alloc new node
	Node* head = (Node*) malloc(sizeof(Node));
	// if the allocation didn't fail, then set the node to the top of the stack
	if(head) {
		head->key = token;
		head->next = *s;
		*s = head;
		return 1;
	}
	else {
		return 0;
	}
}
// pops the stack if there's at least an element
Node* pop(Stack* s) {
	if(*s) {
		Node* tmp = *s;
		*s = (*s)->next;
		return tmp;
	}
	else {
		return NULL;
	}
}
