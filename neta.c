#include <stdio.h>
#include "eval.h"
#include "debug.h"
#include "data.h"

extern FILE *yyin;
extern int yyleng;

int yylex();

int main(int argc, char **argv) {
    argc--, argv++;
    if (argc > 0)
        yyin = fopen(argv[0], "r");
    else
        yyin = stdin;
    yylex();
    // print_parse_tree();
    eval();
    
    print_eval_stack();
    print_global_variable();
    return 0;
}