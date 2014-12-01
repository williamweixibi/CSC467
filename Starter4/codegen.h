#ifndef CODEGEN_H
#define CODEGEN_H 1

#include <stdio.h>
#include "ast.h"
#include "string.h"

int genCode(node * ast);
int initAll(node * ast);

#endif
