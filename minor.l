%{ 
#include <stdlib.h> 
#include <string.h> 
/*#include "node.h"*/ 
#include "y.tab.h"
char *dupstr(const char *s);
int yyerror(char *s);
int in; /*in string or chr*/
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



^"program"	  			            												BEGIN ZONE; 		return PROGRAM;
^"module"    			            													BEGIN ZONE;		 	return MODULE;
<ZONE>"start"                 													return START;
<ZONE>^"end"			 	           	 												BEGIN INITIAL;  return END;
<ZONE>"void"                  													return VOID;
<ZONE>"const"                 													return CONST;
<ZONE>"number"                													return NUMBER;
<ZONE>"array"                 													return ARRAY;
<ZONE>"string"               		 												return STRING;
<ZONE>"function"              													return FUNCTION;
<ZONE>"public"                													return PUBLIC;
<ZONE>"foward"                													return FOWARD;
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
<ZONE>"return"                													return RETURN;/*


<ZONE>\'([^\']|\\[nrt'\\]|\\[0-9a-fA-F][0-9a-fA-F]?)\'	ECHO;*/ 

<ZONE>\'																								BEGIN CHAR;
<CHAR>\\n\'																							BEGIN ZONE; return '\n';							
<CHAR>\\r\'																							BEGIN ZONE; return '\r';
<CHAR>\\t\'																							BEGIN ZONE; return '\t';
<CHAR>\\'\'																							BEGIN ZONE; return '\'';
<CHAR>\\\\'																							BEGIN ZONE; return '\\';/*
<CHR>\\[nrt'\\]\'																				printf("'%s", yytext);BEGIN ZONE;*/
<CHAR>\\[0-9a-fA-F][0-9a-fA-F]\'													printf("'%s", yytext);BEGIN ZONE;
<CHAR>[^\\']\'																						BEGIN ZONE; return *yytext;											
<CHAR>.																									BEGIN CHRERROR; yyerror("char not valid");

<CHRERROR>\'																						BEGIN ZONE;
<CHRERROR>.																							;

<ZONE>\"([^\\"]|\\.)\" 	                                yylval.s = malloc(yyleng); *yylval.s = 0; in = 1; REJECT;
<ZONE>\" 			                                         	if(in) BEGIN STR; else {yyerror("unterminated string"); return 0;} 
<STR>\"	 			                                          BEGIN ZONE; return STRING;
<STR>\\n 			                                          strcat(yylval.s, "\n"); 
<STR>\\r 			                                          strcat(yylval.s, "\r"); 
<STR>\\t 			                                     		  strcat(yylval.s, "\t"); 
<STR>\\\" 		                                          strcat(yylval.s, "\""); 
<STR>\\\\			                                          strcat(yylval.s, "\\"); 
<STR>\\[0-9a-fA-F][0-9a-fA-F]? 	                        { char s[2]; s[1] = 0; s[0] = strtol(yytext+1,0,16); strcat(yylval.s, s); }
<STR>\\. 			                                          yyerror("invalid escape sequence in string");     
<STR>[^"]		                                            strcat(yylval.s, yytext); 

<ZONE>[A-Za-z][A-Za-z0-9_]*	  													yylval.s = strdup(yytext); return ID;
<ZONE>[\#\[\]\(\)\;\:\!\,]	  													return *yytext;
<ZONE>[\-\+\*\/\%\^\|\~\&\?\=\<\>]											return *yytext;	
<ZONE>0[0-7]+			            													errno = 0; yylval.i = strtol(yytext+1, 0, 8); if (errno == ERANGE) yyerror("overflow in octal");  return INT;
<ZONE>[0-9]+			            													errno = 0; yylval.i = strtol(yytext, 0, 10); if (errno == ERANGE) yyerror("overflow in octal");   return INT;
<ZONE>0b[01]+			            													errno = 0; yylval.i = strtol(yytext+2, 0, 2); if (errno == ERANGE) yyerror("overflow in octal");  return INT;
<ZONE>0x[0-9a-fA-F]+          													errno = 0; yylval.i = strtol(yytext+2, 0, 16); if (errno == ERANGE) yyerror("overflow in octal"); return INT;

<ZONE>[ \t\n\r]+	            													; /* ignore whitespace */ 
 
<ZONE>.                       													yyerror("Unknown character"); 	 

.|\n								         														;
%% 

int main() {return yylex();}
int yywrap(void) {
  if (YYSTATE == COM) yyerror("unterminated comment");
  return 1;
}
char *getyytext() { return yytext; }
