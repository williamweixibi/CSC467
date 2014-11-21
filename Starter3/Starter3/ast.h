
#ifndef AST_H_
#define AST_H_ 1

#include <stdarg.h>

#include "linked_list.h"
extern unsigned int scope_count;

// Dummy node just so everything compiles, create your own node/nodes
//
// The code provided below is an example ONLY. You can use/modify it,
// but do not assume that it is correct or complete.
//
// There are many ways of making AST nodes. The approach below is an example
// of a descriminated union. If you choose to use C++, then I suggest looking
// into inheritance.

// forward declare
struct node_;
typedef struct node_ node;
extern node *ast;

typedef enum{
	INT,//0
	IVEC2,
	IVEC3,
	IVEC4,
	BOOL,
	BVEC2,//5
	BVEC3,
	BVEC4,
	FLOAT,
	VEC2,//9
	VEC3,
	VEC4,//11
	FUNCTION
}types;

typedef enum{
	MINUS,
	NOT
} unary_ops;

typedef enum{
	AND_OP,
	OR_OP,
	EQ_OP,
	NEQ_OP,
	LT_OP,
	LEQ_OP,
	GT_OP,
	GEQ_OP,
	ADD_OP,
	SUB_OP,
	MULT_OP,
	DIV_OP,
	POW_OP
} binary_ops;

typedef enum {
/*0*/  UNKNOWN          ,
  ENTER_SCOPE_NODE		,
  SCOPE_NODE            ,
  DECLARATIONS_NODE		,
  STATEMENTS_NODE       ,

/*5*/ EXPRESSION_NODE   ,
  PREN_EXPRESSION_NODE  ,
  UNARY_EXPRESION_NODE  ,
  BINARY_EXPRESSION_NODE,
  INT_NODE              ,

/*10*/  FLOAT_NODE      ,
  BOOL_NODE             ,
  IDENT_NODE            ,
  VAR_NODE              ,
  ARRAY_NODE			,
/*15*/  FUNCTION_NODE   ,
  CONSTRUCTOR_NODE      ,
  TYPE_NODE				,

  IF_ELSE_STATEMENT_NODE,
  IF_STATEMENT_NODE     ,
/*20*/  WHILE_STATEMENT_NODE  ,
  ASSIGNMENT_NODE       ,
  NESTED_SCOPE_NODE     ,

  DECLARATION_NODE      ,
  DECLARATION_ASSIGNMENT_NODE,
/*25*/ CONST_DECLARATION_ASSIGNMENT_NODE,

  ARGUMENTS_COMMA_NODE   ,
  ARGUMENTS_EXPRESSION_NODE

} node_kind;

struct node_ {

  // an example of tagging each node with a type
  node_kind kind;

  union {
    struct {
    	node *declarations;
    	node *statements;
      int line;
    } scope;

    struct {
    	node *scope;
      int line;
    } enter_scope;

    struct {
    	node *declarations;
    	node *declaration;
      int line;
    } declarations;

    struct {
    	node *statements;
    	node *statement;
      int line;
    } statements;
  
    struct {
      int op;
      node *right;
      int line;
    } unary_expr;

    struct {
      int op; //binary_ops enum
      node *left;
      node *right;
      int line;
    } binary_expr;

    struct {
    	node *left;
    	node *right;
      int line;
    }assignment;

    struct {
    	node *condition;
    	node *then_statement;
      int line;
    }if_statement;

    struct {
    	node *condition;
    	node *then_statement;
    	node *else_statement;
      int line;
    }if_else_statement;

    struct {
    	node * type; // types enum
    	node *arguments;
      int line;
    }constructor_exp;

    struct {
    	int function_name;
    	node *arguments;
      int line;
    }function_exp;

    struct {
    	char *identifier;
      int line;
    }variable_exp;

    struct {
    	char *identifier;
    	int index;
      int line;
    }array_exp;

    struct {
    	node *expression;
      int line;
    }paren_exp;

	struct {
    	node *type;
    	char *iden;
      int line;
    }declaration;

    struct {
    	node *type;
    	char *iden;
    	node *value;
      int line;
    }declaration_assignment;

    struct {
    	node *type;
    	char *iden;
    	node *value;
      int line;
    }const_declaration_assignment;

    struct {
    	int type_name;
      int line;
    }type;

    struct {
    	int right;
      int line;
    }int_literal;

    struct {
    	double right;
      int line;
    }float_literal;

    struct {
    	int right;
      int line;
    }bool_literal;

    struct {
        node *arguments;
        node *expression;
        int line;
    }arguments_comma;

    struct {
        node *expression;
        int line;
    }arguments_expression;
    // etc.
  };
};

node *ast_allocate(node_kind type, ...);
void ast_free(node *ast);
void ast_print(node * ast);

#endif /* AST_H_ */
