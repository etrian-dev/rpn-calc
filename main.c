#include <stdio.h>
#include <stdlib.h>
// readline for input
#include <readline/readline.h>

#include "stack.h"

// define token size, hopefully enough
#define TOK_SZ 50

void freeMem(Stack* s);
int eval(char op, int lval, int rval);

int main(void) {
	// arrays for the input line and tokens
	char *line = 0, *token = 0;
	
	// read a line of input using readline
	line = readline("Input rpn expression:\n");
	
	token = (char*) malloc(TOK_SZ * sizeof(*token));
	// stores line's total lenght and current tokenization point
	int line_len, curr_len;
	// variables used in expression evaluation
	int value, res; char operator;
	Node *lval, *rval;
	
	// init stack for operands
	Stack opStack = 0;
	
	// check if allocation was successfull
	if(line && token) {
		
		// calculate input string lenght and init processed lenght
		line_len = strlen(line);
		curr_len = 0;
		
		// tokenize input line by repeatedly calling strtok on it (destructive)
		token = strtok(line, " ");
		while(token) {
			// update current position in the input string
			curr_len += strlen(token) + 1;
			//printf("current token: %s\n", token);
			
			// determine the type of token (operand or operator)
			if(sscanf(token, "%d", &value) == 1) {
				// if token is parsed as an int, then it's an operand
				push(&opStack, value);
			}
			// otherwise it's an operator
			else {
				// obtain it as a single char
				sscanf(token, " %c", &operator);
				// thus pop the first two operands on the stack and apply the operator
				rval = pop(&opStack);
				lval = pop(&opStack);
				// check if both pop() were successfull
				if(rval && lval) {
					// evaluate expression and assign result
					res = eval(operator, lval->key, rval->key);
					//printf("%d %c %d = %d\n", lval->key, operator, rval->key, res);
					// free nodes
					free(rval);
					free(lval);
					
					// now push the result to the stack 
					// if all the tokens haven't been read yet
					if(curr_len < line_len) {
						push(&opStack, res);
					}
					else {
						puts("success: evaluation finished");
					}
				}
				// error: tried to pop from empty stack
				else {
					puts("error: tried to pop from empty stack");
					exit(EXIT_FAILURE);
				}
			}
			
			// update token
			token = strtok(NULL, " ");
		}
		printf("result: %d\n", res);
		// free memory
		/* line below is actually useless, since token is NULL (cannot free) */
		//free(token);
		free(line);
		freeMem(&opStack);
	}
	else {
		puts("Failed alloc line or token");
		return 1;
	}
	return 0;
}

void freeMem(Stack* s) {
	Node* n;
	while(*s) {
		n = *s;
		*s = (*s)->next;
		free(n);
	}
}

int eval(char op, int lval, int rval) {
	int res;
	switch(op) {
		case '+':
			res = lval + rval;
			break;
		case '-':
			res = lval - rval;
			break;
		case '*':
			res = lval * rval;
			break;
		case '/':
			// check if the division is ok
			if(rval == 0) {
				puts("error: division by 0");
				exit(EXIT_FAILURE);
			}
			/// INTEGER DIVISION, remainder is dropped
			res = lval / rval;
			break;
		default:
			puts("error: operation not recognized");
			exit(EXIT_FAILURE);
	}
	return res;
}
