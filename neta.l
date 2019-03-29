%{
#include <string.h>
#include <math.h>
#include "io.h"
#include "lexer.h"
#include "debug.h"
i64 row = 0;
i64 column = 0;
i64 word = 0;

void word_plus()
{
    word++;
}
void new_line()
{
    row++;
    column = 0;
}
void column_plus(i64 n)
{
    column += n;
}
%}

DIGIT           [0-9]
PRESERVED_FUN   "+"|"-"|"*"|"/"|"def"|"undef"|"var"|"val"|".."
IDENTIFIER      [a-zA-Z][a-zA-Z0-9]*
LPAREN          "("
RPAREN          ")"
STRING          \"[^\"\']*\"
CHAR            \'[^\"\']\'

%%
{LPAREN}            {
    word_plus();
    column_plus(strlen(yytext));
    // printf("LParen\n");
    add_lparen();
}
{RPAREN}            {
    word_plus();
    column_plus(strlen(yytext));
    // printf("RParen\n");
    add_rparen();
}
{PRESERVED_FUN}     {
    word_plus();
    column_plus(strlen(yytext));
    // printf("Preserved Function: %s\n", yytext);
    add_preserved_fun(clone(yytext));
}
{IDENTIFIER}        {
    word_plus();
    column_plus(strlen(yytext));
    // printf("Identifier\n");
    add_identifier(clone(yytext));
}
{DIGIT}+            {
    word_plus();
    column_plus(strlen(yytext));
    // printf("Int: %s\n", yytext);
    set_buffer(yytext);
    add_integer(read_i64());
}
{DIGIT}+"."{DIGIT}+   {
    word_plus();
    // printf("Double: %s\n", yytext);
    set_buffer(yytext);
    // printf("Double: %llf\n", read_f64());
    add_float(read_f64());
}
{STRING}            {
    word_plus();
    column_plus(strlen(yytext));
    // printf("String: %s\n", drop_shell(yytext));
    add_string(drop_shell(yytext));
}
{CHAR}              {
    word_plus();
    column_plus(strlen(yytext));
    // printf("Char: %s\n", yytext);
    add_char(yytext[1]);
}
" "+                {
    column_plus(strlen(yytext));
    // printf("WhiteSpace\n");
}
"\t"                {
    column_plus(4);
    // printf("Tab\n");
}
"\n"|"\r\n"         {
    new_line();
    // printf("NewLine\n");
}
.                   {
    printf("Unknown Character At (Row: %lld, Column: %lld, word: %lld)\n", row, column, word);
}
%%
