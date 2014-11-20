
#include "semantic.h"

int checkDepth( node *ast) {

	if(ast==NULL)
		return 0;

	int kind, depth = 0;
	kind = ast->kind;

	switch(kind){
	case EXPRESSION_NODE:
		return 1;
		break;
	case PREN_EXPRESSION_NODE:
		return 1;
		break;
	case UNARY_EXPRESION_NODE:
		return 1;
		break;
	case BINARY_EXPRESSION_NODE:
		return 1;
		break;
	case INT_NODE:
		return 1;
		break;
	case FLOAT_NODE:
		return 1;
		break;
	case BOOL_NODE:
		return 1;
		break;
	case IDENT_NODE:
		return 1;
		break;
	case VAR_NODE:
		return 1;
		break;
	case ARRAY_NODE:
		return 1;
		break;
	case FUNCTION_NODE:
		return 1;
		break;
	case CONSTRUCTOR_NODE:
		return 1;
		break;
	case ARGUMENTS_COMMA_NODE:
		return 1 + checkDepth(ast->arguments_comma.arguments);
		break;
	case ARGUMENTS_EXPRESSION_NODE:
		return checkDepth(ast->arguments_expression.expression);
		break;
	default :
		printf("check depth failed: %d\n", kind);
		break;
	}

	return 0;
}

int scopeCount=0;


