/*
�* File:�� stack.h
�* Author: zentut.com
�* Purpose: stack header file
�*/
#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include <stdio.h>

void s_push(int *s,int* top, int element);
int s_pop(int *s,int *top);
int s_peak(int *s,int *top);
int s_full(int *top,const int size);
int s_empty(int *top);
void s_init(int *top);
void s_display(int *s,int *top);

#endif // STACK_H_INCLUDED
