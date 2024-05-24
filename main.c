#include<stdio.h>
#include<string.h>
#include <ctype.h>
#include "stack_header.h"



// ayesh
typedef struct {
    char notation[100];  // To store the Reverse Polish notation
    char result[50];     // To store the result or error message
} RPNRecord;
// ayesh end



void Header();
void Main_Body_content();
void Footer();
void Insert_Reverse_Polish_Notation();
void DisplaySavedNotations();
void Main_Selection();
void Exit_Message();
void Development_Team();
int evaluatePostfix(char *expr,RPNRecord *record);
void InfixToPostfix();
void infixToPostfixConversion(char* infix, char* postfix);


char simplification[50];

int main(){

    int c;
    Header();
    Main_Body_content();
    Main_Selection(); 
    return 0;
}



// Shehan
void Main_Selection()
{
    int select_value;
    int result;

    printf("Select Your Preference - ");

    // Attempt to read an integer
    result = scanf("%d", &select_value);

    while (result != 1) {
        // Clear the input buffer
        while (getchar() != '\n');
        printf("Invalid input. Please enter a number: ");
        result = scanf("%d", &select_value);

    }
    system("cls");
    Header();

   switch (select_value)
   {
    case 1:
    
        Insert_Reverse_Polish_Notation();
        break;
    
    case 2:

        DisplaySavedNotations();
        break;

    case 3:
        Development_Team();
        break;

    case 4:
        //system("cls");
        InfixToPostfix();
        break;

    case 5:
        system("cls");
        Exit_Message();
        exit(0); 
        break;

    default:
        system("cls");
        printf("\n\n\t\t\tPlease Enter The Valid Number\n\n");
        Exit_Message();
        exit(0);
        break;
   }
   
}
// Shehan end


void Header()
{
    printf("\t---------------------------------------------------------------------\t\t\n");
    printf("\t\t\t| WELCOME TO REVERCE POLISH CALCULATOR |\t\t\t\n");
    printf("\t---------------------------------------------------------------------\t\t\n\n");
}

void Main_Body_content()
{
    printf("1. Add New Reverse Polish Notation.\n");
    printf("2. Display Calculated Notation.\n");
    printf("3. About The Development Team.\n");
    printf("4. Infix To Postfix\n");
    printf("5. Exit.\n");
    

}

void Footer()
{
    printf("-------------------------------------------------------------------------------------\n");
    printf("\t\t 2024 All Right Reserved.Developed By Code Arrow\n");
    printf("-------------------------------------------------------------------------------------\n");
}


// Ayeshhhhhhhhhh
void Insert_Reverse_Polish_Notation()
{
    int c;
    char back_btn;
    RPNRecord record;
    char Expression[100];
    printf("\t -- Enter Only Digits and ('/', '*', '-', '+') Operators in Here --\n\n");
    printf("Enter Revese Polish Notation - ");
    while ((c = getchar()) != '\n' && c != EOF) { }
    fgets(Expression,100,stdin);
    //Expression[strcspn(Expression, "\n")] = 0;
   // printf("%s\n",Expression);
    int result = evaluatePostfix(Expression,&record);

    printf("--------------------------------------------------------------------------\n");
    printf("Result of Reverse Polish Notation = %d\n", result);
    printf("--------------------------------------------------------------------------\n");

    FILE *file = fopen("Reverse_Polish_Notation.txt", "a");  // Open the file in append mode
    if (file != NULL) {

        int notationWidth = 40;
        int notationLength = strlen(record.notation);
        int spaceCount = notationWidth - notationLength;

        // Print notation and result, with notation padded to be 60 characters long
        fprintf(file, "%s", record.notation);
        for (int i = 0; i < spaceCount; i++) {
            fputc(' ', file);  // Add spaces to pad the notation
        }
        fprintf(file, "%s\n", record.result);

        fclose(file); 

    } else {
        printf("Failed to open file for writing.\n");
    }

    printf("\n<-- If You Want To Go Main Menu (Y/N) : ");
        scanf("%s",&back_btn);

    if(back_btn == 'Y' || back_btn == 'y')
    {
        system("cls");
        Header();
        Main_Body_content(); 
        Main_Selection();
    }
    else
    {
        system("cls");
        Exit_Message();
        exit(0);
    }
}
// Ayeshhhhhhhhhh end




