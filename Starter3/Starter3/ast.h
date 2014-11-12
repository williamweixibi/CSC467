
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

typedef enum {
  UNKNOWN               ,

  SCOPE_NODE            ,
  
  EXPRESSION_NODE       ,
  UNARY_EXPRESION_NODE  ,
  BINARY_EXPRESSION_NODE,
  INT_NODE              ,
  FLOAT_NODE            ,
  IDENT_NODE            ,
  VAR_NODE              ,
  FUNCTION_NODE         ,
  CONSTRUCTOR_NODE      ,

  STATEMENT_NODE        ,
  IF_ELSE_STATEMENT_NODE,
  IF_STATEMENT_NODE     ,
  WHILE_STATEMENT_NODE  ,
  ASSIGNMENT_NODE       ,
  NESTED_SCOPE_NODE     ,

  DECLARATION_NODE      ,

  CONSTRUCTOR_EXP_NODE  ,


} node_kind;

struct node_ {

  // an example of tagging each node with a type
  node_kind kind;

  union {
    struct {
      // declarations?
      // statements?
    } scope;
  
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
    	node *else_statement;
    }if_else_statement;

    struct {
    	node *constructor;
    }constructor_exp;

    struct {
    	node *function;
    }function_exp;

    struct {
    	int int_literal;
    }int_literal_exp;

    struct {
    	float float_literal;
    }float_literal_exp;

    struct {
    	node *variable;
    }variable_exp;

    struct {
    	int boolean;
    }boolean_exp;

    struct {
    	node *expression;
    }paren_exp;

    // etc.
  };
};

node *ast_allocate(node_kind type, ...);
void ast_free(node *ast);
void ast_print(node * ast);

#endif /* AST_H_ */
