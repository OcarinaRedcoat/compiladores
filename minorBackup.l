%{ 
#include <stdlib.h> 
#include <string.h> 
/*#include "node.h"*/ 
/*#include "y.tab.h"*/
char *dupstr(const char *s);
int yyerror(char *s);
%}
%x COM ZONE STR CHR CHRERROR
%%

<ZONE>"$$".*                  													;/* one line comment*/
<ZONE>"$"                     													BEGIN COM;/* multi line commment */

<COM>"$"    			            													BEGIN ZONE;
<COM>.|\n   			            													;

<ZONE>"-"                     													ECHO;
<ZONE>"+"                     													ECHO;
<ZONE>"*"                     													ECHO;
<ZONE>"/"                     													ECHO;
<ZONE>"%"                     													ECHO;
<ZONE>"^"                     													ECHO;
<ZONE>":="                    													ECHO;
<ZONE>"<"                    	 													ECHO;
<ZONE>">"                     													ECHO;
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
^"program"	  			            													BEGIN ZONE; 		ECHO;
<ZONE>^"end"			 	           	 													BEGIN INITIAL;  ECHO;
^"module"    			            													BEGIN ZONE;		  ECHO;
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

<ZONE>\'([^\']|\\[nrt'\\]|\\[0-9a-fA-F][0-9a-fA-F]?)\'	ECHO;*/ 

<ZONE>\'																								BEGIN CHR;
<CHR>\\[nrt'\\]\'																				printf("'%s", yytext);BEGIN ZONE;
<CHR>\\[0-9a-fA-F][0-9a-fA-F]\'													printf("'%s", yytext);BEGIN ZONE;
<CHR>[^\\']																						printf("'WHAZA %s'", yytext);BEGIN ZONE;																									
<CHR>.																									printf("erro");

<CHRERROR>\'																						BEGIN ZONE;
<CHRERROR>.																							printf("error");

<ZONE>\"([^\\"]|\\.)\" 	                                ECHO; REJECT;
<ZONE>\" 			                                          ECHO; BEGIN STR; 
<STR>\"	 			                                          ECHO; BEGIN ZONE;
<STR>\\n 			                                          printf("\n");
<STR>\\r 			                                          printf("\r");
<STR>\\t 			                                          printf("\t");
<STR>\\\" 		                                          printf("\"");
<STR>\\\\			                                          printf("\\");
<STR>\\[0-9a-fA-F][0-9a-fA-F]? 	                        ECHO;
<STR>\\. 			                                          ;
<STR>[^"]		                                            ECHO;

<ZONE>[A-Za-z][A-Za-z0-9_]*	  													ECHO;
<ZONE>[\#\[\]\(\)\;\:\!\,]	  													ECHO;

<ZONE>0[0-7]+			            													printf("%ld", strtol(yytext+1, 0, 0));
<ZONE>[0-9]+			            													printf("%ld", strtol(yytext, 0, 10)); 
<ZONE>0b[01]+			            													printf("%ld", strtol(yytext+2, 0, 2));
<ZONE>0x[0-9a-fA-F]+          													printf("%ld", strtol(yytext+2,0, 16));

<ZONE>[ \t\n\r]+	            													ECHO; /* ignore whitespace */ 
 
<ZONE>.                       													;	 

.|\n								         														;//	yyerror("Unknown character"); 
%% 

int main() {return yylex();}
int yywrap() {return 1;}

char *getyytext() { return yytext; }