int semantic_check( node *ast) {

	if(ast==NULL)
		return -1;

	int kind;
	int type;
	int depth;
	int right_exp, left_exp;
	char * name;
	int index;
	kind = ast->kind;
	int isDecl=0;

	switch(kind){
		case 1:
			scopeCount++;
			//printf("ENTER_SCOPE_NODE %d\n", kind);
			semantic_check(ast->enter_scope.scope);
			scopeCount--;
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

			right_exp = semantic_check(ast->unary_expr.right);

			switch ( ast->unary_expr.op){
			case MINUS:
				if(right_exp == BOOL || right_exp==BVEC2|| right_exp==BVEC3|| right_exp==BVEC4){
					printf("ERROR UNARY_EXPRESION_NODE, operand should be arithmetic\n");
					return -1;
				}else{
					return right_exp;
				}
				break;
			case NOT:
				if(right_exp!=BOOL || right_exp!=BVEC2 || right_exp!=BVEC3 || right_exp!=BVEC4){
					printf("ERROR UNARY_EXPRESION_NODE, operand to NOT should be logical\n");
					return -1;

				}else{
					return right_exp;
				}
				break;
			}

			break;
		case 8:
			//printf("BINARY_EXPRESSION_NODE %d\n", kind);
			//printf("Operator: %d\n", ast->binary_expr.op);
			left_exp = semantic_check(ast->binary_expr.left);
			right_exp = semantic_check(ast->binary_expr.right);

			//Logical operators

			if(ast->binary_expr.op==AND_OP || ast->binary_expr.op==OR_OP){
				if(left_exp==BOOL && right_exp==BOOL){
					return BOOL;
				}else if(left_exp==BVEC2 && right_exp==BVEC2){
					return BVEC2;
				}else if(left_exp==BVEC3 && right_exp==BVEC3){
					return BVEC3;
				}else if(left_exp==BVEC4 && right_exp==BVEC4){
					return BVEC4;
				}else if(left_exp == INT || left_exp == IVEC2 || left_exp == IVEC3 || left_exp == IVEC4){
					printf("ERROR BINARY_EXPRESSION_NODE logical operators should have boolean operands\n");
					return -1;
				}else if(left_exp == FLOAT || left_exp == VEC2 || left_exp == VEC3 || left_exp == VEC4){
					printf("ERROR BINARY_EXPRESSION_NODE logical operators should have boolean operands\n");
					return -1;
				}else if(right_exp == FLOAT || right_exp == VEC2 || right_exp == VEC3 || right_exp == VEC4){
					printf("ERROR BINARY_EXPRESSION_NODE logical operators should have boolean operands\n");
					return -1;
				}else if(right_exp == INT || right_exp == IVEC2 || right_exp == IVEC3 || right_exp == IVEC4){
					printf("ERROR BINARY_EXPRESSION_NODE logical operators should have boolean operands\n");
					return -1;
				}
				else if(left_exp != right_exp){
					printf("ERROR BINARY_EXPRESSION_NODE operands should be of same base type\n");
					return -1;
				}
			}

			//comparison operators

			if(ast->binary_expr.op==LT_OP ||ast->binary_expr.op==LEQ_OP || ast->binary_expr.op==GT_OP || ast->binary_expr.op==GEQ_OP){
				if(left_exp==INT && right_exp==INT){
					return INT;
				}else if(left_exp==FLOAT && right_exp == FLOAT){
					return FLOAT;
				}else if(left_exp==BOOL || right_exp==BOOL){
					printf("ERROR BINARY_EXPRESSION_NODE comparison operators should have artimetic operands\n");
					return -1;
				}else if(left_exp== IVEC2 || left_exp==IVEC3 || left_exp==IVEC4){
					printf("ERROR BINARY_EXPRESSION_NODE operands must be scalars\n");
					return -1;
				}else if(left_exp== VEC2 || left_exp==VEC3 || left_exp==VEC4){
					printf("ERROR BINARY_EXPRESSION_NODE operands must be scalars\n");
					return -1;
				}else if(left_exp== BVEC2 || left_exp==BVEC3 || left_exp==BVEC4){
					printf("ERROR BINARY_EXPRESSION_NODE operands must be scalars\n");
					return -1;
				}else if(right_exp== IVEC2 || right_exp==IVEC3 || right_exp==IVEC4){
					printf("ERROR BINARY_EXPRESSION_NODE operands must be scalars\n");
					return -1;
				}else if(right_exp== VEC2 || right_exp==VEC3 || right_exp==VEC4){
					printf("ERROR BINARY_EXPRESSION_NODE operands must be scalars\n");
					return -1;
				}else if(right_exp== BVEC2 || right_exp==BVEC3 || right_exp==BVEC4){
					printf("ERROR BINARY_EXPRESSION_NODE operands must be scalars\n");
					return -1;
				}else if(left_exp!=right_exp){
					printf("ERROR BINARY_EXPRESSION_NODE operands should be of same base type\n");
					return -1;
				}
			}
			//comparison operators
			if(ast->binary_expr.op==EQ_OP || ast->binary_expr.op==NEQ_OP){
				if(left_exp==right_exp){
					if(left_exp==BOOL || left_exp == BVEC2 || left_exp == BVEC3 || left_exp == BVEC4){
						printf("ERROR BINARY_EXPRESSION_NODE comparison operators should have artimetic operands\n");
					}
				}else{
					printf("ERROR BINARY_EXPRESSION_NODE operands should be of same base type\n");
					return -1;
				}
			}

			//arithmetic operators add and sub
			if(ast->binary_expr.op==ADD_OP || ast->binary_expr.op==SUB_OP){
				if(left_exp==INT && right_exp==INT){
					return INT;
				}else if(left_exp==FLOAT && right_exp==FLOAT){
					return FLOAT;
				}else if(left_exp==IVEC2 && right_exp==IVEC2){
					return IVEC2;
				}else if(left_exp==IVEC3 && right_exp==IVEC3){
					return IVEC3;
				}else if(left_exp==IVEC4 && right_exp==IVEC4){
					return IVEC4;
				}else if(left_exp==VEC2 && right_exp==VEC2){
					return VEC2;
				}else if(left_exp==VEC3 && right_exp==VEC3){
					return VEC3;
				}else if(left_exp==VEC4 && right_exp==VEC4){
					return VEC4;
				}else if(left_exp==BOOL || left_exp == BVEC2 || left_exp == BVEC3 || left_exp == BVEC4){
					printf("ERROR BINARY_EXPRESSION_NODE arithmetic operators should have arithmetic operands\n");
					return -1;
				}else if(right_exp==BOOL || right_exp == BVEC2 || right_exp == BVEC3 || right_exp == BVEC4){
					printf("ERROR BINARY_EXPRESSION_NODE arithmetic operators should have arithmetic operands\n");
					return -1;
				}else if(left_exp!=right_exp){
					printf("ERROR BINARY_EXPRESSION_NODE operands should be of same base type\n");
					return -1;
				}
			}

			//arithmetic operator mult
			if(ast->binary_expr.op==MULT_OP){
				if(left_exp == INT && (right_exp==INT || right_exp==IVEC2 || right_exp==IVEC3 || right_exp==IVEC4)){
					return right_exp;
				}else if(right_exp == INT && (left_exp==INT || left_exp==IVEC2 || left_exp==IVEC3 || left_exp==IVEC4)){
					return left_exp;
				}else if(left_exp == FLOAT && (right_exp==FLOAT || right_exp==VEC2 || right_exp==VEC3 || right_exp==VEC4)){
					return right_exp;
				}else if(right_exp == FLOAT && (left_exp==FLOAT || left_exp==VEC2 || left_exp==VEC3 || left_exp==VEC4)){
					return left_exp;
				}else if(left_exp == BOOL || left_exp == BVEC2 || left_exp == BVEC3 || left_exp == BVEC4){
					printf("ERROR BINARY_EXPRESSION_NODE arithmetic operators should have arithmetic operands\n");
					return -1;
				}else if(right_exp==BOOL || right_exp == BVEC2 || right_exp == BVEC3 || right_exp == BVEC4){
					printf("ERROR BINARY_EXPRESSION_NODE arithmetic operators should have arithmetic operands\n");
					return -1;
				}else if(left_exp==right_exp){
					return left_exp;
				}else if(left_exp!=right_exp){
					printf("ERROR BINARY_EXPRESSION_NODE operands should be of same base type\n");
					return -1;
				}
			}

			//arithmetic operator /,^
			if(ast->binary_expr.op==DIV_OP || ast->binary_expr.op==POW_OP){
				if(left_exp==INT && right_exp==INT){
					return INT;
				}else if(left_exp==FLOAT && right_exp==FLOAT){
					return FLOAT;
				}else if(left_exp == BOOL || left_exp == BVEC2 || left_exp == BVEC3 || left_exp == BVEC4){
					printf("ERROR BINARY_EXPRESSION_NODE arithmetic operators should have arithmetic operands\n");
					return -1;
				}else if(right_exp==BOOL || right_exp == BVEC2 || right_exp == BVEC3 || right_exp == BVEC4){
					printf("ERROR BINARY_EXPRESSION_NODE arithmetic operators should have arithmetic operands\n");
					return -1;
				}else if(left_exp!=right_exp){
					printf("ERROR BINARY_EXPRESSION_NODE operands should be of same base type\n");
					return -1;
				}else{
					printf("ERROR BINARY_EXPRESSION_NODE operands can only be scalars\n");
					return -1;
				}

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
			int type;
			type = checkDeclaredInScope(ast->variable_exp.identifier,scopeCount);
			//printf("VAR_NODE %d\n", kind);
			if(type==-1){
				printf("ERROR: Variable not declared in scope before it is used\n");
				return -1;
			}else{
				return type;
			}
			break;
		case 14:
			//printf("ARRAY_NODE %d\n", kind);
			name = ast->array_exp.identifier;
			type = getType(name);

			index = ast->array_exp.index;
			switch(type){
			case IVEC2:
				if(index>=2){
					printf("ERROR index too high\n");
					return -1;
				}
				break;
			case IVEC3:
				if(index>=3){
					printf("ERROR index too high\n");
					return -1;
				}
				break;
			case IVEC4:
				if(index>=4){
					printf("ERROR index too high\n");
					return -1;
				}
				break;
			case BVEC2:
				if(index>=2){
					printf("ERROR index too high\n");
					return -1;
				}
				break;
			case BVEC3:
				if(index>=3){
					printf("ERROR index too high\n");
					return -1;
				}
				break;
			case BVEC4:
				if(index>=4){
					printf("ERROR index too high\n");
					return -1;
				}
				break;
			case VEC2:
				if(index>=2){
					printf("ERROR index too high\n");
					return -1;
				}
				break;
			case VEC3:
				if(index>=3){
					printf("ERROR index too high\n");
					return -1;
				}
				break;
			case VEC4:
				if(index>=4){
					printf("ERROR index too high\n");
					return -1;
				}
				break;
			default:
				printf("ERROR not vec type, only vec types may be indexed\n");
				return -1;
			}

			break;
		case 15:
			//printf("FUNCTION_NODE %d\n", kind);
			type = semantic_check(ast->function_exp.arguments);
			//TODO: get type from function name

			if(ast->function_exp.function_name == 2){ //rsq
				return FLOAT;

			}else if(ast->function_exp.function_name == 0){ //dp3
				if(type==VEC4 || type == VEC3){
					return FLOAT;
				}
				if(type==IVEC4 || type == IVEC3){
					return INT;
				}

			}else if (ast->function_exp.function_name == 1){ //lit
				return VEC4;
			}

			printf("ERROR FUNCTION_NODE\n");
			return -1;

			break;
		case 16:
			//printf("CONSTRUCTOR_NODE %d\n", kind);
			left_exp = semantic_check(ast->constructor_exp.type);
			right_exp = semantic_check(ast->constructor_exp.arguments);

			depth = checkDepth(ast->constructor_exp.arguments);

			switch(left_exp){
			case IVEC2:
				if(depth>2){
					printf("ERROR too many arguments\n");
				}
				break;
			case IVEC3:
				if(depth>3){
					printf("ERROR too many arguments\n");
				}
				break;
			case IVEC4:
				if(depth>4){
					printf("ERROR too many arguments\n");
				}
				break;
			case BVEC2:
				if(depth>2){
					printf("ERROR too many arguments\n");
				}
				break;
			case BVEC3:
				if(depth>3){
					printf("ERROR too many arguments\n");
				}
				break;
			case BVEC4:
				if(depth>4){
					printf("ERROR too many arguments\n");
				}
				break;
			case VEC2:
				if(depth>2){
					printf("ERROR too many arguments\n");
				}
				break;
			case VEC3:
				if(depth>3){
					printf("ERROR too many arguments\n");
				}
				break;
			case VEC4:
				if(depth>4){
					printf("ERROR too many arguments\n");
				}
			default:
				if(depth>1){
					printf("ERROR too many arguments\n");
				}
			}

			if(left_exp==right_exp){
				return left_exp;
			}

			if(left_exp==IVEC2 || left_exp==IVEC3 || left_exp==IVEC4){
				if(right_exp==INT){
					return INT;
				}
			}

			if(left_exp==BVEC2 || left_exp==BVEC3 || left_exp==BVEC4){
				if(right_exp==BOOL){
					return BOOL;
				}
			}

			if(left_exp==VEC2 || left_exp==VEC3 || left_exp==VEC4){
				if(right_exp==FLOAT){
					return FLOAT;
				}
			}

			if(left_exp!=right_exp){
				printf("ERROR types mismatch. %d %d\n",left_exp,right_exp);
				return -1;
			}
			break;


			break;
		case 17:
			//printf("TYPE_NODE %d\n", kind);
			return ast->type.type_name;
			break;
		case 18:
			//printf("IF_ELSE_STATEMENT_NODE %d\n", kind);
			left_exp = semantic_check(ast->if_else_statement.condition);
			if(left_exp!=BOOL){
				printf("Expression must evaluate to bool\n");
				return -1;
			}
			semantic_check(ast->if_else_statement.else_statement);
			semantic_check(ast->if_else_statement.then_statement);
			break;
		case 19:
			//printf("IF_STATEMENT_NODE %d\n", kind);
			left_exp = semantic_check(ast->if_else_statement.condition);
			if(left_exp!=BOOL){
				printf("Expression must evaluate to bool\n");
				return -1;
			}
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
			}

			if(left_exp==IVEC2 || left_exp==IVEC3 || left_exp==IVEC4){
				if(right_exp==INT){
					return INT;
				}
			}

			if(left_exp==BVEC2 || left_exp==BVEC3 || left_exp==BVEC4){
				if(right_exp==BOOL){
					return BOOL;
				}
			}

			if(left_exp==VEC2 || left_exp==VEC3 || left_exp==VEC4){
				if(right_exp==FLOAT){
					return FLOAT;
				}
			}


			if(left_exp!=right_exp){
				printf("ERROR ASSIGNMENT_NODE must be of same type %d %d\n",left_exp,right_exp);
				return -1;
			}

			break;
		case 22:
			//printf("NESTED_SCOPE_NODE No node for %d\n", kind);
			// No NESTED_SCOPE_NODE
			break;
		case 23:
			//printf("DECLARATION_NODE %d\n", kind);
			//printf("checking for %s in scope %d \n", ast->declaration.iden, scopeCount);
			/*isDecl=checkExists(ast->declaration.iden,scopeCount);
			printf("isDecl %d \n", isDecl);
			if(isDecl!=-1){
				printf("Error: Variable cannot be redeclared\n");
				return -1;
			}else{*/
				return semantic_check(ast->declaration.type);
			//}
			break;
		case 24:
			//printf("DECLARATION_ASSIGNMENT_NODE %d\n", kind);
			left_exp = semantic_check(ast->declaration_assignment.type);
			right_exp = semantic_check(ast->declaration_assignment.value);

			if(left_exp==right_exp){
				return left_exp;
			}else{
				printf("ERROR DECLARATION_ASSIGNMENT_NODE must of be same type\n");
				return -1;
			}

			break;
		case 25:
			//printf("CONST_DECLARATION_ASSIGNMENT_NODE %d\n", kind);
			left_exp = semantic_check(ast->const_declaration_assignment.type);
			right_exp = semantic_check(ast->const_declaration_assignment.value);

			if(ast->const_declaration_assignment.value->kind == VAR_NODE){
				type = getState(ast->const_declaration_assignment.value->variable_exp.identifier);
			}

			if(ast->const_declaration_assignment.value->kind == INT_NODE ||
					ast->const_declaration_assignment.value->kind == BOOL_NODE ||
					ast->const_declaration_assignment.value->kind == FLOAT_NODE ||
					type == CONST) {
				;
			}else{
				printf("ERROR const var must be initialized with a literal value or uniform variable\n");
				return -1;
			}

			if(left_exp==right_exp){
				return left_exp;
			}

			if(left_exp==IVEC2 || left_exp==IVEC3 || left_exp==IVEC4){
				if(right_exp==INT){
					return INT;
				}
			}

			if(left_exp==BVEC2 || left_exp==BVEC3 || left_exp==BVEC4){
				if(right_exp==BOOL){
					return BOOL;
				}
			}

			if(left_exp==VEC2 || left_exp==VEC3 || left_exp==VEC4){
				if(right_exp==FLOAT){
					return FLOAT;
				}
			}

			if(left_exp!=right_exp){
				printf("ERROR types must match for assignement\n");
				return -1;
			}

			break;
		case 26:
			//printf("ARGUMENTS_COMMA_NODE %d\n", kind);
			right_exp = semantic_check(ast->arguments_comma.arguments);
			left_exp = semantic_check(ast->arguments_comma.expression);

			if(right_exp==left_exp){
				return right_exp;
			}else{
				printf("ERROR ARGUMENTS_COMMA_NODE");
				return -1;
			}
			break;
		case 27:
			//printf("ARGUMENTS_EXPRESSION_NODE %d\n", kind);
			return semantic_check(ast->arguments_expression.expression);
			break;
		default:
			//printf("DEFAULT!!\n");
			return -1;
			break;

	}



  return 0; // failed checks
}
