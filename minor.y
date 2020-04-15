%{
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "node.h"
#include "tabid.h"

int yylex();
/*void evaluate(Node *p);*/
void yyerror(char *s);
int lbl;
%}

%union {
	int i;			/* integer value                 */
	char *s;		/* symbol name or string literal */
 	Node *n;
};

%token <i> INT
%token <s> ID STRG CHR

%token PROGRAM MODULE START END VOID CONST STRING NUMBER ARRAY FUNCTION PUBLIC
%token FORWARD IF THEN ELSE ELIF FI FOR UNTIL STEP DO DONE REPEAT STOP RETURN

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


%type<n> prog mod decls decl func qual vars var type lit literais body  
%type<n> bloco instrucoes blocoEnd instrucao elifs elif else expr args lv
%token DECL DECLS NIL VARS VAR LIT LITERAIS BLOCO INSTRUCAO INSTRUCOES EXPR ARGS
%%

	/* GRAMATICA  */

file   : prog   															{ printNode($1, 0, (char **)yyname); }
		   | mod																	{ printNode($1, 0, (char **)yyname); }
		   ;

prog   : PROGRAM decls START body END					{ $$ = biNode(PROGRAM, $2, $4); }
		   ;

mod    : MODULE decls END											{ $$ = uniNode(MODULE, $2); }
		   ;

/* 0 ou mais declaracoes */
decls  : decl																	{ $$ = uniNode(DECL, $1 ); }
	   	 | decls ';' decl												{ $$ = biNode(DECLS, $1, $3 );}	
       ;


/* 0 ou 1 declaracao */
decl   :																			{ $$ = nilNode(NIL); }
		   | func 																{ $$ = uniNode(DECL, $1); }
       | var																	{ $$ = uniNode(DECL, $1); }
	     | var ATR literais											{ $$ = biNode(DECL, $1, $3 ); }
	     | CONST var														{ $$ = uniNode(DECL, $2 ); }
	     | CONST var ATR literais								{ $$ = biNode(DECL, $2, $4 ); }
       | qual var															{ $$ = biNode(DECL, $1, $2 ); }
	     | qual var ATR literais								{ $$ = triNode(DECL, $1, $2, $4 ); }	
	     | qual CONST var												{ $$ = biNode(DECL, $1, $3 ); }
	     | qual CONST var ATR literais					{ $$ = triNode(DECL, $1, $3, $5 ); }
	   	 ;	


/* funcao */
func   : FUNCTION type	ID DONE 							{ $$ = uniNode(FUNCTION, $2); }
		   | FUNCTION VOID ID DO body							{ $$ = uniNode(FUNCTION, $5 ); } 
		   | FUNCTION type	ID vars  DONE					{ $$ = biNode(FUNCTION, $2, $4 ); }
		   | FUNCTION type	ID vars  DO body			{ $$ = triNode(FUNCTION, $2, $4, $6 ); } 
		   | FUNCTION VOID	ID vars  DONE					{ $$ = uniNode(FUNCTION, $4 ); }
		   | FUNCTION VOID	ID vars  DO body			{ $$ = biNode(FUNCTION, $4, $6 ); }
		   | FUNCTION qual type	ID DONE 					{ $$ = biNode(FUNCTION, $2, $3 ); }
		   | FUNCTION qual VOID ID DO body				{ $$ = biNode(FUNCTION, $2, $6 ); }
		   | FUNCTION qual type	ID vars  DONE			{ $$ = triNode(FUNCTION, $2, $3, $5 ); }
		   | FUNCTION qual type	ID vars  DO body	{ $$ = quadNode(FUNCTION, $2, $3, $5, $7 ); }
		   | FUNCTION qual VOID	ID vars  DONE			{ $$ = biNode(FUNCTION, $2, $5 ); }
		   | FUNCTION qual VOID	ID vars  DO body	{ $$ = triNode(FUNCTION, $2, $5, $7 ); }
			 ; 




qual   : PUBLIC																{ $$ = nilNode(NIL); }
       | FORWARD															{ $$ = nilNode(NIL); }
       ;

/* 1 ou mais variaveis */
vars 	 : var																	{ $$ = uniNode(VARS, $1); }
	 	 	 | vars ';' var 												{ $$ = biNode(VARS, $1, $3); }
	     ;

/* 1 variavel */
var    : type ID															{ $$ = uniNode(VAR, $1); }
	     | type ID '[' INT ']'									{ $$ = uniNode(VAR, $1); }
	     ;

/* tipo */
type   : NUMBER																{ $$ = nilNode(NIL);}
       | STRING																{ $$ = nilNode(NIL);}
       | ARRAY																{ $$ = nilNode(NIL);}
	     ;



/* 1 literal  */
lit   : INT																		{ $$ = nilNode(NIL);}
	    | CHR																		{ $$ = nilNode(NIL);}	
	    | STRG																	{ $$ = nilNode(NIL);}
	    ; 