// Dilup
int evaluatePostfix(char *expr,RPNRecord *record) {

    Stack s;
    CreateStack(&s);
    strcpy(record->notation, expr);
    int i = 0;
    while (expr[i] != '\0') {
        if (isdigit(expr[i])) {
            int operand = 0;
            while (isdigit(expr[i])) {
                operand = operand * 10 + (expr[i] - '0');
                i++;
            }
            Push(operand, &s);
        } else if (isspace(expr[i])) {
            i++; // Skip spaces
        } else {
            if (IsStackEmpty(&s)) {

                sprintf(record->result, "Invalid Expression: Not Enough Operands!");
                printf("Invalid Expression: Not Enough Operands!\n");
                return FALSE; // Return an error value
            }
            int val2 = Pop(&s);
            

            if (IsStackEmpty(&s)) {

                sprintf(record->result, "Invalid Expression: Not Enough Operands!");
                printf("Invalid Expression: Not Enough Operands!\n");
                return FALSE; // Return an error value
            }
        
            int val1 = Pop(&s);

            switch (expr[i]) {
                case '+':
                
                    printf("Step: %d + %d = %d\n", val1, val2, val1 + val2);
                    Push(val1 + val2, &s);
                    break;
                case '-':

                    printf("Step: %d - %d = %d\n", val1, val2, val1 - val2);
                    Push(val1 - val2, &s);
                    break;
                case '*':

                    printf("Step: %d * %d = %d\n", val1, val2, val1 * val2);
                    Push(val1 * val2, &s);
                    break;
                case '/':
                    if (val2 == 0) {
                        printf("Error: Division by zero!\n");
                        return FALSE; // Return an error value
                    }
                    
                    printf("Step: %d / %d = %d\n", val1, val2, val1 / val2);
                    Push(val1 / val2, &s);
                    break;
                default:

                    sprintf(record->result, "Invalid Expression: Not Enough Operands!");
                    printf("Invalid operator: %c\n", expr[i]);
                    return FALSE; // Return an error value
            }
            i++; // Move to the next character
        }
    }

    if (IsStackEmpty(&s)) {
        printf("Invalid expression: Not enough operands!\n");
        return FALSE; // Return an error value
    }

    int result = Pop(&s);

    if (!IsStackEmpty(&s)) {
        printf("Invalid expression: Too many operands!\n");
        return FALSE; // Return an error value
    }

    sprintf(record->result, "%d", result);

    return result;
}

// Dilup end




void Exit_Message()
{
    printf("\n-------------------------------------------------------------------\n");
    printf("|\t\t\t-- GOOD BYE --  \t\t\t  |\n");
    printf("-------------------------------------------------------------------");
}



//Chamod Piliyandala
void DisplaySavedNotations() {

    char back_btn;
    FILE *file = fopen("Reverse_Polish_Notation.txt", "r"); // Open the file for reading
    if (file == NULL) {
        printf("Unable to open file or file does not exist.\n");
        return;
    }

    char line[200]; // Buffer to hold each line read from the file
    printf("Saved Reverse Polish Notation and Result\n\n");
    printf("-------------------------------------------------------------------\n");
    printf("| REVERSE POLISH NOTATION \t | \t RESULT \t\t  |\n");
    printf("-------------------------------------------------------------------\n");
    while (fgets(line, sizeof(line), file) != NULL) {
        printf("%s", line); // Print each line read from the file
        printf("-------------------------------------------------------------------\n");
    }

    fclose(file); // Close the file after reading

    printf("\n<-- If You Want To Go Back (Y/N) : ");
    scanf("%s",&back_btn);

    if(back_btn == 'Y' || back_btn == 'y')
    {
        system("cls");
        Header();
        Main_Body_content(); 
        Main_Selection();
    }
    else
    {
        system("cls");
        Exit_Message();
        exit(0);
    }
}

