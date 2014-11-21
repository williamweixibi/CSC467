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
		ast->unary_expr.line = va_arg(args, int);
		break;
	case ASSIGNMENT_NODE:
		ast->assignment.left = va_arg(args,node *);
		ast->assignment.right = va_arg(args,node *);
		ast->assignment.line = va_arg(args, int);
		break;

	case IF_ELSE_STATEMENT_NODE:
		ast->if_else_statement.condition = va_arg(args, node *);
		ast->if_else_statement.then_statement = va_arg(args, node *);
		ast->if_else_statement.else_statement = va_arg(args, node *);
		ast->if_else_statement.line = va_arg(args, int);
		break;

	case CONSTRUCTOR_NODE:
		ast->constructor_exp.type = va_arg(args,node *);
		ast->constructor_exp.arguments = va_arg(args,node*);
		ast->constructor_exp.line = va_arg(args, int);
		break;

	case FUNCTION_NODE:
		ast->function_exp.function_name = va_arg(args,int);
		ast->function_exp.arguments = va_arg(args,node*);
		ast->function_exp.line = va_arg(args, int);
		break;

	case IF_STATEMENT_NODE:
		ast->if_statement.condition = va_arg(args,node *);
		ast->if_statement.then_statement = va_arg(args,node *);
		ast->if_statement.line = va_arg(args, int);
		break;

	case DECLARATION_NODE:
		ast->declaration.type=va_arg(args,node *);
		ast->declaration.iden=va_arg(args,char *);
		ast->declaration.line = va_arg(args, int);
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
		ast->variable_exp.identifier = va_arg(args, char *);
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
	int val=0;

	if(ast==NULL)
		return;

	int kind = ast->kind;

	switch(kind) {

	// ...
	case SCOPE_NODE:
		//printf("allocate\n");
		ast_free(ast->scope.declarations);
		ast_free(ast->scope.statements);
		free(ast); ast=NULL;
		break;

	case ENTER_SCOPE_NODE:
		ast_free(ast->enter_scope.scope);
		free(ast); ast=NULL;
		break;

	case DECLARATIONS_NODE:
		ast_free(ast->declarations.declarations);
		ast_free(ast->declarations.declaration);
		free(ast); ast=NULL;
		break;

	case STATEMENTS_NODE:
		ast_free(ast->statements.statements);
		ast_free(ast->statements.statement);
		free(ast); ast=NULL;
		break;

	case PREN_EXPRESSION_NODE:
		ast_free(ast->paren_exp.expression);
		free(ast); ast=NULL;
		break;

	case BINARY_EXPRESSION_NODE:
		//ast_free(ast->binary_expr.op);
		ast_free(ast->binary_expr.left);
		ast_free(ast->binary_expr.right);
		free(ast); ast=NULL;
		break;

	case UNARY_EXPRESION_NODE:
		//ast_free(ast->unary_expr.op);
		ast_free(ast->unary_expr.right);
		free(ast); ast=NULL;
		break;
	case ASSIGNMENT_NODE:
		ast_free(ast->assignment.left);
		ast_free(ast->assignment.right);
		free(ast); ast=NULL;
		break;

	case IF_ELSE_STATEMENT_NODE:
		ast_free(ast->if_else_statement.condition);
		ast_free(ast->if_else_statement.then_statement);
		ast_free(ast->if_else_statement.else_statement);
		free(ast); ast=NULL;
		break;

	case CONSTRUCTOR_NODE:
		//ast_free(ast->constructor_exp.type);
		ast_free(ast->constructor_exp.arguments);
		free(ast); ast=NULL;
		break;

	case FUNCTION_NODE:
		//ast_free(ast->function_exp.function_name);
		ast_free(ast->function_exp.arguments);
		free(ast); ast=NULL;
		break;

	case IF_STATEMENT_NODE:
		ast_free(ast->if_statement.condition);
		ast_free(ast->if_statement.then_statement);
		free(ast); ast=NULL;
		break;

	case DECLARATION_NODE:
		ast_free(ast->declaration.type);
		//ast_free(ast->declaration.iden);
		free(ast); ast=NULL;
		/*insert(ast->declaration_assignment.iden,
				ast->declaration_assignment.type->type.type_name,
				0,
				scope_count);*/
		break;

	case DECLARATION_ASSIGNMENT_NODE:

		ast_free(ast->declaration_assignment.type);
		//ast_free(ast->declaration_assignment.iden);
		ast_free(ast->declaration_assignment.value);

		/*insert(ast->declaration_assignment.iden,
				ast->declaration_assignment.type->type.type_name,
				0,
				scope_count);*/
		free(ast); ast=NULL;

		break;

	case CONST_DECLARATION_ASSIGNMENT_NODE:
		ast_free(ast->const_declaration_assignment.type);
		//ast_free(ast->const_declaration_assignment.iden);
		ast_free(ast->const_declaration_assignment.value);

		/*insert(ast->declaration_assignment.iden,
				ast->declaration_assignment.type->type.type_name,
				1,
				scope_count);*/
		free(ast); ast=NULL;

		break;

	case TYPE_NODE:
		//ast_free(ast->type.type_name);
		free(ast); ast=NULL;
		break;

	case INT_NODE:
		//ast_free(ast->int_literal.right);
		free(ast); ast=NULL;
		break;

	case FLOAT_NODE:
		//ast_free(ast->float_literal.right);
		free(ast); ast=NULL;
		break;

	case BOOL_NODE:
		//ast_free(ast->bool_literal.right);
		free(ast); ast=NULL;
		break;

	case VAR_NODE:

		free(ast->variable_exp.identifier);
		free(ast); ast=NULL;
		break;

	case ARRAY_NODE:
		free(ast->array_exp.identifier);
		//ast_free(ast->array_exp.index = va_arg(args, int);
		free(ast); ast=NULL;
		break;

	case ARGUMENTS_COMMA_NODE:
		ast_free(ast->arguments_comma.arguments);
		ast_free(ast->arguments_comma.expression);
		free(ast); ast=NULL;
		break;

	case ARGUMENTS_EXPRESSION_NODE:
		ast_free(ast->arguments_expression.expression);
		free(ast); ast=NULL;
		break;

	default: break;
	}

}

