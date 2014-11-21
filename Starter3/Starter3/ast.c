#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string.h>

#include "ast.h"
#include "common.h"
#include "parser.tab.h"


#define DEBUG_PRINT_TREE 0

unsigned int scope_count = 0;

node *ast = NULL;

node *ast_allocate(node_kind kind, ...) {
	va_list args;
	int val=0;

	// make the node
	node *ast = (node *) malloc(sizeof(node));
	memset(ast, 0, sizeof *ast);
	ast->kind = kind;
	int tmp;

	va_start(args, kind);
	//printf("allocate\n");

	switch(kind) {

	// ...
	case SCOPE_NODE:
		//printf("allocate\n");
		ast->scope.declarations = va_arg(args, node *);
		ast->scope.statements = va_arg(args, node *);
		ast->scope.line = va_arg(args, int);
		break;

	case ENTER_SCOPE_NODE:

		scope_count++;
		ast->enter_scope.scope = va_arg(args,node *);
		scope_count--;
		ast->enter_scope.line = va_arg(args, int);
		break;

	case DECLARATIONS_NODE:
		ast->declarations.declarations=va_arg(args, node *);
		ast->declarations.declaration = va_arg(args, node *);
		ast->declarations.line = va_arg(args,int);
		break;

	case STATEMENTS_NODE:
		ast->statements.statements = va_arg(args,node *);
		ast->statements.statement = va_arg(args, node *);
		ast->statements.line = va_arg(args, int);
		break;

	case PREN_EXPRESSION_NODE:
		ast->paren_exp.expression = va_arg(args, node*);
		ast->paren_exp.line = va_arg(args, int);
		break;

	case BINARY_EXPRESSION_NODE:
		ast->binary_expr.op = va_arg(args, int);
		ast->binary_expr.left = va_arg(args, node *);
		ast->binary_expr.right = va_arg(args, node *);
		ast->binary_expr.line = va_arg(args, int);
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
		ast->constructor_exp.type = va_arg(args,node *);
		ast->constructor_exp.arguments = va_arg(args,node*);
		break;

	case FUNCTION_NODE:
		ast->function_exp.function_name = va_arg(args,int);
		ast->function_exp.arguments = va_arg(args,node*);
		break;

	case IF_STATEMENT_NODE:
		ast->if_statement.condition = va_arg(args,node *);
		ast->if_statement.then_statement = va_arg(args,node *);
		break;

	case DECLARATION_NODE:
		ast->declaration.type=va_arg(args,node *);
		ast->declaration.iden=va_arg(args,char *);

		/*insert(ast->declaration_assignment.iden,
				ast->declaration_assignment.type->type.type_name,
				0,
				scope_count);*/
		break;

	case DECLARATION_ASSIGNMENT_NODE:

		ast->declaration_assignment.type=va_arg(args,node *);
		ast->declaration_assignment.iden=va_arg(args,char *);
		ast->declaration_assignment.value=va_arg(args,node *);

		/*insert(ast->declaration_assignment.iden,
				ast->declaration_assignment.type->type.type_name,
				0,
				scope_count);*/
		ast->declaration_assignment.line = va_arg(args, int);

		break;

	case CONST_DECLARATION_ASSIGNMENT_NODE:
		ast->const_declaration_assignment.type=va_arg(args,node *);
		ast->const_declaration_assignment.iden=va_arg(args,char *);
		ast->const_declaration_assignment.value=va_arg(args,node *);

		/*insert(ast->declaration_assignment.iden,
				ast->declaration_assignment.type->type.type_name,
				1,
				scope_count);*/
		ast->const_declaration_assignment.line = va_arg(args, int);

		break;

	case TYPE_NODE:
		ast->type.type_name=va_arg(args,int);
		ast->type.line = va_arg(args, int);
		break;

	case INT_NODE:
		ast->int_literal.right = va_arg(args,int);
		ast->int_literal.line = va_arg(args, int);
		break;

	case FLOAT_NODE:
		ast->float_literal.right = va_arg(args,double);
		ast->float_literal.line = va_arg(args, int);
		break;

	case BOOL_NODE:
		ast->bool_literal.right = va_arg(args,int);
		ast->bool_literal.line = va_arg(args, int);
		break;

	case VAR_NODE:
		char * tmp;
		tmp = va_arg(args, char *);

		ast->variable_exp.identifier = (char *)malloc(sizeof(char)*(strlen(tmp)+1));
		strcpy(ast->variable_exp.identifier,tmp);
		ast->variable_exp.line = va_arg(args, int);
		break;

	case ARRAY_NODE:
		ast->array_exp.identifier = va_arg(args, char *);
		ast->array_exp.index = va_arg(args, int);
		ast->array_exp.line = va_arg(args, int);
		break;

	case ARGUMENTS_COMMA_NODE:
		ast->arguments_comma.arguments = va_arg(args, node *);
		ast->arguments_comma.expression = va_arg(args, node *);
		ast->arguments_comma.line = va_arg(args, int);
		break;

	case ARGUMENTS_EXPRESSION_NODE:
		ast->arguments_expression.expression = va_arg(args, node *);
		ast->arguments_expression.line = va_arg(args, int);
		break;

	default: break;
	}

	va_end(args);

	return ast;
}

