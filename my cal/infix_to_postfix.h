#ifndef MY_CAL_INFIX_TO_POSTFIX_H
#define MY_CAL_INFIX_TO_POSTFIX_H

#define MAX 100

// Function prototypes
void infixToPostfix(const char *infix, char *postfix); // Convert infix expression to postfix expression
int precedence(char operator); // Determine precedence of an operator
int isOperator(char c); // Check if a character is an operator
void printState(const char *stack, int top, const char *postfix); // Print current state of the stack and postfix expression

#endif // MY_CAL_INFIX_TO_POSTFIX_H
