%{
#include <string.h>
#include <math.h>
#include "lexer.h"
#include "util.h"
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
PRESERVED_FUN_1 "+"|"-"|"*"|"/"|"d+"|"d-"
PRESERVED_FUN_2 "d*"|"d/"|"<"|"="|">"|"<="
PRESERVED_FUN_3 "!="|">="|"fun"|"undef"|"var"
PRESERVED_FUN_4 "val"|".."|"setf"|"setc"|"prog"
PRESERVED_FUN_5 "!"|"if"|"println"|"print"|"strlen"
PRESERVED_FUN_6 "strcmp"|"while"|"->"|"assign"
PRESERVED_FUN_7 "setl"|"import"|"type"|"istype"
PRESERVED_FUN_8 "rand"|"equal"|"parse"|"read"|"readln"
PRESERVED_FUN_9 "str2int"|"str2float"|"int2float"
PRESERVED_FUN_A "float2int"|"return-f"|"return-p"
PRESERVED_FUN_B "eval"|"catch"|"throw"|"errmsg"|"def?"

IDENTIFIER      [a-zA-Z][?a-zA-Z0-9-]*
SYMBOL          @[a-zA-Z][?a-zA-Z0-9-]*
LPAREN          "("
RPAREN          ")"
LBRACE          "{"
RBRACE          "}"
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
{LBRACE}            {
    word_plus();
    column_plus(strlen(yytext));
    add_lparen();
    add_preserved_fun("!");
}
{RBRACE}            {
    word_plus();
    column_plus(strlen(yytext));
    add_rparen();
}
{SYMBOL}            {
    word_plus();
    column_plus(strlen(yytext));
    add_symbol(clone(yytext));
}
{PRESERVED_FUN_1}     {
    word_plus();
    column_plus(strlen(yytext));
    // printf("Preserved Function: %s\n", yytext);
    add_preserved_fun(clone(yytext));
}
{PRESERVED_FUN_2}     {
    word_plus();
    column_plus(strlen(yytext));
    // printf("Preserved Function: %s\n", yytext);
    add_preserved_fun(clone(yytext));
}
{PRESERVED_FUN_3}     {
    word_plus();
    column_plus(strlen(yytext));
    // printf("Preserved Function: %s\n", yytext);
    add_preserved_fun(clone(yytext));
}
{PRESERVED_FUN_4}     {
    word_plus();
    column_plus(strlen(yytext));
    // printf("Preserved Function: %s\n", yytext);
    add_preserved_fun(clone(yytext));
}
{PRESERVED_FUN_5}     {
    word_plus();
    column_plus(strlen(yytext));
    // printf("Preserved Function: %s\n", yytext);
    add_preserved_fun(clone(yytext));
}
{PRESERVED_FUN_6}     {
    word_plus();
    column_plus(strlen(yytext));
    // printf("Preserved Function: %s\n", yytext);
    add_preserved_fun(clone(yytext));
}
{PRESERVED_FUN_7}     {
    word_plus();
    column_plus(strlen(yytext));
    // printf("Preserved Function: %s\n", yytext);
    add_preserved_fun(clone(yytext));
}
{PRESERVED_FUN_8}       {
    word_plus();
    column_plus(strlen(yytext));
    add_preserved_fun(clone(yytext));
}
{PRESERVED_FUN_9}       {
    word_plus();
    column_plus(strlen(yytext));
    add_preserved_fun(clone(yytext));
}

{PRESERVED_FUN_A}       {
    word_plus();
    column_plus(strlen(yytext));
    add_preserved_fun(clone(yytext));
}
{PRESERVED_FUN_B}       {
    word_plus();
    column_plus(strlen(yytext));
    add_preserved_fun(clone(yytext));
}
{IDENTIFIER}        {
    word_plus();
    column_plus(strlen(yytext));
    // printf("Identifier\n");
    add_identifier(clone(yytext));
}
"-"?{DIGIT}+        {
    word_plus();
    column_plus(strlen(yytext));
    // printf("Int: %s\n", yytext);
    set_buffer(yytext);
    add_integer(read_i64());
}
"-"?{DIGIT}+"."{DIGIT}+ {
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
";;".+|";;".+       {
    new_line();
}
.                   {
    printf("Unknown Character At (Row: %lld, Column: %lld, word: %lld)\n", row, column, word);
}
%%
