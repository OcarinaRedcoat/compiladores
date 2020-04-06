%{ 
#include <stdlib.h> 
#include <string.h> 
#include "node.h" 
#include "y.tab.h" 
char *dupstr(const char *s);
extern void yyerror(const char *msg);
void yyerror(char *s);
int octal(char *);


%}
%x COM ZONE
%%

<ZONE>"$$".*      ; /* one line comment*/
<ZONE> "$"        BEGIN COM;/* multi line commment */

<COM>.|\n   			;
<COM>"$"    			BEGIN INITIAL;




<ZONE>">="        return GE; 
<ZONE>"<="			  return LE; 
<ZONE>"=="			  return EQ; 
<ZONE>"!="			  return NE; 
<ZONE>"while" 	  return WHILE;
<ZONE>"if"			  return IF; 
<ZONE>"else"		  return ELSE; 
<ZONE>"print" 	  return PRINT;
<ZONE>"read"		  return READ; 
"program"	  			BEGIN ZONE; 		return PROGRAM; 
<ZONE>"end"			 	BEGIN INITIAL;  return END; 
"module"    			BEGIN ZONE;		  return MODULE;
<ZONE>"start"     return START;
<ZONE>"void"      return VOID;
<ZONE>"const"     return CONST;
<ZONE>"number"    return NUMBER;
<ZONE>"array"     return ARRAY;
<ZONE>"string"    return STRING;
<ZONE>"function"  return FUNCTION;
<ZONE>"public"    return PUBLIC;
<ZONE>"foward"    return FOWARD;
<ZONE>"then"      return THEN;
<ZONE>"elif"      return ELIF;
<ZONE>"fi"        return FI;
<ZONE>"for"       return FOR;
<ZONE>"until"     return UNTIL;
<ZONE>"step"      return STEP;
<ZONE>"do"        return DO;
<ZONE>"done"      return DONE;
<ZONE>"repeat"    return REPEAT;
<ZONE>"stop"      return STOP;
<ZONE>"return"    return RETURN;


<ZONE>[A-Za-z][A-Za-z0-9_]*	{ yylval.s = dupstr(yytext); return VARIABLE; } 
<ZONE>\'([^']|\\())\'		{ yytext[yyleng-1] = 0; yylval.s = dupstr(yytext+1); return CHAR; }
<ZONE>[-()<>=+*/%;{}.]	return *yytext; 


<ZONE>0[0-9]+			; yylval.i = octal(yytext); return INT; //FIXME ver a expressão regular
<ZONE>[0-9]+			; errno = 0; yylval.i = strtol(yytext, 0, 10); if (errno == ERANGE) yyerror("overflow in decimal constant"); return INT;
<ZONE>0b[01]+			; errno = 0; yylval.i = strtol(yytext+2, 0, 2); if (errno == ERANGE) yyerror("overflow in binary constant"); return INT;
<ZONE>0x[0-9a-fA-F]+ yylval.i = strtol(yytext+2,0, 16);



 
<ZONE>[ \t\n\r]+		; /* ignore whitespace */ 
 
.|\n								;//	yyerror("Unknown character"); 
%% 

int octal(char *s)
{
  int i, a = 0, b = 0;

  for (i = 0; i < strlen(s); i++) {
    if (s[i] < '0' || s[i] > '9') break;
    b = b * 8 + s[i] - '0';
    if (b < a) {
      yyerror("octal overflow");
      break;
    }
    a = b;
  }
  return a;
}







int yywrap(void) { return 1; } 
char *getyytext() { return yytext; }
