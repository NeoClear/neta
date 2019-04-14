#include "parse.h"
#include "../eval.h"
#include "../err.h"
#include "../nlib.h"
#include <stdio.h>

extern FILE *yyin;
int yylex();

void builtin_parse()
{
    i64 ms = milestone();
    eval();
    if (get_current_eval().t != STRING)
        runtime_err(neta_type2string(STRING), neta_type2string(get_current_eval().t));
    i64 ptr_m = ptr;
    i64 parse_top_m = parse_top;
    ptr = parse_top;

    FILE *tmp = fopen("parse.tmp", "w+");
    fprintf(tmp, "%s", get_current_eval().v.s);
    rewind(tmp);
    fflush(tmp);
    yyin = tmp;
    yylex();
    remove("parse.tmp");
    while (!parse_finished()) {
        eval();
        eval_top -= 1;
    }
    ptr = ptr_m;
    parse_top = parse_top_m;
    if (!read_rparen())
        parse_err(neta_type2string(RPAREN), neta_type2string(get_next_parse().t));
    reset(ms - 2);
}