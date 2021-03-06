#include "str.h"
#include "../err.h"
#include "../eval.h"
#include "../nlib.h"
#include "../util.h"
#include <stdlib.h>

enum return_type builtin_strlen()
{
    push_trace("strlen");
    i64 ms = milestone();
    eval_errh()
    if (get_current_eval().t != STRING && get_current_eval().t != CHAR)
        runtime_errh("STRING or CHAR", neta_type2string(get_current_eval().t))
    eval_stack[ms - 2].t = INTEGER;
    if (get_current_eval().t == CHAR)
        eval_stack[ms - 2].v.i = 1;
    else
        eval_stack[ms - 2].v.i = (i64)strlen(get_current_eval().v.s);
    if (!read_rparen())
        parse_errh(neta_type2string(RPAREN), neta_type2string(get_next_parse().t))
    pop_trace();
    reset(ms - 2);
    return NORMAL;
}

enum return_type builtin_strcmp()
{
    push_trace("strcmp");
    i64 ms = milestone();
    eval_errh()
    if (get_current_eval().t != STRING)
        runtime_errh(neta_type2string(STRING), neta_type2string(get_current_eval().t))
    eval_errh()
    if (get_current_eval().t != STRING)
        runtime_errh(neta_type2string(STRING), neta_type2string(get_current_eval().t))
    eval_stack[ms - 2].t = INTEGER;
    eval_stack[ms - 2].v.i = (i64)strcmp(eval_stack[ms].v.s, eval_stack[ms + 1].v.s);
    if (!read_rparen())
        parse_errh(neta_type2string(RPAREN), neta_type2string(get_next_parse().t))
    pop_trace();
    reset(ms - 2);
    return NORMAL;
}

enum return_type builtin_str2int()
{
    push_trace("str2int");
    i64 ms = milestone();
    eval_errh()
    eval_stack[ms - 2].t = INTEGER;
    if (get_current_eval().t != STRING)
        runtime_errh(neta_type2string(STRING), neta_type2string(get_current_eval().t))
    set_buffer(get_current_eval().v.s);
    eval_stack[ms - 2].v.i = read_i64();
    if (!read_rparen())
        parse_errh(neta_type2string(RPAREN), neta_type2string(get_next_parse().t))
    pop_trace();
    reset(ms - 2);
    return NORMAL;
}
enum return_type builtin_str2float()
{
    push_trace("str2float");
    i64 ms = milestone();
    eval_errh()
    eval_stack[ms - 2].t = FLOAT;
    if (get_current_eval().t != STRING)
        runtime_errh(neta_type2string(STRING), neta_type2string(get_current_eval().t))
    set_buffer(get_current_eval().v.s);
    eval_stack[ms - 2].v.f = read_f64();
    if (!read_rparen())
        parse_errh(neta_type2string(RPAREN), neta_type2string(get_next_parse().t))
    pop_trace();
    reset(ms - 2);
    return NORMAL;
}