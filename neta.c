/*
 * neta.c contains:
 * main function
 */

#include <stdio.h>
#include "eval.h"
#include "debug.h"
#include "data.h"
#include "util.h"
#include <stdlib.h>
#include <time.h>

extern FILE *yyin;
extern int yyleng;

void init()
{
    srand((i64)time(nil));
}

int yylex();

int main(int argc, char **argv) {
    argc--, argv++;
    if (argc > 0)
        yyin = fopen(argv[0], "r");
    else
        yyin = stdin;
    yylex();
    init();
    while (!parse_finished()) {
        eval();
        eval_top = 0;
    }
    return 0;
}