literais		: lit															{ $$ = uniNode(LIT, $1);}
						| literais	lit										{ $$ = biNode(LITERAIS, $1, $2);}
						| literais ',' lit								{ $$ = biNode(LITERAIS, $1, $3);}	
						;

body        : bloco														{ $$ = uniNode(BLOCO, $1);} 
		        | vars ';' bloco	 								{ $$ = biNode(BLOCO, $1, $3);}
						;


bloco   		: instrucoes blocoEnd							{ $$ = biNode(INSTRUCOES, $1, $2);}
						;

instrucoes  : 																{ $$ = nilNode(NIL);}
						| instrucoes instrucao						{ $$ = biNode(INSTRUCOES, $1, $2);}						
						;					

blocoEnd   : 																	{ $$ = nilNode(NIL);}
					 | REPEAT														{ $$ = nilNode(NIL);}	
					 | STOP															{ $$ = nilNode(NIL);}
					 | RETURN expr 											{ $$ = uniNode(EXPR, $2);}
					 | RETURN														{ $$ = nilNode(NIL);}
					 ;

instrucao  : IF expr THEN bloco  FI     			{ $$ = biNode(INSTRUCAO, $2, $4);}
					 | IF expr THEN bloco elifs FI    	{ $$ = triNode(INSTRUCAO, $2, $4, $5);} 
				   | IF expr THEN bloco else FI 			{ $$ = triNode(INSTRUCAO, $2, $4, $5);}
				   | IF expr THEN bloco elifs else FI { $$ = quadNode(INSTRUCAO, $2, $4, $5, $6);} 
					 | FOR expr UNTIL expr  STEP expr DO bloco DONE	{ $$ = quadNode(INSTRUCAO, $2, $4, $6, $8);}
					 | expr ';'													{ $$ = uniNode(INSTRUCAO, $1);}
					 | expr '!'													{ $$ = uniNode(INSTRUCAO, $1);}
					 | lv '#' expr ';'									{ $$ = biNode(INSTRUCAO, $1, $3);}
					 ;

/* 0 ou mais elif  */
elifs  		 : elif															{ $$ = uniNode(ELIF, $1);}
			 		 | elifs elif												{ $$ = biNode(ELIF, $1, $2);}
			 		 ;

/* 1 elif */
elif   		 : ELIF expr THEN bloco							{ $$ = biNode(ELIF, $2, $4);}
			     ;

/* 0 ou 1 else  */
else       : ELSE bloco												{ $$ = uniNode(ELSE, $2);}																									
  			   ;

expr 			 : lv																{ $$ = uniNode(EXPR	, $1);}
					 | lv ATR expr											{ $$ = biNode(EXPR, $1, $3);}	
					 | '-' expr %prec UMINUS						{ $$ = uniNode(EXPR, $2);} 
			 		 | '~' expr %prec UMINUS						{ $$ = uniNode(EXPR, $2);}	
			 		 | '&' lv %prec UMINUS							{ $$ = uniNode(EXPR, $2);}
					 | expr '+' expr										{ $$ = biNode(EXPR, $1, $3);}	
					 | expr '-' expr										{ $$ = biNode(EXPR, $1, $3);}
					 | expr '*' expr										{ $$ = biNode(EXPR, $1, $3);}
					 | expr '/' expr										{ $$ = biNode(EXPR, $1, $3);}	
					 | expr '%' expr										{ $$ = biNode(EXPR, $1, $3);}
			 		 | expr GE expr											{ $$ = biNode(EXPR, $1, $3);}
					 | expr LE expr											{ $$ = biNode(EXPR, $1, $3);}	
					 | expr '<' expr										{ $$ = biNode(EXPR, $1, $3);}	
					 | expr '>' expr										{ $$ = biNode(EXPR, $1, $3);}
					 | expr '^' expr										{ $$ = biNode(EXPR, $1, $3);}
					 | expr '|' expr										{ $$ = biNode(EXPR, $1, $3);}
					 | expr '&' expr										{ $$ = biNode(EXPR, $1, $3);}
					 | expr NE expr											{ $$ = biNode(EXPR, $1, $3);}	
					 | expr '=' expr										{ $$ = biNode(EXPR, $1, $3);}
					 | '(' expr ')'											{ $$ = uniNode(EXPR, $2);}
					 | '?'															{ $$ = nilNode(NIL);}
					 | ID '(' args ')'									{ $$ = uniNode(EXPR, $3);}
				 	 ; 

args       : expr															{ $$ = uniNode(ARGS, $1);}
					 | args ',' expr										{ $$ = biNode(ARGS, $1, $3);}
					 ; 

lv     		 : ID																{ $$ = nilNode(NIL);} 
			 		 | ID '[' expr ']'									{ $$ = nilNode(NIL);}
			 		 ;


%%

char **yynames =
#if YYDEBUG > 0
		 (char**)yyname;
#else
		 0;
#endif
