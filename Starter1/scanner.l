%{
/**********************************************************************
 *
 * **YOUR GROUP INFO SHOULD GO HERE**
 *
 *  Interface to the scanner module for CSC467 course project
 **********************************************************************/


#include "common.h"
#include "parser.tab.h"
#include "string.h"
#include <stdio.h>

#define YY_USER_INIT { yyin = inputFile; }
#define	yyinput      input
#define yTRACE(x)    { if (traceScanner) fprintf(traceFile, "TOKEN %3d : %s\n", x, yytext); }
#define yERROR(x)    { fprintf(errorFile, "\nLEXICAL ERROR, LINE %d: %s\n", yyline, x); errorOccurred = TRUE; yyterminate(); }

int CheckInt(void);
int checkNum(char c);
int yyline = 1;

%}
%option noyywrap

WS          [ \t]
ALPHABETS   [a-zA-Z]
DIGITS      [0-9]
IDENTIFIER        {ALPHABETS}*({ALPHABETS}|{DIGITS})*
%%
"/*"        {
              int c1      = 0;
              int c2      = yyinput();
              int curline = yyline;
              for(;;) {
                if (c2 == EOF) {
                  fprintf(errorFile, "\nLEXICAL ERROR, LINE %d: Unmatched /*\n", curline);
                  errorOccurred = TRUE;
                  yyterminate();
                }
                if (c1 == '*' && c2 == '/'){
                  //printf("Comment");
                  
	yTRACE((TOKEN_COMMENT));
	return (TOKEN_COMMENT);
 
                  break;
				        }
                c1 = c2;
                c2 = yyinput();
                if (c1 == '\n' && c2 != EOF)
                  yyline++;
              }
            }

"int"{WS}* {
	yTRACE((TOKEN_INT));
	return (TOKEN_INT);
 }

"float"{WS}* {
	yTRACE((TOKEN_FLOAT));
	return (TOKEN_FLOAT);
 }

"bool"{WS}* {
	yTRACE((TOKEN_BOOL));
	return (TOKEN_BOOL);
 }

"vec2"{WS}* {
	yTRACE((TOKEN_VEC2));
	return (TOKEN_VEC2);
 }

"vec3"{WS}* {
	yTRACE((TOKEN_VEC3));
	return (TOKEN_VEC3);
 }

"vec4"{WS}* {
	yTRACE((TOKEN_VEC4));
	return (TOKEN_VEC4);
 }

"bvec2"{WS}* {
	yTRACE((TOKEN_BVEC2));
	return (TOKEN_BVEC2);
 }

"bvec3"{WS}* {
	yTRACE((TOKEN_BVEC3));
	return (TOKEN_BVEC3);
 }
            
"bvec4"{WS}* {
	yTRACE((TOKEN_BVEC4));
	return (TOKEN_BVEC4);
 }

"ivec2"{WS}* {
	yTRACE((TOKEN_IVEC2));
	return (TOKEN_IVEC2);
 }

"ivec3"{WS}* {
	yTRACE((TOKEN_IVEC3));
	return (TOKEN_IVEC3);
 }

"ivec4"{WS}* {
	yTRACE((TOKEN_IVEC4));
	return (TOKEN_IVEC4);
 }

";"{WS}* {
	yTRACE((TOKEN_SEMI));
	return (TOKEN_SEMI);
 }

"{"{WS}* {
	yTRACE((TOKEN_SCOPE_START));
	return (TOKEN_SCOPE_START);
 }

"}"{WS}* {
	yTRACE((TOKEN_SCOPE_END));
	return (TOKEN_SCOPE_END);
 }

"true"{WS}* {
	yTRACE((TOKEN_TRUE));
	return (TOKEN_TRUE);
 }

"false"{WS}* {
	yTRACE((TOKEN_FALSE));
	return (TOKEN_FALSE);
 }

"void"{WS}* {
	yTRACE((TOKEN_VOID));
	return (TOKEN_VOID);
 }

"const"{WS}* {
	yTRACE((TOKEN_CONST));
	return (TOKEN_CONST);
 }

"else"{WS}* {
	yTRACE((TOKEN_ELSE));
	return (TOKEN_ELSE);
 }

{IDENTIFIER} {
	yTRACE((TOKEN_IDENTIFIER));
	return (TOKEN_IDENTIFIER);
 }

"+"{WS}* {
	yTRACE((PLUS));
	return (PLUS);
 }

"-"{WS}* {
	yTRACE((MINUS));
	return (MINUS);
 }

"*"{WS}* {
	yTRACE((MULT));
	return (MULT);
 }

"/"{WS}* {
	yTRACE((DIV));
	return (DIV);
 }

"=="{WS}* {
	yTRACE((EQUAL));
	return (EQUAL);
 }

"="{WS}* {
	yTRACE((ASSIGN));
	return (ASSIGN);
  }

"&&"{WS}* {
	yTRACE((TOKEN_AND));
	return (TOKEN_AND);
 }

"||"{WS}* {
	yTRACE((TOKEN_OR));
	return (TOKEN_OR);
 }

"!="{WS}* {
	yTRACE((TOKEN_NOT_EQ));
	return (TOKEN_NOT_EQ);
 }

"<="{WS}* {
	yTRACE((TOKEN_LTE));
	return (TOKEN_LTE);
 }

"<"{WS}* {
	yTRACE((TOKEN_LT));
	return (TOKEN_LT);
 }

">="{WS}* {
	yTRACE((TOKEN_GTE));
	return (TOKEN_GTE);
 }

">"{WS}* {
	yTRACE((TOKEN_GT));
	return (TOKEN_GT);
 }

"!"{WS}* {
	yTRACE((TOKEN_NOT));
	return (TOKEN_NOT);
 }

"^"{WS}* {
	yTRACE((TOKEN_XOR));
	return (TOKEN_XOR);
 }

"("{WS}* {
	yTRACE((TOKEN_OPENRB));
	return (TOKEN_OPENRB);
 }

")"{WS}* {
	yTRACE((TOKEN_CLOSERB));
	return (TOKEN_CLOSERB);
 }

"["{WS}* { 
	yTRACE((TOKEN_OPENSB));
	return (TOKEN_OPENSB);
 }

"]"{WS}* { 
	yTRACE((TOKEN_CLOSESB));
	return (TOKEN_CLOSESB);
  }

"while"{WS}* { 
	yTRACE((TOKEN_WHILE));
	return (TOKEN_WHILE);
  }

"if"{WS}* { 
	yTRACE((TOKEN_IF));
	return (TOKEN_IF);
  }

"lit"{WS}* { 
	yTRACE((TOKEN_LIT));
	return (TOKEN_LIT);
  }

"dp3"{WS}* { 
	yTRACE((TOKEN_DP3));
	return (TOKEN_DP3);
  }

"rsq"{WS}* { 
	yTRACE((TOKEN_RSQ));
	return (TOKEN_RSQ);
  }

"\n"{WS}* { 
	yTRACE((TOKEN_NEWLINE));
	return (TOKEN_NEWLINE);
  }

. { yERROR("Unknown token"); }


%%

int checkNum(char c){
  if(c>='0' && c<='9' )
    return 1;
  else
    return 0;
}