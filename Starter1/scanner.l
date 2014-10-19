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
IDENTIFIER  (({ALPHABETS}*[_]|[_]*)({ALPHABETS}|{DIGITS})*([_]*({ALPHABETS}|{DIGITS})*))*
SIGN 		[-+]
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
				
 
                  break;
				        }
                c1 = c2;
                c2 = yyinput();
                if (c1 == '\n' && c2 != EOF)
                  yyline++;
              }
              return (TOKEN_COMMENT);
            }

"int" {
	yTRACE((TOKEN_INT_DEC));
	return (TOKEN_INT_DEC);
 }

"float" {
	yTRACE((TOKEN_FLOAT_DEC));
	return (TOKEN_FLOAT_DEC);
 }

"bool" {
	yTRACE((TOKEN_BOOL));
	return (TOKEN_BOOL);
 }

"vec2" {
	yTRACE((TOKEN_VEC2));
	return (TOKEN_VEC2);
 }

"vec3" {
	yTRACE((TOKEN_VEC3));
	return (TOKEN_VEC3);
 }

"vec4" {
	yTRACE((TOKEN_VEC4));
	return (TOKEN_VEC4);
 }

"bvec2" {
	yTRACE((TOKEN_BVEC2));
	return (TOKEN_BVEC2);
 }

"bvec3" {
	yTRACE((TOKEN_BVEC3));
	return (TOKEN_BVEC3);
 }
            
"bvec4" {
	yTRACE((TOKEN_BVEC4));
	return (TOKEN_BVEC4);
 }

"ivec2" {
	yTRACE((TOKEN_IVEC2));
	return (TOKEN_IVEC2);
 }

"ivec3" {
	yTRACE((TOKEN_IVEC3));
	return (TOKEN_IVEC3);
 }

"ivec4" {
	yTRACE((TOKEN_IVEC4));
	return (TOKEN_IVEC4);
 }

";" {
	yTRACE((TOKEN_SEPARATOR));
	return (TOKEN_SEPARATOR);
 }
 
"," {
	yTRACE((TOKEN_SEMI));
	return (TOKEN_SEMI);
 }

"{" {
	yTRACE((TOKEN_SCOPE_START));
	return (TOKEN_SCOPE_START);
 }

"}" {
	yTRACE((TOKEN_SCOPE_END));
	return (TOKEN_SCOPE_END);
 }

"true" {
	yTRACE((TOKEN_TRUE));
	return (TOKEN_TRUE);
 }

"false" {
	yTRACE((TOKEN_FALSE));
	return (TOKEN_FALSE);
 }

"void" {
	yTRACE((TOKEN_VOID));
	return (TOKEN_VOID);
 }

"const" {
	yTRACE((TOKEN_CONST));
	return (TOKEN_CONST);
 }

"else" {
	yTRACE((TOKEN_ELSE));
	return (TOKEN_ELSE);
 }

"+" {
	yTRACE((PLUS));
	return (PLUS);
 }

"-" {
	yTRACE((MINUS));
	return (MINUS);
 }

"*" {
	yTRACE((MULT));
	return (MULT);
 }

"/" {
	yTRACE((DIV));
	return (DIV);
 }

"==" {
	yTRACE((EQUAL));
	return (EQUAL);
 }

"=" {
	yTRACE((ASSIGN));
	return (ASSIGN);
  }

"&&" {
	yTRACE((TOKEN_AND));
	return (TOKEN_AND);
 }

"||" {
	yTRACE((TOKEN_OR));
	return (TOKEN_OR);
 }

"!=" {
	yTRACE((TOKEN_NOT_EQ));
	return (TOKEN_NOT_EQ);
 }

"<=" {
	yTRACE((TOKEN_LTE));
	return (TOKEN_LTE);
 }

"<" {
	yTRACE((TOKEN_LT));
	return (TOKEN_LT);
 }

">=" {
	yTRACE((TOKEN_GTE));
	return (TOKEN_GTE);
 }

">" {
	yTRACE((TOKEN_GT));
	return (TOKEN_GT);
 }

"!" {
	yTRACE((TOKEN_NOT));
	return (TOKEN_NOT);
 }

"^" {
	yTRACE((TOKEN_XOR));
	return (TOKEN_XOR);
 }

"(" {
	yTRACE((TOKEN_OPENRB));
	return (TOKEN_OPENRB);
 }

")" {
	yTRACE((TOKEN_CLOSERB));
	return (TOKEN_CLOSERB);
 }

"[" { 
	yTRACE((TOKEN_OPENSB));
	return (TOKEN_OPENSB);
 }

"]" { 
	yTRACE((TOKEN_CLOSESB));
	return (TOKEN_CLOSESB);
  }

"while"{WS}*"\n"*"(" { 
	if(strstr(yytext,"\n")){
		yyline++;
	}
	yTRACE((TOKEN_WHILE));
	return (TOKEN_WHILE);
  }

"if"{WS}*"\n"*"(" { 
	if(strstr(yytext,"\n")){
		yyline++;
	}
	yTRACE((TOKEN_IF));
	return (TOKEN_IF);
  }

"lit"{WS}*"\n"*"(" { 
	if(strstr(yytext,"\n")){
		yyline++;
	}
	yTRACE((TOKEN_LIT));
	return (TOKEN_LIT);
  }

"dp3"{WS}*"\n"*"(" { 
	if(strstr(yytext,"\n")){
		yyline++;
	}
	yTRACE((TOKEN_DP3));
	return (TOKEN_DP3);
  }

"rsq"{WS}*"\n"*"(" { 
	if(strstr(yytext,"\n")){
		yyline++;
	}
	yTRACE((TOKEN_RSQ));
	return (TOKEN_RSQ);
  }

{SIGN}?{DIGITS}+ {

	if(atoi(yytext)>MAX_INTEGER){
		yERROR("Integer size exceeded");
	}else{
		yTRACE((TOKEN_INT));
		return (TOKEN_INT);
	}
 }
 
{SIGN}?({DIGITS}+\.{DIGITS}*|{DIGITS}*\.{DIGITS}+) {
	yTRACE((TOKEN_FLOAT_DEC));
	return (TOKEN_FLOAT_DEC);
 }

"\n" { 
	yyline++;
	yTRACE((TOKEN_NEWLINE));
	return (TOKEN_NEWLINE);
  }

{IDENTIFIER} {
	if(strlen(yytext)>MAX_IDENTIFIER){
		yERROR("Identifer size exceeded");
	}else{
		yTRACE((TOKEN_IDENTIFIER));
		return (TOKEN_IDENTIFIER);
	}
 }


{WS}* {
	
}

. { yERROR("Unknown token"); }


%%

int checkNum(char c){
  if(c>='0' && c<='9' )
    return 1;
  else
    return 0;
}