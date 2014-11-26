#define print(...) printf(__VA_ARGS__)

#include "codegen.h"

#include "linked_list.h"
#include "semantic.h"
static int scopeCount;
int tmpCount =1;
int prmCount =1;

char toChar(int n){
	switch(n){
	case 0:
		return 'x';
	case 1:
		return 'y';
	case 2:
		return 'z';
	case 3:
		return 'w';
	}
}

int genCode(node *ast) {

	if(ast==NULL){
		//printf("ERROR empty tree\n");
		return 0;
	}

	int kind;
	int type;
	int depth;
	int tmp;
	int right_exp, left_exp;
	char * name;
	int index;
	kind = ast->kind;
	int isDecl=0;
	int val;

	switch(kind){
		case 1:
			scopeCount++;
			//printf("ENTER_SCOPE_NODE %d\n", kind);

			right_exp = genCode(ast->enter_scope.scope);
			scopeCount--;
			return right_exp;
			break;
		case 2:
			//printf("SCOPE_NODE %d\n", kind);
			right_exp = genCode(ast->scope.declarations);
			left_exp = genCode(ast->scope.statements);

			if(right_exp==-1 || left_exp == -1)
				return -1;

			return 0;
			break;
		case 3:
			//printf("DECLARATIONS_NODE %d\n", kind);
			right_exp = genCode(ast->declarations.declarations);
			left_exp = genCode(ast->declarations.declaration);

			if(right_exp==-1 || left_exp == -1)
				return -1;

			return left_exp;
			break;
		case 4:
			//printf("STATEMENTS_NODE %d\n", kind);
			right_exp = genCode(ast->statements.statements);
			left_exp = genCode(ast->statements.statement);

			if(right_exp==-1 || left_exp == -1)
				return -1;

			return left_exp;
			break;
		case 5:
			//printf("EXPRESSION_NODE No node %d\n", kind);
			// No EXPRESSION_NODE
			break;
		case 6:
			//printf("PREN_EXPRESSION_NODE %d\n", kind);
			return genCode(ast->paren_exp.expression);
			break;
		case 7:
			//printf("UNARY_EXPRESION_NODE %d\n", kind);
			//printf("Operator: %d\n", ast->unary_expr.op);

			right_exp = genCode(ast->unary_expr.right);

			switch ( ast->unary_expr.op){
			case MINUS:
				print("MULT tmpVar%d, tmpVar%d, -1.0;\n", tmpCount, right_exp);
				val =  tmpCount++;
				return val;
				break;
			case NOT:
				print("NOT tmpVar%d, tmpVar%d;\n", tmpCount, right_exp);
				val = tmpCount++;
				return val;
				break;
			}

			break;
		case 8:
			//printf("BINARY_EXPRESSION_NODE %d\n", kind);
			//printf("Operator: %d\n", ast->binary_expr.op);

			if(ast->binary_expr.op==AND_OP){
				print("AND ");
			}
			else if(ast->binary_expr.op==OR_OP){
				print("OR ");
			}
			else if(ast->binary_expr.op==LT_OP){
				print("SLT ");
			}
			else if(ast->binary_expr.op==LEQ_OP){
				print("SLE ");
			}
			else if(ast->binary_expr.op==GT_OP){
				print("SGT ");
			}else if(ast->binary_expr.op==GEQ_OP){
				print("SGE ");
			}
			else if(ast->binary_expr.op==EQ_OP){
				print("SEQ ");
			}
			else if(ast->binary_expr.op==NEQ_OP){
				print("SNE ");
			}else if(ast->binary_expr.op==ADD_OP){
				print("ADD ");
			}
			else if(ast->binary_expr.op==SUB_OP){
				print("SUB ");
			}
			else if(ast->binary_expr.op==MULT_OP){
				print("MUL ");
			}
			else if(ast->binary_expr.op==DIV_OP){
				print("DIV ");
			}
			else if(ast->binary_expr.op==POW_OP){
				print("POW ");
			}

			left_exp = genCode(ast->binary_expr.left);
			if(left_exp==0){
				print(",");
			}

			right_exp = genCode(ast->binary_expr.right);
			if(right_exp == 0  || left_exp == 0){
				print(", tmpVar%d;\n", tmpCount);
			}else{
				print("tmpVar%d , tmpVar%d, tmpVar%d;\n", left_exp, right_exp, tmpCount);
			}
			val = tmpCount++;
			return val;
			break;
		case 9:
			//printf("INT_NODE %d\n", kind);
			//printf("Integer: %d\n",ast->int_literal.right);
			print("MOV tmpVar%d, %d.0;\n", tmpCount, ast->int_literal.right);
			val = tmpCount++;
			return val;
			break;
		case 10:
			//printf("FLOAT_NODE %d\n", kind);
			//printf("Float: %f", ast->float_literal.right);
			print("MOV tmpVar%d, %d;\n", tmpCount, ast->float_literal.right);
			val = tmpCount++;
			return val;
			break;
		case 11:
			//printf("BOOL_NODE %d\n", kind);
			//printf("Bool: %d", ast->bool_literal.right);
			if(ast->bool_literal.right==1){
				print("MOV tmpVar%d, %f;\n", tmpCount, 1.0);
				val = tmpCount++;
			}else if(ast->bool_literal.right==0){
				print("MOV tmpVar%d, %f;\n", tmpCount, -1.0);
				val = tmpCount++;
			}
			return val;
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
				printf("ERROR: Variable not declared in scope before it is used line:%d \n", ast->variable_exp.line );
				return -1;
			}else{
				return type;
			}
			break;
		case 14:
			name = ast->array_exp.identifier;
			type = getType(name);

			index = ast->array_exp.index;

			if(strcmp(name,"gl_FragColor")==0){
				print("result.color.%c", toChar(index));
				return 0;

			}else if(strcmp(name,"gl_FragDepth")==0){
				print("result.depth.%c", toChar(index));
				return 0;

			}else if(strcmp(name,"gl_FragCoord")==0){
				print("fragment.position.%c", toChar(index));
				return 0;

			}else if(strcmp(name,"gl_TexCoord")==0){
				print("fragment.texcoord.%c", toChar(index));
				return 0;

			}else if(strcmp(name,"gl_Color")==0){
				print("fragment.color.%c", toChar(index));
				return 0;

			}else if(strcmp(name,"gl_Secondary")==0){
				print("fragment.color.secondary.%c", toChar(index));
				return 0;

			}else if(strcmp(name,"gl_FogFragCoord")==0){
				print("fragment.fogcoord.%c", toChar(index));
				return 0;

			}else if(strcmp(name,"gl_Light_Half")==0){
				print("state.light[0].half.%c", toChar(index));
				return 0;

			}else if(strcmp(name,"gl_Light_Ambient")==0){
				print("state.lightmodel.ambient.%c", toChar(index));
				return 0;

			}else if(strcmp(name,"gl_Material_Shininess")==0){
				print("state.material.shininess.%c", toChar(index));
				return 0;

			}else if(strcmp(name,"env1")==0){
				print("program.env[1].%c", toChar(index));
				return 0;

			}else if(strcmp(name,"env2")==0){
				print("program.env[2].%c", toChar(index));
				return 0;

			}else if(strcmp(name,"env3")==0){
				print("program.env[3].%c", toChar(index));
				return 0;

			}else{
				val = tmpCount;
				tmpCount++;
				print("TEMP tmpVar%d\n", val);
				print("MOV tmpVar%d, %s.%c\n", val, name, toChar(index));
				return val;
			}


			break;
		case 15:
			//printf("FUNCTION_NODE %d\n", kind);
			if(type==-1)
				return -1;

			type = genCode(ast->function_exp.arguments);

			if(ast->function_exp.function_name == 2){ //rsq
				print("rsq tmpVar%d", type);
			}else if(ast->function_exp.function_name == 0){ //dp3
				print("dp3 tmpVar%d", type);
			}else if (ast->function_exp.function_name == 1){ //lit
				print("lit tmpVar%d", type);
			}

			print("\n");

			return 0;

			break;
		case 16:
			//printf("CONSTRUCTOR_NODE %d\n", kind);
			left_exp = genCode(ast->constructor_exp.type);
			right_exp = genCode(ast->constructor_exp.arguments);

			return 0;

			break;
		case 17:
			//printf("TYPE_NODE %d\n", kind);
			return 0;//ast->type.type_name;
			break;
		case 18:
			printf("#IF_ELSE_STATEMENT_NODE %d\n", kind);
			left_exp = genCode(ast->if_else_statement.condition);

			/*if(left_exp == -1)
				return -1;

			if(left_exp!=BOOL){
				printf("ERROR: Expression must evaluate to bool line: %d\n", ast->if_else_statement.line);
				return -1;
			}*/
			genCode(ast->if_else_statement.else_statement);
			genCode(ast->if_else_statement.then_statement);
			return 0;
			break;
		case 19:
			printf("#IF_STATEMENT_NODE %d\n", kind);
			left_exp = genCode(ast->if_else_statement.condition);
			/*if(left_exp == -1)
				return -1;

			if(left_exp!=BOOL){
				printf("ERROR: Expression must evaluate to bool line: %d\n", ast->if_else_statement.line);
				return -1;
			}*/
			genCode(ast->if_statement.then_statement);
			return 0;
			break;
		case 20:
			//printf("WHILE_STATEMENT_NODE No node %d\n", kind);
			//No WHILE_STATEMENT_NODE
			break;
		case 21:
			//printf("ASSIGNMENT_NODE %d\n", kind);
			tmp = genCode(ast->assignment.left);
			// set type of symbol in local var
			name = ast->assignment.left->variable_exp.identifier;

			left_exp = getType(name);
			right_exp = genCode(ast->assignment.right);

			print("MOV %s, tmpVar%d;\n", name, right_exp);

			return 0;

			break;
		case 22:
			//printf("NESTED_SCOPE_NODE No node for %d\n", kind);
			// No NESTED_SCOPE_NODE
			break;
		case 23:
			//printf("DECLARATION_NODE %d\n", kind);
			print("#Declaration \n");
			print("TEMP %s;\n", ast->declaration.iden  );

			return 0;
			break;
		case 24:
			//printf("DECLARATION_ASSIGNMENT_NODE %d\n", kind);
			left_exp = genCode(ast->declaration_assignment.type);
			right_exp = genCode(ast->declaration_assignment.value);

			print("#Declaration Assignement\n");
			print("TEMP %s;\n", ast->declaration_assignment.iden);
			print("MOV %s, tmpVar%d;\n", ast->declaration_assignment.iden, tmpCount);

			return 0;
			break;
		case 25:
			//printf("CONST_DECLARATION_ASSIGNMENT_NODE %d\n", kind);
			left_exp = genCode(ast->const_declaration_assignment.type);
			right_exp = genCode(ast->const_declaration_assignment.value);

			print("PARAM %s;\n", ast->const_declaration_assignment.iden);
			print("MOV %s, tmpVar%d;\n", ast->const_declaration_assignment.iden, right_exp);

			return 0;
			break;
		case 26:
			print("#ARGUMENTS_COMMA_NODE %d\n", kind);
			val = tmpCount++;

			print("TEMP tmpVar%d = {", val);
			right_exp = genCode(ast->arguments_comma.arguments);
			print(", ");
			left_exp = genCode(ast->arguments_comma.expression);
			print("}\n");

			return val;

			break;
		case 27:
			//printf("ARGUMENTS_EXPRESSION_NODE %d\n", kind);
			return genCode(ast->arguments_expression.expression);
			break;
		default:
			printf("DEFAULT!!\n");
			return -1;
			break;

	}



  return 0; // failed checks
}
