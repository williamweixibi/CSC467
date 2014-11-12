
#ifndef AST_H_
#define AST_H_ 1

#include <stdarg.h>

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
	INT,
	IVEC2,
	IVEC3,
	IVEC4,
	BOOL,
	BVEC2,
	BVEC3,
	BVEC4,
	FLOAT,
	VEC2,
	VEC3,
	VEC4
} types;

typedef enum {
  UNKNOWN               ,

  SCOPE_NODE            ,
  DECLARATIONS_NODE		,
  STATEMENTS_NODE        ,

  
  EXPRESSION_NODE       ,
  UNARY_EXPRESION_NODE  ,
  BINARY_EXPRESSION_NODE,
  INT_NODE              ,
  FLOAT_NODE            ,
  IDENT_NODE            ,
  VAR_NODE              ,
  FUNCTION_NODE         ,
  CONSTRUCTOR_NODE      ,

  IF_ELSE_STATEMENT_NODE,
  IF_STATEMENT_NODE     ,
  WHILE_STATEMENT_NODE  ,
  ASSIGNMENT_NODE       ,
  NESTED_SCOPE_NODE     ,

  DECLARATION_NODE,
  DECLARATION_ASSIGNMENT_NODE,
  CONST_DECLARATION_ASSIGNMENT_NODE
} node_kind;

struct node_ {

  // an example of tagging each node with a type
  node_kind kind;

  union {
    struct {
    	node *declarations;
    	node *statements;
    } scope;

    struct {
    	node *declarations;
    	node *declaration;
    } declarations;

    struct {
    	node *statements;
    	node *statement;
    } statements;
  
    struct {
      int op;
      node *right;
    } unary_expr;

    struct {
      int op;
      node *left;
      node *right;
    } binary_expr;

    struct {
    	node *left;
    	node *right;
    }assignment;

    struct {
    	node *condition;
    	node *then_statement;
    }if_statement;

    struct {
    	node *condition;
    	node *then_statement;
    	node *else_statement;
    }if_else_statement;

    struct {
    	node *type;
    	char *iden;
    }declaration;

    struct {
    	node *type;
    	char *iden;
    	node *value;
    }declaration_assignment;

    struct {
    	node *type;
    	char *iden;
    	node *value;
    }const_declaration_assignment;

    struct {
    	int type_name;
    }type;



    // etc.
  };
};

node *ast_allocate(node_kind type, ...);
void ast_free(node *ast);
void ast_print(node * ast);

#endif /* AST_H_ */