void ast_free(node *ast) {

}

void ast_print(node * ast) {

	if(ast==NULL)
		return;

	int kind;

	kind = ast->kind;

	switch(kind){
		case 1:

			printf("ENTER_SCOPE_NODE %d\n", kind);
			ast_print(ast->enter_scope.scope);

			break;
		case 2:

			printf("SCOPE_NODE %d\n", kind);
			ast_print(ast->scope.declarations);
			ast_print(ast->scope.statements);

			break;
		case 3:
			printf("DECLARATIONS_NODE %d\n", kind);
			ast_print(ast->declarations.declarations);
			ast_print(ast->declarations.declaration);
			break;
		case 4:
			printf("STATEMENTS_NODE %d\n", kind);
			ast_print(ast->statements.statements);
			ast_print(ast->statements.statement);
			break;
		case 5:
			printf("EXPRESSION_NODE No node %d\n", kind);
			// No EXPRESSION_NODE
			break;
		case 6:
			printf("PREN_EXPRESSION_NODE %d\n", kind);
			ast_print(ast->paren_exp.expression);
			break;
		case 7:
			printf("UNARY_EXPRESION_NODE %d\n", kind);
			printf("Operator: %d\n", ast->unary_expr.op);
			ast_print(ast->unary_expr.right);
			break;
		case 8:
			printf("BINARY_EXPRESSION_NODE %d\n", kind);
			printf("Operator: %d\n", ast->binary_expr.op);
			ast_print(ast->binary_expr.left);
			ast_print(ast->binary_expr.right);
			break;
		case 9:
			printf("INT_NODE %d\n", kind);
			printf("Integer: %d\n",ast->int_literal.right);
			break;
		case 10:
			printf("FLOAT_NODE %d\n", kind);
			printf("Float: %f", ast->float_literal.right);
			break;
		case 11:
			printf("BOOL_NODE %d\n", kind);
			printf("Bool: %d", ast->bool_literal.right);
			break;
		case 12:
			printf("IDENT_NODE No node %d\n", kind);
			// No IDENT_NODE
			break;
		case 13:
			printf("VAR_NODE %d\n", kind);
			printf("Identifier: %s\n", ast->variable_exp.identifier);
			break;
		case 14:
			printf("ARRAY_NODE %d\n", kind);
			break;
		case 15:
			printf("FUNCTION_NODE %d\n", kind);
			ast_print(ast->function_exp.arguments);
			break;
		case 16:
			printf("CONSTRUCTOR_NODE %d\n", kind);
			ast_print(ast->constructor_exp.arguments);
			break;
		case 17:
			printf("TYPE_NODE %d\n", kind);
			break;
		case 18:
			printf("IF_ELSE_STATEMENT_NODE %d\n", kind);
			ast_print(ast->if_else_statement.condition);
			ast_print(ast->if_else_statement.else_statement);
			ast_print(ast->if_else_statement.then_statement);
			break;
		case 19:
			printf("IF_STATEMENT_NODE %d\n", kind);
			ast_print(ast->if_statement.condition);
			ast_print(ast->if_statement.then_statement);
			break;
		case 20:
			printf("WHILE_STATEMENT_NODE No node %d\n", kind);
			//No WHILE_STATEMENT_NODE
			break;
		case 21:
			printf("ASSIGNMENT_NODE %d\n", kind);
			ast_print(ast->assignment.left);
			ast_print(ast->assignment.right);
			break;
		case 22:
			printf("NESTED_SCOPE_NODE No node for %d\n", kind);
			// No NESTED_SCOPE_NODE
			break;
		case 23:
			printf("DECLARATION_NODE %d\n", kind);
			ast_print(ast->declaration.type);
			break;
		case 24:
			printf("DECLARATION_ASSIGNMENT_NODE %d\n", kind);
			ast_print(ast->declaration_assignment.type);
			ast_print(ast->declaration_assignment.value);
			break;
		case 25:
			printf("CONST_DECLARATION_ASSIGNMENT_NODE %d\n", kind);
			ast_print(ast->const_declaration_assignment.type);
			ast_print(ast->const_declaration_assignment.value);
			break;
		case 26:
			printf("ARGUMENTS_COMMA_NODE %d\n", kind);
			ast_print(ast->arguments_comma.arguments);
			ast_print(ast->arguments_comma.expression);
			break;
		case 27:
			printf("ARGUMENTS_EXPRESSION_NODE %d\n", kind);
			ast_print(ast->arguments_expression.expression);
			break;
		default:
			printf("DEFAULT!!\n");
			break;

	}

}
