#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "infix_to_postfix.h"
#include "evaluate_postfix.h"


// Function to check if a given calculation is in infix notation
int isExpressionInfix(const char *calculation) {
    int numOpenParentheses = 0;
    int numCloseParentheses = 0;
    int numOperators = 0;
    int numOperands = 0;

    for (int i = 0; calculation[i] != '\0'; i++) {
        if (calculation[i] == '(') {
            numOpenParentheses++;
        } else if (calculation[i] == ')') {
            numCloseParentheses++;
        } else if (isdigit(calculation[i])) {
            numOperands++;
            // Skip all continuous digits for multi-digit numbers
            while (isdigit(calculation[i])) {
                i++;
            }
            i--; // Decrement i to account for the last character of the operand
        } else if (calculation[i] == '+' || calculation[i] == '-' || calculation[i] == '*' || calculation[i] == '/') {
            numOperators++;
        }
    }

    // Infix expression should have exactly one more operand than operators
    return numOpenParentheses == numCloseParentheses && numOperands == numOperators + 1;
}


int isExpressionPostfix(const char *calculation) {
    int length = strlen(calculation);
    // Check if the last character is an operator
    if (length > 0 && (calculation[length - 1] == '+' || calculation[length - 1] == '-' || calculation[length - 1] == '*' || calculation[length - 1] == '/')) {
        return 1; // Postfix expression
    } else {
        return 0; // Not a postfix expression
    }
}


int checkValidityCalculation(char *calculation, const char *option) {
    int balance = 0; // To check the balance of parentheses

    for (int i = 0; i < strlen(calculation); i++) {
        if (isdigit(calculation[i]) || calculation[i] == '+' || calculation[i] == '-' || calculation[i] == '*' || calculation[i] == '/' || calculation[i] == ' ' || (calculation[i] == '(' && strcmp(option, "1") == 0) || (calculation[i] == ')' && strcmp(option, "1") == 0)) {
            if (calculation[i] == '(' && strcmp(option, "1") == 0) {
                balance++;
            } else if (calculation[i] == ')' && strcmp(option, "1") == 0) {
                balance--;
                // If balance goes negative, there are more closing parentheses than opening ones
                if (balance < 0) {
                    return 0; // Indicates invalid input
                }
            }
        } else {
            return 0; // Indicates invalid input
        }
    }

    // Check if all opened parentheses are closed (only relevant for infix)
    if (strcmp(option, "1") == 0 && balance != 0) {
        return 0; // Indicates invalid input
    }

    return 1; // Indicates valid input
}



char *removeSpacesInCalculation(char *calculation) {
    int i, j = 0;
    for (i = 0; calculation[i]; i++) {
        if (calculation[i] != ' ') {
            calculation[j++] = calculation[i];
        }
    }
    calculation[j] = '\0'; // Null-terminate the modified string
    return calculation;
}


// Function to get the calculation from the user based on the selected option
char* enterCalculation(const char *option) {
    static char calculation[100]; // Define a static array to hold the input

    printf("\n\n");
    printf("\t*Enter only digits and ('/', '*', '-', '+') operators in here *");
    printf("\n\n");
    if (strcmp(option, "1") == 0) {
        printf("\t\t\tInsert your infix calculation   : ");
    } else if (strcmp(option, "2") == 0) {
        printf("**(Separate numbers(specially two digit numbers eg: 23 45+) by space to help the calculator identify separate numbers)**");
        printf("\n\n\t\t\t");
        printf("\t\t\tInsert your postfix calculation: ");
    }

    scanf(" %99[^\n]", calculation); // Read a line of input
    return calculation; // Return the input string
}


// Function to check the validity of the option entered by the user
int checkValidityOfOption(const char *option) {
    if (strcmp(option, "Q") == 0 || strcmp(option, "q") == 0) {
        return 0; // Indicates exit
    } else if (strcmp(option, "1") == 0 || strcmp(option, "2") == 0) {
        return 1; // Indicates valid option
    }
    return 3; // Indicates invalid option
}


// Function to display the user interface and get user input
char* firstUserInterface() {
    static char option[4]; // Define a static array to hold the input

    printf("\t\t\t-------------------------------------------\t\t\t\n");
    printf("\t\t\t******** Reverse Polish Calculator ********\t\t\t\n");
    printf("\t\t\t-------------------------------------------\t\t\t\n");
    printf("\n\n");

    printf("\t\t1) Convert infix to postfix and obtain the answer         \n");
    printf("\t\t2) Insert the postfix expression and retrieve the answer  \n");
    printf("\t\t3) Press Q/q to exit                                      \n\n");

    printf("\t* Your Option : ");
    scanf(" %3s", option); // Read a line of input
    return option; // Return the input string
}


int main() {
    char *option;
    int validity;
    do {
        option = firstUserInterface();
        validity = checkValidityOfOption(option);

        if (validity == 0) {
            printf("\t\t\tExiting program...\n");
            return 0;
        }

        if (validity == 3) {
            printf("\n");
            printf("\t\t\tError: Invalid input!\n");
            printf("_______________________________________________________________________________\n\n\n");
        }

    } while (validity == 3);


    char *calculation;
    calculation = enterCalculation(option);

    if (strcmp(option, "1") == 0) {
        removeSpacesInCalculation(calculation);
    }

    while (checkValidityCalculation(calculation, option) == 0) {
        printf("\tError: The calculation contains invalid characters!\n");
        printf("_______________________________________________________________________________\n\n");

        calculation = enterCalculation(option);
    }


    if (strcmp(option, "1") == 0) {
        if (!isExpressionInfix(calculation)) {
            return 0;
        }
    } else if (strcmp(option, "2") == 0) {
        if (!isExpressionPostfix(calculation)) {
            return 0;
        }
    }


    char postfix[100];
    if (strcmp(option, "1") == 0) {
        infixToPostfix(calculation, postfix);
        evaluatePostfix(postfix);
    } else if (strcmp(option, "2") == 0) {
        evaluatePostfix(calculation);
    }


    return 0;
}
