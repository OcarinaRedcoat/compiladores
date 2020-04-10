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

%start FILE

%token <i> INT
%token <s> ID STRING

%token PROGRAM MODULE START END VOID CONST NUMBER ARRAY STRING FUNCTION PUBLIC
%token FOWARD IF THEN ELSE ELIF FI FOR UNTIL STEP DO DONE REPEAT STOP RETURN

%nonassoc IFX
%nonassoc ELSE

%right ATR


%left GE LE EQ NE '>' '<'
%left '+' '-'
%left '*' '/' '%'
%nonassoc UMINUS

%type <n> stmt expr list


%%

	/* GRAMATICA  */

file : prog
		 | mod
		 ;


prog : PROGRAM START body END
		 | PROGRAM decl START body END //FIXME  

mod  : MODULE decl END
		 ;

decl : func
		 | qual var
		 | qual var ATR lit
		 | qual CONST var ATR lit
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
