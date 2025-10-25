%{
#include <stdio.h>
#include <stdlib.h>
int yylex();
int yyerror(const char *s);
%}
%token OPERAND
%left  '+' '-'
%left  '*' '/'
%right UMINUS

%%
start:  expr '\n' {printf("\n");}

expr:   expr'+'expr {printf("+");}
      |  expr'-'expr {printf("-");}
      |  expr'*'expr {printf("*");}
      |  expr'/'expr {printf("/");}
      |  '('expr')' {}
      |   '-' expr %prec UMINUS  {printf("~");}
      |   OPERAND    {printf("%c",$1);}

%%

int main()
{
        printf("Enter the expression:");
        yyparse();
        return 0;
}
int yyerror(const char *s)
{
        printf("Invalid\n");
        return 0;
}
