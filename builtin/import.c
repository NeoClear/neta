#include "import.h"
#include "../eval.h"
#include "../nlib.h"
#include "../err.h"

extern FILE *yyin;
extern int yyleng;

int yylex();

void builtin_import()
{
    i64 ms = milestone();
    if (!read_string())
        runtime_err(neta_type2string(STRING), neta_type2string(get_next_parse().t));
    i64 ptr_m = ptr;
    i64 parse_top_m = parse_top;
    yyin = fopen(get_current_eval().v.s, "r");
    if (yyin == nil)
        err("could not open file");
    ptr = parse_top;
    yylex();
    while (!parse_finished()) {
        eval();
        eval_top = 0;
    }
    ptr = ptr_m;
    parse_top = parse_top_m;
    if (!read_rparen())
        parse_err(neta_type2string(RPAREN), neta_type2string(get_next_parse().t));
    reset(ms - 2);
}