%{
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
/*#include "node.h"*/
#include "tabid.h"

int yylex();
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

prog : PROGRAM decls START END
		 ;

mod  : MODULE decls END
		 ;
/* 0 ou mais declaracoes */
decls  : decl
	   | decls ';' decl
       ;


/* 0 ou 1 declaracao */
decl   : 
       | var
	   | var ATR literais
	   | CONST var
	   | CONST var ATR literais
       | qual var
	   | qual var ATR literais
	   | qual CONST var
	   | qual CONST var ATR literais
	   ;	

qual : PUBLIC
     | FOWARD
     ;

/* 1 ou mais variaveis */
vars : var
	 | vars ';' var 
	 ;

/* 1 variavel */
var  : type ID
     | ARRAY ID
	 | ARRAY ID '[' INT ']'
	 ;

/* tipo */
type  : NUMBER
	  | STRING
	  ;



/* 1 literal  */
lit  : INT
	 | CHR
	 | STRING
	 ; 

literais : lit
         | literais ',' lit 
         | literais lit
         ;
/*literais : lit
         | litVir 
         | litSVir
         ;


litVir : lit 
       | litVir ','  lit
       ;

litSVir: lit
       | litSVir lit
       ;
*/

%%

char **yynames =
#if YYDEBUG > 0
		 (char**)yyname;
#else
		 0;
#endif
