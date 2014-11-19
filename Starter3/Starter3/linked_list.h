#ifndef _LIST_H
#define _LIST_H 1

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef union value{
	float f;
	int i;
	char s[1024];
}value_t;

typedef struct listNode
{
    int data;
    char *name;
    value_t val;
    unsigned int scope;
    int type;

    struct listNode *next;
} listNode_t;


void insert_at_begning(int value);
void insert(char *, value_t, unsigned int, int);
void insert_at_end(int value);
void insert_at_middle(int value, int loc);
int delete_from_middle(int value);
int delete_from_end();
void display();

#endif

