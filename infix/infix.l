%{
#include "y.tab.h"
%}
%option noyywrap
%%
[a-zA-Z0-9]   {yylval=yytext[0];return OPERAND;}
[+\-*/()\n]       {return yytext[0];}
[\t]            ;
.             {return yytext[0];}

%%
