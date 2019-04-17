/*
 * neta.c contains:
 * main function
 */

#include <stdio.h>
#include "eval.h"
#include "debug.h"
#include "data.h"
#include "util.h"
#include "nlib.h"
#include <stdlib.h>
#include <time.h>
#include "err.h"

extern FILE *yyin;
extern int yyleng;

int yylex();

int shit();

void init()
{
    srand((i64)time(nil));
}

int main(int argc, char **argv) {
    argc--, argv++;
    if (argc > 0)
        yyin = fopen(argv[0], "r");
    else
        yyin = stdin;
    yylex();
    init();
    // print_parse_tree();
    while (!parse_finished()) {
        eval();
        if (is_err)
            exit(0);
        eval_top = 0;
    }
    return 0;
}