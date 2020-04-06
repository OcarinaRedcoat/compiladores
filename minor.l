%{ 
#include <stdlib.h> 
#include <string.h> 
/*#include "node.h"*/ 
/*#include "y.tab.h"*/
char *dupstr(const char *s);
/*extern void yyerror(const char *msg);*/
void yyerror(char *s);
int octal(char *);


%}
%x COM ZONE
%%

<ZONE>"$$".*      ; /* one line comment*/
<ZONE>"$"         BEGIN COM;/* multi line commment */

<COM>"$"    			BEGIN ZONE;
<COM>.|\n   			;




<ZONE>">="        printf("GE"); 
<ZONE>"<="			  printf("LE"); 
<ZONE>"=="			  printf("EQ"); 
<ZONE>"!="			  printf("NE"); 
<ZONE>"while" 	  printf("WHILE");
<ZONE>"if"			  printf("IF"); 
<ZONE>"else"		  printf("ELSE"); 
<ZONE>"print" 	  printf("PRINT");
<ZONE>"read"		  printf("READ"); 
"program"	  			BEGIN ZONE; 		printf("PROGRAM"); 
<ZONE>"end"			 	BEGIN INITIAL;  printf("END"); 
"module"    			BEGIN ZONE;		  printf("MODULE");
<ZONE>"start"     printf("START");
<ZONE>"void"      printf("VOID");
<ZONE>"const"     printf("CONST");
<ZONE>"number"    printf("NUMBER");
<ZONE>"array"     printf("ARRAY");
<ZONE>"string"    printf("STRING");
<ZONE>"function"  printf("FUNCTION");
<ZONE>"public"    printf("PUBLIC");
<ZONE>"foward"    printf("FOWARD");
<ZONE>"then"      printf("THEN");
<ZONE>"elif"      printf("ELIF");
<ZONE>"fi"        printf("FI");
<ZONE>"for"       printf("FOR");
<ZONE>"until"     printf("UNTIL");
<ZONE>"step"      printf("STEP");
<ZONE>"do"        printf("DO");
<ZONE>"done"      printf("DONE");
<ZONE>"repeat"    printf("REPEAT");
<ZONE>"stop"      printf("STOP");
<ZONE>"return"    printf("RETURN");


<ZONE>[A-Za-z][A-Za-z0-9_]*	{ dupstr(yytext); printf("VARIABLE"); } 
<ZONE>\'([^']|[\\n\\r\\t\\'.])\' { yytext[yyleng-1] = 0; dupstr(yytext+1); printf("CHAR"); }
<ZONE>[-()<>=+*/%;{}.]	printf("yytext"); 


<ZONE>0[0-7]+			; octal(yytext); printf("INT"); //FIXME ver a expressão regular
<ZONE>[0-9]+			; errno = 0; strtol(yytext, 0, 10); if (errno == ERANGE) yyerror("overflow in decimal constant"); printf("INT");
<ZONE>0b[01]+			; errno = 0; strtol(yytext+2, 0, 2); if (errno == ERANGE) yyerror("overflow in binary constant"); printf("INT");
<ZONE>0x[0-9a-fA-F]+ strtol(yytext+2,0, 16);



 
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
