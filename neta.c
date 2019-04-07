/*
 * neta.c contains:
 * main function
 */

#include <stdio.h>
#include "eval.h"
#include "debug.h"
#include "data.h"
#include "util.h"

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
    while (!parse_finished()) {
        eval();
        print_eval_stack();
        eval_top = 0;
    }
    print_global_variable_d(glov);
    // print_global_variable();
    
    return 0;
}