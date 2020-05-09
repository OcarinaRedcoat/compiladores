%{
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "node.h"
#include "tabid.h"

int onlyInt(Node *n);
int isInt(Node *n1, Node *n2);
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


%type<n> file prog mod decls decl func qual vars var type lit literais body  
%type<n> bloco instrucoes blocoEnd instrucao elifs elif else expr args lv push
%token DECL DECLS NIL VARS VAR LIT LITERAIS BLOCO INSTRUCAO INSTRUCOES EXPR ARGS LEFTV PARTFUNC INTR ELIFX ELIFELSE
%%

	/* GRAMATICA  */

file   : prog   															{ printNode($1, 0, (char **)yyname); }
		   | mod																	{ printNode($1, 0, (char **)yyname); }
		   ;

prog   : PROGRAM decls START body END					{ $$ = binNode(PROGRAM, $2, $4); }
		   ;

mod    : MODULE decls END											{ $$ = uniNode(MODULE, $2); }
		   ;

/* 0 ou mais declaracoes */
decls  : decl																	{ $$ = binNode(';', nilNode(NIL),$1 ); }
	   	 | decls ';' decl												{ $$ = binNode(';', $1, $3 );}	
       ;


/* 0 ou 1 declaracao */
decl   :																			{ $$ = nilNode(NIL); }
		   | func 																{ $$ = binNode(DECL, nilNode(NIL), $1); }
       | var																	{ $$ = binNode(DECL, nilNode(NIL), $1); }
	     | var ATR literais											{ $$ = binNode(DECL, $1, $3 ); }
	     | CONST var														{ $$ = binNode(DECL, nilNode(NIL),$2 ); }
	     | CONST var ATR literais								{ $$ = binNode(DECL, $2, $4 ); }
       | qual var															{ $$ = binNode(DECL, $1, $2 ); }
	     | qual var ATR literais								{ $$ = binNode(DECL, binNode(DECLS, $1, $2), $4 ); }	
	     | qual CONST var												{ $$ = binNode(DECL, $1, $3 ); }
	     | qual CONST var ATR literais					{ $$ = binNode(DECL, binNode(DECLS, $1, $3), $5 ); }
	   	 ;	


/* funcao */
func   : FUNCTION type	ID DONE 							{ $$ = binNode(FUNCTION,  binNode(PARTFUNC, $2, nilNode(NIL)) ,nilNode(NIL)); IDpop();}
		   | FUNCTION VOID ID DO body							{ $$ = binNode(FUNCTION, nilNode(NIL), $5 ); IDpop();} 
		   | FUNCTION type	ID push vars  DONE					{ $$ = binNode(FUNCTION, binNode(PARTFUNC, $2, $4), $5); IDpop();}
		   | FUNCTION type	ID push vars  DO body			{ $$ = binNode(FUNCTION, binNode(PARTFUNC, $2, $4), binNode(PARTFUNC,$7, $5 )); IDpop();}
		   | FUNCTION VOID	ID push vars  DONE					{ $$ = binNode(FUNCTION, $4, $5);IDpop(); }
		   | FUNCTION VOID	ID push vars  DO body			{ $$ = binNode(FUNCTION, $7, binNode(PARTFUNC,$4, $5 )); IDpop();}
		   | FUNCTION qual type	ID DONE 					{ $$ = binNode(FUNCTION, $2, $3 ); IDpop();}
		   | FUNCTION qual type	ID push vars  DONE			{ $$ = binNode(FUNCTION, binNode(PARTFUNC, $2, $3), binNode(PARTFUNC,$6, $5 )); IDpop();}
		   | FUNCTION qual type	ID push vars  DO body	{ $$ = binNode(FUNCTION, binNode(PARTFUNC, $2, $3), binNode(PARTFUNC,$5, binNode(PARTFUNC, $6, $8))); IDpop();}
		   | FUNCTION qual VOID	ID push vars  DONE			{ $$ = binNode(FUNCTION, $2, binNode(PARTFUNC, $5, $6 )); IDpop();}
		   | FUNCTION qual VOID	ID push vars  DO body	{ $$ = binNode(FUNCTION, binNode(PARTFUNC,$2, $5), binNode(PARTFUNC, $6, $8) ); IDpop();}
			 ; 

push : {IDpush();} {$$ = nilNode(NIL);}
		 ;

qual   : PUBLIC																{ $$ = nilNode(NIL); }
       | FORWARD															{ $$ = nilNode(NIL); }
       ;

/* 1 ou mais variaveis */
vars 	 : var																	{ $$ = binNode(VARS, nilNode(NIL),$1); } /* check  */
	 	 	 | vars ';' var 												{ $$ = binNode(VARS, $1, $3); }
	     ;

/* 1 variavel */
var    : type ID															{ $$ = uniNode(VAR, $1); IDnew($1->value.i, $2, 0); }
	     | type ID '[' INT ']'									{ $$ = uniNode(VAR, $1); checkArray($1); IDnew($1->value.i, $2, 0); }
	     ;

/* tipo */
type   : NUMBER																{ $$ = intNode(NUMBER, 268);}
       | STRING																{ $$ = intNode(STRING, 267);}
       | ARRAY																{ $$ = intNode(ARRAY, 269);}
	     ;



/* 1 literal  */
lit   : INT																		{ $$ = intNode(NUMBER, $1); $$->info = NUMBER;}
	    | CHR																		{ $$ = strNode(CHR, $1); $$->info = NUMBER;}	
	    | STRG																	{ $$ = strNode(STRING, $1); $$->info = STRING;}
	    ; 

literais		: lit															{ $$ = uniNode(LIT, $1);}
						| literais	lit										{ $$ = binNode(LITERAIS, $1, $2);}
						| literais ',' lit								{ $$ = binNode(LITERAIS, $1, $3);}	
						;

body        : bloco														{ $$ = binNode(BLOCO, $1, nilNode(NIL));} 
		        | vars ';' bloco	 								{ $$ = binNode(BLOCO, $1, $3);}
						;


bloco   		: instrucoes blocoEnd							{ $$ = binNode(INSTRUCOES, $1, $2);}
						;

instrucoes  : 																{ $$ = nilNode(NIL);}
						| instrucoes instrucao						{ $$ = binNode(INSTRUCOES, $1, $2);}						
						;					

blocoEnd   : 																	{ $$ = nilNode(NIL);}
					 | REPEAT														{ $$ = nilNode(NIL);}	
					 | STOP															{ $$ = nilNode(NIL);}
					 | RETURN expr 											{ $$ = uniNode(EXPR, $2);}
					 | RETURN														{ $$ = nilNode(NIL);}
					 ;

instrucao  : IF expr THEN bloco  FI     			{ $$ = binNode(INSTRUCAO, $2, $4);}
					 | IF expr THEN bloco elifs FI    	{ $$ = binNode(INSTRUCAO, binNode(INTR,$2, $4), $5);} 
				   | IF expr THEN bloco else FI 			{ $$ = binNode(INSTRUCAO, binNode(INTR,$2, $4), $5);}
				   | IF expr THEN bloco elifs else FI { $$ = binNode(INSTRUCAO, binNode(ELIFELSE,$2, $4), binNode(ELIFELSE,$5, $6));} 
					 | FOR expr UNTIL expr  STEP expr DO bloco DONE	{ $$ = binNode(INSTRUCAO, binNode(FOR,$2, $4), binNode(FOR,$6, $8));}
					 | expr ';'													{ $$ = binNode(INSTRUCAO, $1, nilNode(NIL));}
					 | expr '!'													{ $$ = binNode(INSTRUCAO, $1, nilNode(NIL));}
					 | lv '#' expr ';'									{ $$ = binNode(INSTRUCAO, $3, $1);}
					 ;

/* 0 ou mais elif  */
elifs  		 : elif															{ $$ = binNode(ELIF, nilNode(NIL),$1);}
			 		 | elifs elif												{ $$ = binNode(ELIF, $1, $2);}
			 		 ;

/* 1 elif */
elif   		 : ELIF expr THEN bloco							{ $$ = binNode(ELIFX, $2, $4);}
			     ;

/* 0 ou 1 else  */
else       : ELSE bloco												{ $$ = uniNode(ELSE, $2);}																									
  			   ;

expr 			 : lv																{ $$ = uniNode(LEFTV, $1);}
					 | lv ATR expr											{ $$ = binNode(ATR, $1, $3); }	
					 | lit															{ $$ = uniNode(EXPR, $1); } 
					 | '-' expr %prec UMINUS						{ $$ = uniNode(EXPR, $2);} 
			 		 | '~' expr 												{ $$ = uniNode(EXPR, $2);}	
			 		 | '&' lv %prec UMINUS							{ $$ = uniNode(EXPR, $2); }
					 | expr '+' expr										{ $$ = binNode('+', $1, $3); }	
					 | expr '-' expr										{ $$ = binNode('-', $1, $3);}
					 | expr '*' expr										{ $$ = binNode('*', $1, $3);}
					 | expr '/' expr										{ $$ = binNode('/', $1, $3);}	
					 | expr '%' expr										{ $$ = binNode('%', $1, $3);}
			 		 | expr GE expr											{ $$ = binNode(GE, $1, $3);}
					 | expr LE expr											{ $$ = binNode(LE, $1, $3);}	
					 | expr '<' expr										{ $$ = binNode('<', $1, $3);}	
					 | expr '>' expr										{ $$ = binNode('>', $1, $3);}
					 | expr '^' expr										{ $$ = binNode('^', $1, $3);}
					 | expr '|' expr										{ $$ = binNode('|', $1, $3);}
					 | expr '&' expr										{ $$ = binNode('&', $1, $3);}
					 | expr NE expr											{ $$ = binNode(NE, $1, $3);}	
					 | expr '=' expr										{ $$ = binNode('=', $1, $3);}
					 | '(' expr ')'											{ $$ = uniNode(EXPR, $2);}
					 | '?'															{ $$ = nilNode(NIL);}
					 | ID '(' args ')'									{ $$ = binNode(ARGS, strNode(ID, $1),$3);}
				 	 ; 

args       : expr															{ $$ = binNode(ARGS, nilNode(NIL),$1);}
					 | args ',' expr										{ $$ = binNode(ARGS, $1, $3);}
					 ; 

lv     		 : ID																{ $$ = binNode(ATR, strNode(ID, $1), nilNode(NIL));} 
			 		 | ID '[' expr ']'									{ $$ = binNode(ATR, strNode(ID, $1), $3); }
			 		 ;


%%
int onlyInt(Node *n){
	if (n->info != NUMBER)
		yyerror("onlyInt");
	return NUMBER;
}
int isInt(Node *n1, Node *n2){
	printf("\nnode 1 info: %d\n", n1->info);
	printf("\nnode 2 info: %d\n", n2->info);
	if (n1->info != NUMBER || n2->info != NUMBER)
		yyerror("isInt");
	return NUMBER;
}

int checkArray(Node *n){
		if (n->value.i != ARRAY){
			yyerror("Eis um array que nao e array");
		}
		return ARRAY;
}

char **yynames =
#if YYDEBUG > 0
		 (char**)yyname;
#else
		 0;
#endif
