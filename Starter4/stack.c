/*
�* File:��  stack.c
�* Author:  zentut.com
�* Purpose: stack source code file
�*/

/*
	initialize stack pointer
*/
#include "stack.h" 

void s_init(int *top)
{
    *top = 0;
}

/*
	push an element into stack
	precondition: the stack is not full
*/
void s_push(int *s,int* top, int element)
{
    s[(*top)++] = element;
}

int s_peak(int *s,int *top)
{
	int tmp = *top - 1;
    return s[tmp];
}

/*
	remove an element from stack
	precondition: stack is not empty
*/
int s_pop(int *s,int *top)
{
    return s[--(*top)];
}
/*
	return 1 if stack is full, otherwise return 0
*/
int s_full(int *top,const int size)
{
    return *top == size ? 1 : 0;
}
/*
	return 1 if the stack is empty, otherwise return 0
*/
int s_empty(int *top)
{
    return *top == 0 ? 1 : 0;
}

/*
    display stack content
*/
void s_display(int *s,int *top)
{
    printf("Stack: ");
    int i;
    for(i = 0; i < *top; i++)
    {
        printf("%d ",s[i]);
    }
    printf("\n");
}
