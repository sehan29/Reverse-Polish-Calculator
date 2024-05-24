// Shehan

#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<stdbool.h>

#define MAXSTACK 20
typedef int StackEntry;
typedef enum {FALSE, TRUE} Boolean;

typedef struct{
    int top;
    StackEntry entry[MAXSTACK];
}Stack;


// Creating New Stack
void CreateStack(Stack *s)
{
    s->top = -1;
}

// Checking Whether Empty or Not
Boolean IsStackEmpty(const Stack *s)
{

    if(s->top == -1)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }

}

// Checking is Stackfull
Boolean IsStackFull(const Stack *s)
{
    if(s->top == MAXSTACK-1)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }  
}

// Inserting a New Value to Stack
void Push(StackEntry item, Stack *s)
{
    if (IsStackFull(s))
    {
        printf("stack is full\n");
        exit(1);
    }

    s->entry[++s->top] = item;   

}

// Removing last Inserted Value
int Pop(Stack *s)
{
    if (IsStackEmpty(s))
    {
        printf("Stack is empty\n");
        exit(1);
    }
    return s->entry[s->top--];

}

