%{ 
#include <stdlib.h> 
#include <string.h> 
/*#include "node.h"*/ 
/*#include "y.tab.h"*/
char *dupstr(const char *s);
extern void yyerror(const char *msg);
int octal(char *);


%}
%x COM ZONE CHR
%%

<ZONE>"$$".*                  ; /* one line comment*/
<ZONE>"$"                     BEGIN COM;/* multi line commment */

<COM>"$"    			            BEGIN ZONE;
<COM>.|\n   			            ;

<ZONE>"-"                     ECHO;
<ZONE>"+"                     ECHO;
<ZONE>"*"                     ECHO;
<ZONE>"/"                     ECHO;
<ZONE>"%"                     ECHO;
<ZONE>"^"                     ECHO;
<ZONE>":="                    ECHO;
<ZONE>"<"                     ECHO;
<ZONE>">"                     ECHO;
<ZONE>"="                     ECHO;
<ZONE>">="                    ECHO;
<ZONE>"<="                    ECHO;
<ZONE>"~="                    ECHO;
<ZONE>"|"                     ECHO;
<ZONE>"&"                     ECHO;
<ZONE>"~"                     ECHO;
<ZONE>"?"                     ECHO;

<ZONE>"while" 	              ECHO;
<ZONE>"if"			              ECHO;
<ZONE>"else"		              ECHO;
<ZONE>"print" 	              ECHO;
<ZONE>"read"		              ECHO;
"program"	  			            BEGIN ZONE; 		ECHO;
<ZONE>"end"			 	            BEGIN INITIAL;  ECHO;
"module"    			            BEGIN ZONE;		  ECHO;
<ZONE>"start"                 ECHO;
<ZONE>"void"                  ECHO;
<ZONE>"const"                 ECHO;
<ZONE>"number"                ECHO;
<ZONE>"array"                 ECHO;
<ZONE>"string"                ECHO;
<ZONE>"function"              ECHO;
<ZONE>"public"                ECHO;
<ZONE>"foward"                ECHO;
<ZONE>"then"                  ECHO;
<ZONE>"elif"                  ECHO;
<ZONE>"fi"                    ECHO;
<ZONE>"for"                   ECHO;
<ZONE>"until"                 ECHO;
<ZONE>"step"                  ECHO;
<ZONE>"do"                    ECHO;
<ZONE>"done"                  ECHO;
<ZONE>"repeat"                ECHO;
<ZONE>"stop"                  ECHO;
<ZONE>"return"                ECHO;


<ZONE>[A-Za-z][A-Za-z0-9_]*	  ECHO;


<ZONE>[\#\[\]\(\)\;\:\!\,]	  ECHO;

<CHR>\'                       BEGIN ZONE
<CHR>\\'                      
<CHR>\\n
<CHR>\r
<CHR>\\t
<CHR>\\\
<CHR>\\[0-9a-fA-F][0-9a-fA-F]? {}

<ZONE>0[0-7]+			            printf("%d", octal(yytext));
<ZONE>[0-9]+			            printf("%ld", strtol(yytext, 0, 10)); 
<ZONE>0b[01]+			            printf("%ld", strtol(yytext+2, 0, 2));
<ZONE>0x[0-9a-fA-F]+          printf("%ld", strtol(yytext+2,0, 16));



 
<ZONE>[ \t\n\r]+	            ECHO; /* ignore whitespace */ 
 
<ZONE>.                       ; 
.|\n								          ;//	yyerror("Unknown character"); 
%% 

int octal(char *s)  
{
  puts("------");
  int i, a = 0, b = 0;

  for (i = 0; i < strlen(s); i++) {
    if (s[i] < '0' || s[i] > '9') break;
    b = b * 8 + s[i] - '0';
    if (b < a) {
      printf("octal overflow");
      break;
    }
    a = b;
  }
  return a;
}


int main() {return yylex();}
int yywrap() {return 1;}

char *getyytext() { return yytext; }
