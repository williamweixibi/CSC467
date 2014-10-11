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
                  printf("Comment");
                  break;
				        }
                c1 = c2;
                c2 = yyinput();
                if (c1 == '\n' && c2 != EOF)
                  yyline++;
              }
            }

"int"{WS}* {
              yTRACE(TOKEN_INT);
            }

"float"{WS}* {
              yTRACE(TOKEN_FLOAT);
            }

"bool"{WS}* {
              yTRACE(TOKEN_BOOL);
            }

"vec2"{WS}* {
            yTRACE(TOKEN_VEC2);
            }

"vec3"{WS}* {
            yTRACE(TOKEN_VEC3);
            }

"vec4"{WS}* {
              yTRACE(TOKEN_VEC4);
            }


"bvec2"{WS}* {
            yTRACE(TOKEN_BVEC2);
            }

"bvec3"{WS}* {
            yTRACE(TOKEN_BVEC3);
            }

"bvec4"{WS}* {
              yTRACE(TOKEN_BVEC4);
            }

"ivec2"{WS}* {
            yTRACE(TOKEN_IVEC2);
            }

"ivec3"{WS}* {
            yTRACE(TOKEN_IVEC3);
            }

"ivec4"{WS}* {
              yTRACE(TOKEN_IVEC4);
            }

";" {
    printf("Semi \n");
}

{IDENTIFIER}     {
          printf("%s\n",yytext);
            }

"+" {
  yTRACE(PLUS);
}

"-" {
  yTRACE(MINUS);
}

"*" {
  yTRACE(MULT);
}

"/" {
  yTRACE(DIV);
}

"=" {
  int c2      = yyinput();
  int curline = yyline;
  if(c2=='='){
    yTRACE(EQUAL);
  }else{
    yTRACE(ASSIGN);
  }
}


"if" {
  yTRACE(TOKEN_IF);
}

"while" {
  yTRACE(TOKEN_WHILE);
}

.           { yERROR("Unknown token"); }

%%

int checkNum(char c){
  if(c>='0' && c<='9' )
    return 1;
  else
    return 0;
}