#ifndef _LIST_H
#define _LIST_H 1

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef enum {
	NONCONST,
	CONST_S,
	RESULT,
	ATTRIBUTE,
	UNIFORM,
}state ;

typedef struct listNode
{
    int data;
    char *name;
    unsigned int scope;
    int state;
    int type;

    struct listNode *next;
} listNode_t;


void insert_at_begning(int value);
void insert(char *, int, int, unsigned int);
int getType(char *);
int checkDeclaredInScope(char*,int);
int checkExists(char *name, int scope);
int getState(char *);
void insert_at_end(int value);
void insert_at_middle(int value, int loc);
int delete_from_middle(int value);
int delete_from_end();
void display();

#endif

