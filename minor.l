%{ 
#include <stdlib.h> 
#include <string.h> 
/*#include "node.h"*/ 
/*#include "y.tab.h"*/
char *dupstr(const char *s);
int yyerror(char *s);
int octal(char *);


%}
%x COM ZONE STR
%%

<ZONE>"$$".*                  ;/* one line comment*/
<ZONE>"$"                     BEGIN COM;/* multi line commment */

<COM>"$"    			            BEGIN ZONE;
<COM>.|\n   			            ;

<ZONE>"-"                     ECHO;
<ZONE>"+"                     													ECHO;
<ZONE>"*"                     ECHO;
<ZONE>"/"                     ECHO;
<ZONE>"%"                     ECHO;
<ZONE>"^"                     ECHO;
<ZONE>":="                    ECHO;
<ZONE>"<"                     ECHO;
<ZONE>">"                     ECHO;
<ZONE>"="                     													ECHO;
<ZONE>">="                    													ECHO;
<ZONE>"<="                    													ECHO;
<ZONE>"~="                    													ECHO;
<ZONE>"|"                     													ECHO;
<ZONE>"&"                     													ECHO;
<ZONE>"~"                     													ECHO;
<ZONE>"?"                     													ECHO;

<ZONE>"while" 	              													ECHO;
<ZONE>"if"			              													ECHO;
<ZONE>"else"		              													ECHO;
<ZONE>"print" 	              													ECHO;
<ZONE>"read"		              													ECHO;
"program"	  			            													BEGIN ZONE; 		ECHO;
<ZONE>"end"			 	           	 													BEGIN INITIAL;  ECHO;
"module"    			            													BEGIN ZONE;		  ECHO;
<ZONE>"start"                 													ECHO;
<ZONE>"void"                  													ECHO;
<ZONE>"const"                 													ECHO;
<ZONE>"number"                													ECHO;
<ZONE>"array"                 													ECHO;
<ZONE>"string"               		 												ECHO;
<ZONE>"function"              													ECHO;
<ZONE>"public"                													ECHO;
<ZONE>"foward"                													ECHO;
<ZONE>"then"                 	 													ECHO;
<ZONE>"elif"                  													ECHO;
<ZONE>"fi"                    													ECHO;
<ZONE>"for"                   													ECHO;
<ZONE>"until"                 													ECHO;
<ZONE>"step"                  													ECHO;
<ZONE>"do"                    													ECHO;
<ZONE>"done"                  													ECHO;
<ZONE>"repeat"                													ECHO;
<ZONE>"stop"                  													ECHO;
<ZONE>"return"                													ECHO;/*

<ZONE>\'([^\\']|\\[\\nrt']|\\[0-9a-fA-F][0-9a-fA-F]?)\'	ECHO;*/
<ZONE>\"([^\\"]|\\.)\"																	REJECT;//yylval.s = malloc(yyleng); *yylval.s = 0; REJECT;
<ZONE>\"																								ECHO; BEGIN STR; 
<STR>\"																									ECHO; BEGIN ZONE; // return STRING;
<STR>\\n																								ECHO; //strcat(yylval.s, "\n");
<STR>\\r																								ECHO;
<STR>\\t																								ECHO; //strcat(yylval.s, "\t");
<STR>\\[\\\"]																							ECHO; //strcat(yylval.s, yytext+1);
<STR>\\[0-9a-fA-F][0-9a-fA-F]?													ECHO;
<STR>\\.																								; //yyerror("invalid escape sequence in string");
<STR>.|\n																								ECHO; //strcat(yylval.s, yytext);

<ZONE>[A-Za-z][A-Za-z0-9_]*	  													ECHO;
<ZONE>[\#\[\]\(\)\;\:\!\,]	  													ECHO;


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