char *getType(int type){
	switch(type){
	case	INT:
		return "INT";
		break;
	case 	IVEC2:
		return "IVEC2";
		break;
	case 	IVEC3:
		return "IVEC3";
		break;
	case 	IVEC4:
		return "IVEC4";
		break;
	case 	BOOL:
		return "BOOL";
		break;
	case 	BVEC2:
		return "BVEC2";
		break;
	case 	BVEC3:
		return "BVEC3";
		break;
	case 	BVEC4:
		return "BVEC4";
		break;
	case 	FLOAT:
		return "FLOAT";
		break;
	case 	VEC2:
		return "VEC2";
		break;
	case 	VEC3:
		return "VEC3";
		break;
	case 	VEC4:
		return "VEC4";
		break;
	case 	FUNCTION:
		return "FUNCTION";
		break;
	}
}

void ast_print(node * ast) {

	if(ast==NULL)
		return;

	int kind;

	kind = ast->kind;

	switch(kind){
		case 1:

			//printf("ENTER_SCOPE_NODE %d\n", kind);
			printf("\nSCOPE ( ");
			ast_print(ast->enter_scope.scope);
			printf(" )\n");

			break;
		case 2:
			//printf("SCOPE ( ");
			//printf("SCOPE_NODE %d\n", kind);
			ast_print(ast->scope.declarations);
			ast_print(ast->scope.statements);

			break;
		case 3:
			printf("DECLARAIONS ");
			//printf("DECLARATIONS_NODE %d\n", kind);
			ast_print(ast->declarations.declarations);
			ast_print(ast->declarations.declaration);
			printf( ")\n");
			break;
		case 4:
			printf("STATEMENTS ");
			//printf("STATEMENTS_NODE %d\n", kind);
			ast_print(ast->statements.statements);
			ast_print(ast->statements.statement);
			printf(" )\n");
			break;
		case 5:
			//printf("EXPRESSION_NODE No node %d\n", kind);
			// No EXPRESSION_NODE
			break;
		case 6:
			//printf("PREN_EXPRESSION_NODE %d\n", kind);
			ast_print(ast->paren_exp.expression);
			break;
		case 7:
			printf("(UNARY %d ",ast->unary_expr.op);
			//printf("UNARY_EXPRESION_NODE %d\n", kind);
			//printf("Operator: %d\n", ast->unary_expr.op);
			ast_print(ast->unary_expr.right);
			printf(" )\n");
			break;
		case 8:
			printf("BINARY %d ", ast->binary_expr.op);
			//printf("BINARY_EXPRESSION_NODE %d\n", kind);
			//printf("Operator: %d\n", ast->binary_expr.op);
			
			ast_print(ast->binary_expr.left);
			ast_print(ast->binary_expr.right);
			printf(" )\n");
			break;
		case 9:
			printf("%d ", ast->int_literal.right);
			//printf("Integer: %d\n",ast->int_literal.right);
			break;
		case 10:
			printf("%f ", ast->float_literal.right);
			//printf("FLOAT_NODE %d\n", kind);
			//printf("Float: %f", ast->float_literal.right);
			break;
		case 11:
			printf("%s ",ast->bool_literal.right? "true" : "false");
			//printf("Bool: %d", ast->bool_literal.right);
			break;
		case 12:
			//printf("IDENT_NODE No node %d\n", kind);
			// No IDENT_NODE
			break;
		case 13:
			//printf("VAR_NODE %d\n", kind);
			printf("%s ", ast->variable_exp.identifier);
			break;
		case 14:
			//printf("ARRAY_NODE %d\n", kind);
			break;
		case 15:
			printf("\n(CALL ");
			if(ast->function_exp.function_name==0){
				printf("dp3 ");
			}else if(ast->function_exp.function_name==1){
				printf("lit ");
			}else if(ast->function_exp.function_name==2){
				printf("rsq");
			}
			//printf("FUNCTION_NODE %d\n", kind);
			ast_print(ast->function_exp.arguments);
			printf(" )\n");
			break;
		case 16:
			//printf("CONSTRUCTOR_NODE %d\n", kind);
			printf("\nCALL ");
			ast_print(ast->constructor_exp.arguments);
			printf(" )\n");
			break;
		case 17:
			//TODO: add getType
			//str_type = getType(type_name);
			//printf("%s ", str_type);
			//printf("TYPE_NODE %d\n", kind);
			break;
		case 18:
			printf("\n(IF ");
			//printf("IF_ELSE_STATEMENT_NODE %d\n", kind);
			ast_print(ast->if_else_statement.condition);
			ast_print(ast->if_else_statement.else_statement);
			ast_print(ast->if_else_statement.then_statement);
			printf(" )\n");
			break;
		case 19:
			printf("\n(IF ");
			//printf("IF_STATEMENT_NODE %d\n", kind);
			ast_print(ast->if_statement.condition);
			ast_print(ast->if_statement.then_statement);
			printf(" )\n");
			break;
		case 20:
			//printf("WHILE_STATEMENT_NODE No node %d\n", kind);
			//No WHILE_STATEMENT_NODE
			break;
		case 21:
			printf("\n(ASSIGN ");
		//	printf("ASSIGNMENT_NODE %d\n", kind);
			ast_print(ast->assignment.left);
			ast_print(ast->assignment.right);
			printf(" )\n");
			break;
		case 22:
			printf("NESTED_SCOPE_NODE No node for %d\n", kind);
			// No NESTED_SCOPE_NODE
			break;
		case 23:
			//TODO: add type
			printf("\n(DECLARATION %s ",ast->declaration.iden);
			ast_print(ast->declaration.type);
			printf(" )\n");
			break;
		case 24:
			printf("\n(DECLARATION %s ", ast->declaration_assignment.iden);
			ast_print(ast->declaration_assignment.type);
			ast_print(ast->declaration_assignment.value);
			printf(" )\n");
			break;
		case 25:
			printf("\n( CONST DECLARATION %s ", ast->const_declaration_assignment.iden);
			ast_print(ast->const_declaration_assignment.type);
			ast_print(ast->const_declaration_assignment.value);
			printf(" )\n");
			break;
		case 26:
			//printf("ARGUMENTS_COMMA_NODE %d\n", kind);
			ast_print(ast->arguments_comma.arguments);
			ast_print(ast->arguments_comma.expression);
			break;
		case 27:
			//printf("ARGUMENTS_EXPRESSION_NODE %d\n", kind);
			ast_print(ast->arguments_expression.expression);
			break;
		default:
			printf("DEFAULT!!\n");
			break;

	}

}
