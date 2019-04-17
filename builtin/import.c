#include "import.h"
#include "../eval.h"
#include "../nlib.h"
#include "../err.h"

extern FILE *yyin;
extern int yyleng;

int yylex();

enum return_type builtin_import()
{
    i64 ms = milestone();
    if (!read_string())
        runtime_errh(neta_type2string(STRING), neta_type2string(get_next_parse().t))
    i64 ptr_m = ptr;
    i64 parse_top_m = parse_top;
    yyin = fopen(get_current_eval().v.s, "r");
    if (yyin == nil)
        errh("could not open file")
    ptr = parse_top;
    yylex();
    while (!parse_finished()) {
        eval_errh()
        eval_top = 0;
    }
    ptr = ptr_m;
    parse_top = parse_top_m;
    if (!read_rparen())
        parse_errh(neta_type2string(RPAREN), neta_type2string(get_next_parse().t))
    eval_stack[ms - 2] = default_return;
    reset(ms - 2);
    return NORMAL;
}