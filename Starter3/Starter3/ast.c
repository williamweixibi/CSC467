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

	case PREN_EXPRESSION_NODE:
		ast->paren_exp.expression = va_arg(args, node*);
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

	case CONSTRUCTOR_NODE:
		ast->constructor_exp.type = va_arg(args,int);
		ast->constructor_exp.arguments = va_arg(args,node*);
		break;

	case FUNCTION_NODE:
		ast->constructor_exp.type = va_arg(args,int);
		ast->constructor_exp.arguments = va_arg(args,node*);
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
		ast->type.type_name=va_arg(args,int);
		break;

	case INT_NODE:
		ast->int_literal.right = va_arg(args,int);
		break;

	case FLOAT_NODE:
		ast->float_literal.right = va_arg(args,double);
		break;

	case BOOL_NODE:
		ast->bool_literal.right = va_arg(args,int);
		break;

	case VAR_NODE:
		ast->variable_exp.identifier = va_arg(args, char *);
		break;

	case ARRAY_NODE:
		ast->array_exp.identifier = va_arg(args, char *);
		ast->array_exp.index = va_arg(args, int);
		break;

	case ARGUMENTS_COMMA_NODE:
		ast->arguments_comma.arguments = va_arg(args, node *);
		ast->arguments_comma.expression = va_arg(args, node *);
		break;

	case ARGUMENTS_EXPRESSION_NODE:
		ast->arguments_expression.expression = va_arg(args, node *);
		break;

	default: break;
	}

	va_end(args);

	return ast;
}

void ast_free(node *ast) {

}

void ast_print(node * ast) {

	int kind;

	kind = ast->kind;

	switch(kind){
		case 1:
			printf("%d\n", kind);
			ast_print(ast->enter_scope.scope);
			break;
		case 2:
			printf("%d\n", kind);
			ast_print(ast->scope.declarations);
			ast_print(ast->scope.statements);
			break;
		case 3:
			printf("%d\n", kind);
			ast_print(ast->declarations.declarations);
			ast_print(ast->declarations.declaration);
			break;
		case 4:
			printf("%d\n", kind);
			ast_print(ast->statements.statements);
			ast_print(ast->statements.statement);
			break;
		case 5:
			printf("%d\n", kind);
			// No EXPRESSION_NODE
			break;
		case 6:
			printf("%d\n", kind);
			ast_print(ast->paren_exp.expression);
			break;
		case 7:
			printf("%d\n", kind);
			printf("Operator: %d", ast->unary_expr.op);
			ast_print(ast->unary_expr.right);
			break;
		case 8:
			printf("%d\n", kind);
			printf("Operator: %d", ast->binary_expr.op);
			ast_print(ast->binary_expr.left);
			ast_print(ast->binary_expr.right);
			break;
		case 9:
			printf("%d\n", kind);
			printf("Integer: %d",ast->int_literal.right);
			break;
		case 10:
			printf("%d\n", kind);
			printf("Float: %d", ast->float_literal.right);
			break;
		case 11:
			printf("%d\n", kind);
			printf("Bool: %d", ast->bool_literal.right);
			break;
		case 12:
			printf("%d\n", kind);
			// No IDENT_NODE
			break;
		case 13:
			printf("%d\n", kind);
			printf("Identifier: %s", ast->variable_exp.identifier);
			break;
		case 14:
			printf("%d\n", kind);
			break;
		case 15:
			printf("%d\n", kind);
			break;
		case 16:
			printf("%d\n", kind);
			break;
		case 17:
			printf("%d\n", kind);
			break;
		case 18:
			printf("%d\n", kind);
			break;
		case 19:
			printf("%d\n", kind);
			break;
		case 20:
			printf("%d\n", kind);
			break;
		case 21:
			printf("%d\n", kind);
			break;
		case 22:
			printf("%d\n", kind);
			break;
		case 23:
			printf("%d\n", kind);
			break;
		case 24:
			printf("%d\n", kind);
			break;
		case 25:
			printf("%d\n", kind);
			break;
		case 26:
			printf("%d\n", kind);
			break;
		case 27:
			printf("%d\n", kind);
			break;

	}

}
