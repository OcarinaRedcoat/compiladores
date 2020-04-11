%{
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "node.h"
#include "tabid.h"

int yylex();
void evaluate(Node *p);
void yyerror(char *s);
int lbl;
%}

%union {
	int i;			/* integer value                 */
	char *s;		/* symbol name or string literal */
	Node *n;
};

%token <i> INT
%token <s> ID STRING

%token PROGRAM MODULE START END VOID CONST NUMBER ARRAY STRING FUNCTION PUBLIC
%token FOWARD IF THEN ELSE ELIF FI FOR UNTIL STEP DO DONE REPEAT STOP RETURN

%nonassoc IFX
%nonassoc ELSE

%right ATR


%left GE LE NE '>' '<'
%left '+' '-'
%left '*' '/' '%'
%nonassoc UMINUS

%type <n> stmt expr list


%%

	/* GRAMATICA  */

file   : prog
		   | mod
		   ;

/* program */
prog   : PROGRAM decls  START body END 	//: PROGRAM START body END
		   ;

/* module */
mod    : MODULE decls END
		   ;

/* 0 ou mais declaracoes */
decls  : decl
		   | decls ';' decl
	     ;

/* 0 ou 1 declaracao */
decl   : 
		   | func
		   | qual var
		   | qual var ATR lit
		   |  qual CONST var
		   | qual CONST var ATR lit
		   ;	

/* funcao */
func   : FUNCTION qual type	ID DONE 
		   | FUNCTION qual VOID ID DO body
		   | FUNCTION qual type	ID vars  DONE
		   | FUNCTION qual type	ID vars  DO body
		   | FUNCTION qual VOID	ID vars  DONE
		   | FUNCTION qual VOID	ID vars  DO body
		   ;

/* existencia ou nao de qualificador */
qual   : 
		   | PUBLIC
		   | FOWARD
		   ;

/* 1 ou mais variaveis */
vars   : var
		   | vars ';' var 
		   ;

/* 1 variavel */
var    : type ID
		   | type ID '[' INT ']'
		   ;

/* tipo */
type   : NUMBER
		   | STRING
		   | ARRAY
		   ;

/* FIXME */
varc   : var ';'
		   | varc var ';'
		   ;

/* 1 ou mais */
instrs : instr
			 | instrs instr
			 ; 

body   : varc instrs 
		   ;

/* 1 literal  */
lit    : INT
			 | CHT
			 | STR
			 ; 

/* 1 ou mais literais*/
lits   : lit
			 | lits lit
			 ;

/* 1 ou mais literais separados de virgula */
litsc  : lit
			 | litsc ',' lit
			 ;	

/* 1 instrucao */
instr  : IF expr THEN instrs elifs else FI
			 | FOR expr UNTIL expr STEP expr DO instrs DONE
			 | expr ';'
			 | expr '!'
			 | REPEAT
			 | STOP
			 | RETURN
			 | RETURN expr
			 | lv # expr
			 ;

/* 0 ou mais elif  */
elifs  : 
			 | elif
			 | elifs elif
			 ;

/* 1 elif */
elif   : ELIF expr THEN instrs
			 ;

/* 0 ou 1 else  */
else   : 
			 | ELSE instrs
			 ; 

expr   : 
			 ;































%%

char *mklbl(int n) {
  static char buf[20];
  sprintf(buf, "_i%d", n);
  return strdup(buf);
}

char **yynames =
#if YYDEBUG > 0
		 (char**)yyname;
#else
		 0;
#endif
