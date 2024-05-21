#include "infix_to_postfix.h"
#include <ctype.h>
#include <stdio.h>

#define MAX 100

// Function to check operator precedence
int precedence(char operator) {
    switch (operator) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        default:
            return 0;
    }
}

// Function to check if character is an operator
int isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

// Function to print current state of the stack and postfix expression
void printState(const char *stack, int top, const char *postfix) {
    printf("%-20s", "Stack: ");
    for (int i = 0; i <= top; i++) {
        printf("%c ", stack[i]);
    }
    printf("\tPostfix: %s\n", postfix);
}

// Function to convert infix expression to postfix expression and show steps
void infixToPostfix(const char *infix, char *postfix) {
    char stack[MAX];
    int top = -1;
    int j = 0; // Index for postfix array

    printf("\nConverting infix to postfix...\n\n");
    printf("%-20s\t%-20s\n", "Stack", "Postfix");

    for (int i = 0; infix[i] != '\0'; i++) {
        if (isdigit(infix[i])) {
            // Append operands (numbers) directly to postfix expression
            while (isdigit(infix[i])) {
                postfix[j++] = infix[i++];
            }
            postfix[j++] = ' '; // Add a space after each operand
            i--; // Decrement i to process the current character again
        } else if (infix[i] == '(') {
            // Push '(' to stack
            stack[++top] = infix[i];
        } else if (infix[i] == ')') {
            // Pop from stack until '(' is found
            while (top != -1 && stack[top] != '(') {
                postfix[j++] = stack[top--];
                postfix[j++] = ' '; // Add a space after each operator
            }
            top--; // Pop '(' from stack
        } else if (isOperator(infix[i])) {
            // Pop from stack to postfix if precedence of infix[i] is less than or equal to stack[top]
            while (top != -1 && precedence(stack[top]) >= precedence(infix[i])) {
                postfix[j++] = stack[top--];
                postfix[j++] = ' '; // Add a space after each operator
            }
            // Push the current operator to stack
            stack[++top] = infix[i];
        }

        // Print current state after processing each character
        printState(stack, top, postfix);
    }

    // Pop all remaining operators from the stack
    while (top != -1) {
        postfix[j++] = stack[top--];
        postfix[j++] = ' '; // Add a space after each operator
        // Print current state after each pop
        printState(stack, top, postfix);
    }

    postfix[j] = '\0'; // Null-terminate the postfix expression

    printf("\nConversion complete.\n");
    printf("Postfix expression: %s\n", postfix);
    printf("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n\n");

}
