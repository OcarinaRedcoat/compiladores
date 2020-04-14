%{ 
#include <stdlib.h> 
#include <string.h> 
/*#include "node.h"*/ 
#include "y.tab.h"
/*char *dupstr(const char *s);*/
extern void yyerror(char *s);
void checkDup(char *text);
void checkHex(char *text);
int in; 
int inCHR = 0;  /*in string or chr*/
%}
%x COM ZONE STR CHAR CHRERROR
%%

<ZONE>"$$".*                  													;/* one line comment*/
<ZONE>"$"                     													BEGIN COM;/* multi line commment */

<COM>"$"    			            													BEGIN ZONE;
<COM>.|\n   			            													;

<ZONE>":="                   														return ATR;	
<ZONE>">="                    													return GE;
<ZONE>"<="                    													return LE;
<ZONE>"~="                    													return NE;



^"program"	  			            												{ BEGIN ZONE; 		return PROGRAM;}
^"module"    			            													{ BEGIN ZONE;		 	return MODULE;}
<ZONE>"start"                 													return START;
<ZONE>^"end"			 	           	 												{ BEGIN INITIAL;  return END; }
<ZONE>"void"                  													return VOID;
<ZONE>"const"                 													return CONST;
<ZONE>"number"                													return NUMBER;
<ZONE>"array"                 													return ARRAY;
<ZONE>"string"               		 												return STRING;
<ZONE>"function"              													return FUNCTION;
<ZONE>"public"                													return PUBLIC;
<ZONE>"forward"                													return FORWARD;
<ZONE>"if"			              													return IF;
<ZONE>"then"                 	 													return THEN;
<ZONE>"else"		              													return ELSE;
<ZONE>"elif"                  													return ELIF;
<ZONE>"fi"                    													return FI;
<ZONE>"for"                   													return FOR;
<ZONE>"until"                 													return UNTIL;
<ZONE>"step"                  													return STEP;
<ZONE>"do"                    													return DO;
<ZONE>"done"                  													return DONE;
<ZONE>"repeat"                													return REPEAT;
<ZONE>"stop"                  													return STOP;
<ZONE>"return"                													return RETURN;

<ZONE>[ \t\n\r]+	            													; /* ignore whitespace */ 


<ZONE>\' 																								{BEGIN CHAR; inCHR=1;}
<CHAR>\'																								{BEGIN ZONE; return CHR;} 
<CHAR>[^\\']																						{if (inCHR){  strcat(yylval.s, yytext); inCHR = 0; }else {yyerror("char error");}}
<CHAR>\\\'																							{if (inCHR){ strcat(yylval.s, "\'"); inCHR = 0; }else {yyerror("char error");}}
<CHAR>\\n																								{if (inCHR){ strcat(yylval.s, "\n"); inCHR = 0; }else {yyerror("char error");}}
<CHAR>\\r																								{if (inCHR){ strcat(yylval.s, "\r"); inCHR = 0; }else {yyerror("char error");}}
<CHAR>\\t																								{if (inCHR){ strcat(yylval.s, "\t"); inCHR = 0; }else {yyerror("char error");}}
<CHAR>\\[0-9a-fA-F][0-9a-fA-F]?													{if (inCHR){ char s[2]; s[1] = 0; s[0] = strtol(yytext+1,0,16); strcat(yylval.s, s); inCHR = 0; } else {yyerror("char error");}}
 
<ZONE>\"([^"\\]|\\(.|\n))*\"	                                {yylval.s = malloc(yyleng); *yylval.s = 0; in = 1; REJECT;}
<ZONE>\" 			                                         	{if(in) BEGIN STR; else {yyerror("unterminated string"); return 0;}} 
<STR>\"	 			                                          {BEGIN ZONE; return STRG;}
<STR>\\n 			                                          strcat(yylval.s, "\n"); 
<STR>\\r 			                                          strcat(yylval.s, "\r"); 
<STR>\\t 			                                     		  strcat(yylval.s, "\t"); 
<STR>\\\" 		                                          strcat(yylval.s, "\""); 
<STR>\\\\			                                          strcat(yylval.s, "\\"); 
<STR>\\[0-9a-fA-F][0-9a-fA-F]? 	                        { char s[2]; s[1] = 0; s[0] = strtol(yytext+1,0,16); strcat(yylval.s, s); }
<STR>\\. 			                                          yyerror("invalid escape sequence in string");     
<STR>[^"]		                                            strcat(yylval.s, yytext); 

<ZONE>[A-Za-z][A-Za-z0-9_]*	  													{yylval.s = strdup(yytext); return ID;}
<ZONE>[\#\[\]\(\)\;\:\!\,]	  													return *yytext;
<ZONE>[\-\+\*\/\%\^\|\~\&\?\=\<\>]											return *yytext;
<ZONE>0[0-7]+			            													{errno = 0; yylval.i = strtol(yytext+1, 0, 8);  if (errno == ERANGE) yyerror("overflow in octal");  return INT;}
<ZONE>[0-9]+			            													{errno = 0; yylval.i = strtol(yytext, 0, 10);   if (errno == ERANGE) yyerror("overflow in octal");  return INT;}
<ZONE>0b[01]+			            													{errno = 0; yylval.i = strtol(yytext+2, 0, 2);  if (errno == ERANGE) yyerror("overflow in octal");  return INT;}
<ZONE>0x[0-9a-fA-F]+          													{errno = 0; yylval.i = strtol(yytext+2, 0, 16); if (errno == ERANGE) yyerror("overflow in octal");  return INT;}

 
<ZONE>.                       													yyerror("Unknown character"); 	 

.|\n								         														;
%%

int yywrap(void) {
  return 1;
}
char *getyytext() { return yytext; }
