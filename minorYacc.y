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
%token <s> ID STRG CHR

%token PROGRAM MODULE START END VOID CONST STRING NUMBER ARRAY FUNCTION PUBLIC
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

prog   : PROGRAM decls START END
		   ;

mod    : MODULE decls END
		   ;

/* 0 ou mais declaracoes */
decls  : decl
	   	 | decls ';' decl
       ;


/* 0 ou 1 declaracao */
decl   :
		   | func 
       | var
	     | var ATR literais
	     | CONST var
	     | CONST var ATR literais
       | qual var
	     | qual var ATR literais
	     | qual CONST var
	     | qual CONST var ATR literais
	   	 ;	


/* funcao */
func   : FUNCTION type	ID DONE 
		   | FUNCTION VOID ID DO body 
		   | FUNCTION type	ID vars  DONE
		   | FUNCTION type	ID vars  DO 
		   | FUNCTION VOID	ID vars  DONE
		   | FUNCTION VOID	ID vars  DO 
		   | FUNCTION qual type	ID DONE 
		   | FUNCTION qual VOID ID DO 
		   | FUNCTION qual type	ID vars  DONE
		   | FUNCTION qual type	ID vars  DO
		   | FUNCTION qual VOID	ID vars  DONE
		   | FUNCTION qual VOID	ID vars  DO 
			 ; 




qual   : PUBLIC
       | FOWARD
       ;

/* 1 ou mais variaveis */
vars 	 : var
	 	 	 | vars ';' var 
	     ;

/* 1 variavel */
var    : type ID
       | ARRAY ID
	     | ARRAY ID '[' INT ']'
	     ;

/* tipo */
type   : NUMBER
       | STRING
	     ;



/* 1 literal  */
lit   : INT
	    | CHR
	    | STRING
	    ; 

literais  	: lit
         		| literais ',' lit 
         		| literais lit
          	;

body        : vars ';'
            | instrucoes
		        | vars ';' instrucoes
	          ;

instrucoes : instrucao
					 | instrucoes instrucao
           ; 

instrucao  : IF expr  THEN instrucoes elif else
				   | FOR expr UNTIL expr  STEP expr DO instrucoes DONE
					 | expr ';'
					 | expr '!'
					 | REPEAT
					 | STOP
					 | RETURN 
					 | RETURN  expr 
					 | lv '#' expr
					 ;

/* 0 ou mais elif  */
elifs  		 : elif
			 		 | elifs elif
			 		 ;

/* 1 elif */
elif   		 : ELIF THEN instrucoes
			     ;

/* 0 ou 1 else  */
else       : ELSE instrucoes
  			   ;

throng     : ARRAY lv
					 | ARRAY lv ATR literais 
					 ;

expr 			 : lv
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

args       : expr
					 | args ',' expr
					 ; 

lv     		 : ID
			 		 | ID '[' ']'
			 		 ;


%%

char **yynames =
#if YYDEBUG > 0
		 (char**)yyname;
#else
		 0;
#endif
