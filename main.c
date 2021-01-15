#include <stdio.h>
#include <stdlib.h>
#include <math.h>
// readline for input
#include <readline/readline.h>

#include "stack.h"

// define token size, hopefully enough
#define TOK_SZ 50

void freeMem(Stack* s) {
    Node* n;
    while(*s) {
        n = *s;
        *s = (*s)->next;
        free(n);
    }
}

// the core function, where values are computed
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
        case '%':
        	// modulo must be positive
        	if(rval <= 0) {
        		puts("error: modulo cannot be <= 0");
        		exit(EXIT_FAILURE);
        	}
        	res = lval % rval;
        	break;
        case '^':
        	// effient power function
        	res = (int)pow(lval, rval);
        	break;
        default:
            puts("error: operation not recognized");
            exit(EXIT_FAILURE);
    }
    
    // check for overflows
    if(
        ((op != '-') 
        	&&	((lval > 0 && rval > 0 && res < 0)
        		|| (lval < 0 && rval < 0 && res > 0))
       	)
        || 	((op == '-') && (lval < rval && res > 0))
      )
    {
        puts("error: overflow");
        exit(EXIT_FAILURE);
    }
    return res;
}

int main(void) {
    // arrays for the input line and tokens
    char *line = NULL;
    char *token = (char*) malloc(TOK_SZ * sizeof(*token));
    
    // read a line of input using readline
    line = readline("Input rpn expression:\n");

    // stores line's length and current position
    int line_len, curr_len;
    // variables used in expression evaluation
    int value, res; char operator;
    Node *lval, *rval;
    
    // Stack for operands
    Stack opStack = 0;
    
    // check if allocation was successful
    if(line && token) {
        
        // calculate input string lenght and set tokenization point to the beginning
        line_len = strlen(line);
        curr_len = 0;
        
        // tokenize input line on whitespaces
        // by repeatedly calling strtok on it (destructive)
        token = strtok(line, " ");
        while(token) {
            // update the position in the line
            curr_len += strlen(token) + 1;
            
            // determine the type of token (operand or operator)
            if(sscanf(token, "%d", &value) == 1) {
                // if an integer is parsed then it's an operand
                // and must be pushed to the stack, waiting for its operator
                push(&opStack, value);
            }
            // otherwise it's an operator
            else {
                // obtain the symbol as a char
                sscanf(token, " %c", &operator);
                // pop the two operands from the stack and apply the operation
                // the order obviously matters for anything but '+' and '*'
                rval = pop(&opStack); // right operand
                lval = pop(&opStack); // left operand
                // check if both calls were successful
                if(rval != NULL && lval != NULL) {
                    // evaluate the expression and assign the result
                    res = eval(operator, lval->key, rval->key);
                    //printf("%d %c %d = %d\n", lval->key, operator, rval->key, res);
                    
                    // free nodes
                    free(rval);
                    free(lval);
                    
                    // now push the result to the stack if all the tokens haven't been read yet
                    if(curr_len < line_len) {
                        push(&opStack, res);
                    }
                }
                // error: tried to pop an operand from empty stack
                else {
                    puts("error: tried to pop from empty stack");
                    exit(EXIT_FAILURE);
                }
            }
            
            // update token
            token = strtok(NULL, " ");
        }
        // print the result
        printf("result: %d\n", res);
        
        // free memory
        free(line);
        freeMem(&opStack);
    }
    else {
        puts("Failed alloc line or token");
        exit(EXIT_FAILURE);
    }
    return 0;
}
