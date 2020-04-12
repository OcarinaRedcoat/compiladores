%{
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
/*#include "node.h"*/
#include "tabid.h"

extern int yylex();
/*void evaluate(Node *p);*/
void yyerror(char *s);
int lbl;
%}

%union {
	int i;			/* integer value                 */
	char *s;		/* symbol name or string literal */
	/*Node *n;*/
};

%token <i> INT
%token <s> ID STRING CHR

%token PROGRAM MODULE START END VOID CONST NUMBER ARRAY FUNCTION PUBLIC
%token FOWARD IF THEN ELSE ELIF FI FOR UNTIL STEP DO DONE REPEAT STOP RETURN

%nonassoc IFX
%nonassoc ELSE

%right ATR
%left '|' 
%left '&'
%left '~' 
%left NE '=' 
%left '<' '>' GE LE
%left  '+' '-' 
%left '*' '/' '%'
%right '^'
%nonassoc '?' UMINUS  //'&'
%left '(' ')' '[' ']'

%%

	/* GRAMATICA  */

file : prog
		 | mod
		 ;

prog : PROGRAM END
		 ;

mod  : MODULE END
		 ;
%%

char **yynames =
#if YYDEBUG > 0
		 (char**)yyname;
#else
		 0;
#endif
