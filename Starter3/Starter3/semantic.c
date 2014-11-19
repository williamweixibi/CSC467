
#include "semantic.h"

int semantic_check( node *ast) {

	if(ast==NULL)
		return -1;

	int kind;
	int right_exp, left_exp;
	char * name;

	kind = ast->kind;

	switch(kind){
		case 1:
			//printf("ENTER_SCOPE_NODE %d\n", kind);
			semantic_check(ast->enter_scope.scope);

			break;
		case 2:
			//printf("SCOPE_NODE %d\n", kind);
			semantic_check(ast->scope.declarations);
			semantic_check(ast->scope.statements);

			break;
		case 3:
			//printf("DECLARATIONS_NODE %d\n", kind);
			semantic_check(ast->declarations.declarations);
			return semantic_check(ast->declarations.declaration);
			break;
		case 4:
			//printf("STATEMENTS_NODE %d\n", kind);
			semantic_check(ast->statements.statements);
			return semantic_check(ast->statements.statement);
			break;
		case 5:
			//printf("EXPRESSION_NODE No node %d\n", kind);
			// No EXPRESSION_NODE
			break;
		case 6:
			//printf("PREN_EXPRESSION_NODE %d\n", kind);
			return semantic_check(ast->paren_exp.expression);
			break;
		case 7:
			//printf("UNARY_EXPRESION_NODE %d\n", kind);
			//printf("Operator: %d\n", ast->unary_expr.op);

			switch ( ast->unary_expr.op){
			case MINUS:
				return semantic_check(ast->unary_expr.right);
				break;
			case NOT:
				return BOOL;
				break;
			}

			break;
		case 8:
			//printf("BINARY_EXPRESSION_NODE %d\n", kind);
			//printf("Operator: %d\n", ast->binary_expr.op);
			left_exp = semantic_check(ast->binary_expr.left);
			right_exp = semantic_check(ast->binary_expr.right);


			if(left_exp==right_exp){
				return left_exp;
			}else{
				printf("ERROR BINARY_EXPRESSION_NODE\n");
				return -1;
			}

			break;
		case 9:
			//printf("INT_NODE %d\n", kind);
			//printf("Integer: %d\n",ast->int_literal.right);
			return INT;
			break;
		case 10:
			//printf("FLOAT_NODE %d\n", kind);
			//printf("Float: %f", ast->float_literal.right);
			return FLOAT;
			break;
		case 11:
			//printf("BOOL_NODE %d\n", kind);
			//printf("Bool: %d", ast->bool_literal.right);
			return BOOL;
			break;
		case 12:
			//printf("IDENT_NODE No node %d\n", kind);
			// No IDENT_NODE
			break;
		case 13:
			//printf("VAR_NODE %d\n", kind);
			//printf("Identifier: %s\n", ast->variable_exp.identifier);

			return  getType(ast->variable_exp.identifier);
			break;
		case 14:
			//printf("ARRAY_NODE %d\n", kind);
			break;
		case 15:
			//printf("FUNCTION_NODE %d\n", kind);
			semantic_check(ast->function_exp.arguments);
			//TODO: get type from function name
			break;
		case 16:
			//printf("CONSTRUCTOR_NODE %d\n", kind);
			semantic_check(ast->constructor_exp.arguments);
			//TODO: get type from function name
			break;
		case 17:
			//printf("TYPE_NODE %d\n", kind);
			return ast->type.type_name;
			break;
		case 18:
			//printf("IF_ELSE_STATEMENT_NODE %d\n", kind);
			semantic_check(ast->if_else_statement.condition);
			semantic_check(ast->if_else_statement.else_statement);
			semantic_check(ast->if_else_statement.then_statement);
			break;
		case 19:
			//printf("IF_STATEMENT_NODE %d\n", kind);
			semantic_check(ast->if_statement.condition);
			semantic_check(ast->if_statement.then_statement);
			break;
		case 20:
			//printf("WHILE_STATEMENT_NODE No node %d\n", kind);
			//No WHILE_STATEMENT_NODE
			break;
		case 21:
			//printf("ASSIGNMENT_NODE %d\n", kind);
			semantic_check(ast->assignment.left);
			// set type of symbol in local var
			name = ast->assignment.left->variable_exp.identifier;


			left_exp = getType(name);
			right_exp = semantic_check(ast->assignment.right);

			if(left_exp==right_exp){
				return left_exp;
			}else{
				printf("ERROR ASSIGNMENT_NODE\n");
				return -1;
			}

			break;
		case 22:
			//printf("NESTED_SCOPE_NODE No node for %d\n", kind);
			// No NESTED_SCOPE_NODE
			break;
		case 23:
			//printf("DECLARATION_NODE %d\n", kind);
			return semantic_check(ast->declaration.type);
			break;
		case 24:
			//printf("DECLARATION_ASSIGNMENT_NODE %d\n", kind);
			left_exp = semantic_check(ast->declaration_assignment.type);
			right_exp = semantic_check(ast->declaration_assignment.value);

			if(left_exp==right_exp){
				return left_exp;
			}else{
				printf("ERROR DECLARATION_ASSIGNMENT_NODE\n");
				return -1;
			}

			break;
		case 25:
			//printf("CONST_DECLARATION_ASSIGNMENT_NODE %d\n", kind);
			left_exp = semantic_check(ast->const_declaration_assignment.type);
			right_exp = semantic_check(ast->const_declaration_assignment.value);

			if(left_exp==right_exp){
				return left_exp;
			}else{
				printf("ERROR CONST_DECLARATION_ASSIGNMENT_NODE\n");
				return -1;
			}

			break;
		case 26:
			//printf("ARGUMENTS_COMMA_NODE %d\n", kind);
			semantic_check(ast->arguments_comma.arguments);
			semantic_check(ast->arguments_comma.expression);
			break;
		case 27:
			//printf("ARGUMENTS_EXPRESSION_NODE %d\n", kind);
			semantic_check(ast->arguments_expression.expression);
			break;
		default:
			//printf("DEFAULT!!\n");
			break;

	}



  return 0; // failed checks
}
