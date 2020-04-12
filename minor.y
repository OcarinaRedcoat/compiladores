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
		   | qual var ATR litr
		   | qual CONST var
		   | qual CONST var ATR litr
		   ;	

/* funcao */
func   : FUNCTION type	ID DONE 
		   | FUNCTION VOID ID DO body
		   | FUNCTION type	ID vars  DONE
		   | FUNCTION type	ID vars  DO body
		   | FUNCTION VOID	ID vars  DONE
		   | FUNCTION VOID	ID vars  DO body
		   | FUNCTION qual type	ID DONE 
		   | FUNCTION qual VOID ID DO body
		   | FUNCTION qual type	ID vars  DONE
		   | FUNCTION qual type	ID vars  DO body
		   | FUNCTION qual VOID	ID vars  DONE
		   | FUNCTION qual VOID	ID vars  DO body
			 ; 

/* existencia ou nao de qualificador */
qual   : PUBLIC
		   | FOWARD
		   ;

/* 1 ou mais variaveis */
vars   : var
		   | vars ';' var 
		   ;

/* 1 variavel */
var    : type ID
		   | ARRAY ID '[' INT ']'
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

body   : 
			 | varc
			 | instrs
			 | varc instrs 
		   ;

/* 1 literal  */
lit    : INT
			 | CHR
			 | STRING
			 ; 

litr   : lits
			 | litsc
			 ;

/* 0 ou mais literais*/
lits   : lit
			 | lits lit
			 ;

/* 1 ou mais literais separados de virgula */
litsc  : lit
			 | litsc ',' lit
			 ;	

/* 1 instrucao */
instr  : 
			 | IF expr THEN instrs elifs else FI
			 | FOR expr UNTIL expr STEP expr DO instrs DONE
			 | expr ';'
			 | expr '!'
			 | REPEAT
			 | STOP
			 | RETURN
			 | RETURN expr
			 | lv '#' expr ';'
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

throng : ARRAY lv
			 | ARRAY lv ATR litsc 
			 ;

expr   : lv
			 | lv ATR expr
			 | INT
			 | STRING
			 | throng
			 | CHR
			 | '-' expr %prec UMINUS
			 | '~' expr %prec UMINUS
			 | '&' lv %prec UMINUS
			 | '!' expr %prec UMINUS
			 | expr '+' expr
			 | expr '-' expr
			 | expr '*' expr
			 | expr '%' expr
			 | expr GE expr
			 | expr LE expr
			 | expr '<' expr
			 | expr '>' expr
			 | expr '^' expr
			 | expr '|' expr
			 | expr '&' expr
			 | expr NE expr
			 | expr '=' expr
			 | '(' expr ')'
			 | '?' expr
			 | ID '(' args ')'
			 | ID '(' ')'
			 ;

args   : expr
			 | args ',' expr
		   ; 

lv     : ID
			 | ID '[' expr ']'
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
