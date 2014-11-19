#ifndef _LIST_H
#define _LIST_H 1

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


typedef struct listNode
{
    int data;
    char *name;
    unsigned int scope;
    int isConst;
    int type;

    struct listNode *next;
} listNode_t;


void insert_at_begning(int value);
void insert(char *, int, int, unsigned int);
void insert_at_end(int value);
void insert_at_middle(int value, int loc);
int delete_from_middle(int value);
int delete_from_end();
void display();

#endif