//Chamod Piliyandala end



//malaka
void Development_Team()
{
    char back_btn;

    printf("2021T0198 - G.S.H GAMAGE\n");
    printf("2021T01205 - G.S.H GAMAGE\n");
    printf("2021T01205 - G.S.H GAMAGE\n");
    printf("2021T01205 - G.S.H GAMAGE\n");
    printf("2021T01205 - G.S.H GAMAGE\n");
    printf("2021T01205 - G.S.H GAMAGE\n");

    printf("\n<-- If You Want To Go Back (Y/N) : ");
    scanf("%s",&back_btn);

    if(back_btn == 'Y' || back_btn == 'y')
    {
        system("cls");
        Header();
        Main_Body_content(); 
        Main_Selection();
    }
    else
    {
        system("cls");
        Exit_Message();
        exit(0);
    }
}
//malaka end



int precedence(char op) {
    switch (op) {
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


// Malaka
void infixToPostfixConversion(char* infix, char* postfix) {
    Stack s;
    CreateStack(&s);
    int j = 0;

    for (int i = 0; infix[i] != '\0'; i++) {
        if (isdigit(infix[i])) {
            while (isdigit(infix[i])) {
                postfix[j++] = infix[i++];
            }
            postfix[j++] = ' ';
            i--;
        } else if (infix[i] == '(') {
            Push(infix[i], &s);
        } else if (infix[i] == ')') {
            while (!IsStackEmpty(&s) && s.entry[s.top] != '(') {
                postfix[j++] = Pop(&s);
                postfix[j++] = ' ';
            }
            Pop(&s); // Remove '(' from stack
        } else {
            while (!IsStackEmpty(&s) && precedence(infix[i]) <= precedence(s.entry[s.top])) {
                postfix[j++] = Pop(&s);
                postfix[j++] = ' ';
            }
            Push(infix[i], &s);
        }
    }

    while (!IsStackEmpty(&s)) {
        postfix[j++] = Pop(&s);
        postfix[j++] = ' ';
    }

    postfix[j - 1] = '\0'; // Remove the last space and terminate the string
}

// Malaka end





// Ravidu
void InfixToPostfix() {
    int c;
    char back_btn;
    char infix[100];
    char postfix[100];
    RPNRecord record;

    printf("\t -- Enter Only Digits and ('/', '*', '-', '+') Operators in Here --\n\n");

    printf("Enter Infix Expression - ");
    while ((c = getchar()) != '\n' && c != EOF) { }
    fgets(infix, 100, stdin);
    infix[strcspn(infix, "\n")] = 0; // Remove newline character

    infixToPostfixConversion(infix, postfix);
    printf("Postfix Expression: %s\n", postfix);

    int result = evaluatePostfix(postfix, &record);

    printf("--------------------------------------------------------------------------\n");
    printf("Result of Infix Expression = %d\n", result);
    printf("--------------------------------------------------------------------------\n");

    FILE *file = fopen("Reverse_Polish_Notation.txt", "a");  // Open the file in append mode
    if (file != NULL) {
        int notationWidth = 40;
        int notationLength = strlen(record.notation);
        int spaceCount = notationWidth - notationLength;

        // Print notation and result, with notation padded to be 60 characters long
        fprintf(file, "%s", record.notation);
        for (int i = 0; i < spaceCount; i++) {
            fputc(' ', file);  // Add spaces to pad the notation
        }
        fprintf(file, "%s\n", record.result);

        fclose(file); 
    } else {
        printf("Failed to open file for writing.\n");
    }

    printf("\n<-- If You Want To Go Main Menu (Y/N) : ");
    scanf("%s", &back_btn);

    if (back_btn == 'Y' || back_btn == 'y') {
        system("cls");
        Header();
        Main_Body_content(); 
        Main_Selection();
    } else {
        system("cls");
        Exit_Message();
        exit(0);
    }
}

// Ravidu end
