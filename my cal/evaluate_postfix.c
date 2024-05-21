#include "evaluate_postfix.h"
#include <ctype.h>
#include <stdio.h>

#define MAX 100

// Function to print the current state of the stack
void printStack(int stack[], int top) {
    printf("Stack: ");
    for (int i = 0; i <= top; i++) {
        printf("%d ", stack[i]);
    }
    printf("\n");
}

// Function to evaluate a postfix expression
int evaluatePostfix(const char *postfix) {
    int stack[MAX];
    int top = -1;

    printf("Evaluating postfix expression: %s...\n\n", postfix);
    printf("%-30s%-30s\n", "Action", "Stack\n");

    for (int i = 0; postfix[i] != '\0';) {
        if (isdigit(postfix[i])) {
            // Parse multi-digit numbers
            int operand = 0;
            while (isdigit(postfix[i])) {
                operand = operand * 10 + (postfix[i] - '0');
                i++;
            }
            // Push operand to stack
            stack[++top] = operand;
            printf("%-30s", "Pushed operand");
            printStack(stack, top);
            // Skip whitespace characters
            while (isspace(postfix[i])) {
                i++;
            }
        } else if (isspace(postfix[i])) {
            // Skip whitespace characters
            i++;
        } else {
            // Check for valid operators
            if (postfix[i] != '+' && postfix[i] != '-' && postfix[i] != '*' && postfix[i] != '/') {
                printf("Unknown operator: %c\n", postfix[i]);
                return -1;
            }
            // Pop two operands from stack, apply operator, and push result back to stack
            if (top < 1) {
                printf("Not enough operands for operator %c\n", postfix[i]);
                return -1;
            }
            int operand2 = stack[top--];
            int operand1 = stack[top--];
            int result;

            switch (postfix[i]) {
                case '+':
                    result = operand1 + operand2;
                    break;
                case '-':
                    result = operand1 - operand2;
                    break;
                case '*':
                    result = operand1 * operand2;
                    break;
                case '/':
                    if (operand2 == 0) {
                        printf("Division by zero\n");
                        return -1;
                    }
                    result = operand1 / operand2;
                    break;
            }

            stack[++top] = result;
            printf("%-30s%d %c %d = %d\n", "Applied operator", operand1, postfix[i], operand2, result);
            printStack(stack, top);
            i++; // Move to the next character after the operator
        }
    }

    // Check if the stack contains exactly one element
    if (top != 0) {
        printf("Invalid expression: Too many operands\n");
        return -1;
    }

    // The result of the postfix expression is the last element in the stack
    printf("\nFinal result: %d\n", stack[top]);
    return stack[top];
}
