#include "string.h"
#include "../err.h"
#include "../eval.h"
#include "../nlib.h"
#include <string.h>
#include "../util.h"

void builtin_strlen()
{
    i64 ms = milestone();
    eval();
    if (get_current_eval().t != STRING && get_current_eval().t != CHAR)
        runtime_err("STRING or CHAR", neta_type2string(get_current_eval().t));
    eval_stack[ms - 2].t = INTEGER;
    if (get_current_eval().t == CHAR)
        eval_stack[ms - 2].v.i = 1;
    else
        eval_stack[ms - 2].v.i = strlen(get_current_eval().v.s);
    if (!read_rparen())
        parse_err(neta_type2string(RPAREN), neta_type2string(get_next_parse().t));
    reset(ms - 2);
}

void builtin_strcmp()
{
    i64 ms = milestone();
    eval();
    if (get_current_eval().t != STRING)
        runtime_err(neta_type2string(STRING), neta_type2string(get_current_eval().t));
    eval();
    if (get_current_eval().t != STRING)
        runtime_err(neta_type2string(STRING), neta_type2string(get_current_eval().t));
    eval_stack[ms - 2].t = INTEGER;
    eval_stack[ms - 2].v.i = strcmp(eval_stack[ms].v.s, eval_stack[ms + 1].v.s);
    if (!read_rparen())
        parse_err(neta_type2string(RPAREN), neta_type2string(get_next_parse().t));
    reset(ms - 2);
}

void builtin_str2int()
{
    i64 ms = milestone();
    eval();
    eval_stack[ms - 2].t = INTEGER;
    if (get_current_eval().t != STRING)
        runtime_err(neta_type2string(STRING), neta_type2string(get_current_eval().t));
    set_buffer(get_current_eval().v.s);
    eval_stack[ms - 2].v.i = read_i64();
    if (!read_rparen())
        parse_err(neta_type2string(RPAREN), neta_type2string(get_next_parse().t));
    reset(ms - 2);
}
void builtin_str2float()
{
    i64 ms = milestone();
    eval();
    eval_stack[ms - 2].t = INTEGER;
    if (get_current_eval().t != STRING)
        runtime_err(neta_type2string(STRING), neta_type2string(get_current_eval().t));
    set_buffer(get_current_eval().v.s);
    eval_stack[ms - 2].v.i = read_f64();
    if (!read_rparen())
        parse_err(neta_type2string(RPAREN), neta_type2string(get_next_parse().t));
    reset(ms - 2);
}