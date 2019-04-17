#include "parse.h"
#include "../eval.h"
#include "../err.h"
#include "../nlib.h"
#include <stdio.h>

extern FILE *yyin;
int yylex();

enum return_type builtin_parse()
{
    push_trace("parse");
    enum error_type err_c = error_mode;
    error_mode = PARSE;
    i64 ms = milestone();
    eval();
    if (is_err)
        return NORMAL;
    if (get_current_eval().t != STRING)
        runtime_errh(neta_type2string(STRING), neta_type2string(get_current_eval().t))
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
        eval_top = ms + 1;
        if (is_err) {
            is_err = false;
            error_mode = err_c;
            break;
        }
    }
    ptr = ptr_m;
    parse_top = parse_top_m;
    if (!read_rparen())
        parse_errh(neta_type2string(RPAREN), neta_type2string(get_next_parse().t))
    eval_stack[ms - 2] = default_return;
    pop_trace();
    reset(ms - 2);
    error_mode = err_c;
    return NORMAL;
}

enum return_type builtin_eval()
{
    push_trace("eval");
    enum error_type err_c = error_mode;
    error_mode = EVAL;
    i64 ms = milestone();
    eval();
    if (is_err)
        return NORMAL;
    if (get_current_eval().t != STRING)
        runtime_errh(neta_type2string(STRING), neta_type2string(get_current_eval().t))
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
        
    eval();
    if (is_err) {
        is_err = false;
        error_mode = err_c;
        eval_stack[ms - 2] = default_return;
    } else
        eval_stack[ms - 2] = get_current_eval();
    // eval_top -= 1;

    ptr = ptr_m;
    parse_top = parse_top_m;
    if (!read_rparen())
        parse_errh(neta_type2string(RPAREN), neta_type2string(get_next_parse().t))
    pop_trace();
    reset(ms - 2);
    error_mode = err_c;
    return NORMAL;
}