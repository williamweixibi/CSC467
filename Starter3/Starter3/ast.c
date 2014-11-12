#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string.h>

#include "ast.h"
#include "common.h"
#include "parser.tab.h"

#define DEBUG_PRINT_TREE 0

node *ast = NULL;

node *ast_allocate(node_kind kind, ...) {
	va_list args;

	// make the node
	node *ast = (node *) malloc(sizeof(node));
	memset(ast, 0, sizeof *ast);
	ast->kind = kind;

	va_start(args, kind);

	switch(kind) {

	// ...
	case SCOPE_NODE:
		ast->scope.declarations = va_arg(args, node *);
		ast->scope.statements = va_arg(args, node *);
		break;

	case ENTER_SCOPE_NODE:
		ast->enter_scope.scope = va_arg(args,node *);
		break;

	case DECLARATIONS_NODE:
		ast->declarations.declarations=va_arg(args, node *);
		ast->declarations.declaration = va_arg(args, node *);
		break;

	case STATEMENTS_NODE:
		ast->statements.statements = va_arg(args,node *);
		ast->statements.statement = va_arg(args, node *);
		break;

	case BINARY_EXPRESSION_NODE:
		ast->binary_expr.op = va_arg(args, int);
		ast->binary_expr.left = va_arg(args, node *);
		ast->binary_expr.right = va_arg(args, node *);
		break;

	case UNARY_EXPRESION_NODE:
		ast->unary_expr.op = va_arg(args,int);
		ast->unary_expr.right = va_arg(args,node *);
		break;
	case ASSIGNMENT_NODE:
		ast->assignment.left = va_arg(args,node *);
		ast->assignment.right = va_arg(args,node *);
		break;

	case IF_ELSE_STATEMENT_NODE:
		ast->if_else_statement.condition = va_arg(args, node *);
		ast->if_else_statement.then_statement = va_arg(args, node *);
		ast->if_else_statement.else_statement = va_arg(args, node *);
		break;


	case CONSTRUCTOR_EXP_NODE:
		ast->constructor_exp.constructor = va_arg(args,node*);
		break;

	case IF_STATEMENT_NODE:
		ast->if_statement.condition = va_arg(args,node *);
		ast->if_statement.then_statement = va_arg(args,node *);
		break;

	case DECLARATION_NODE:
		ast->declaration.type=va_arg(args,node *);
		ast->declaration.iden=va_arg(args,char *);
		break;

	case DECLARATION_ASSIGNMENT_NODE:
		ast->declaration_assignment.type=va_arg(args,node *);
		ast->declaration_assignment.iden=va_arg(args,char *);
		ast->declaration_assignment.value=va_arg(args,node *);
		break;

	case CONST_DECLARATION_ASSIGNMENT_NODE:
		ast->const_declaration_assignment.type=va_arg(args,node *);
		ast->const_declaration_assignment.iden=va_arg(args,char *);
		ast->const_declaration_assignment.value=va_arg(args,node *);
		break;

	case TYPE_NODE:
		ast->type.type_name=va_arg(args,types);
		break;
	// ...

	default: break;
	}

	va_end(args);

	return ast;
}

void ast_free(node *ast) {

}

void ast_print(node * ast) {

}
