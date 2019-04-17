#include "standard.h"
#include "../eval.h"
#include "../err.h"
#include "../nlib.h"

enum return_type builtin_equal_val()
{
    push_trace("equal");
    i64 ms = milestone();
    eval_errh()
    eval_errh()
    eval_stack[ms - 2].t = INTEGER;
    switch (eval_stack[ms].t) {
    case INTEGER:
        if (eval_stack[ms + 1].t == INTEGER) {
            if (eval_stack[ms].v.i == eval_stack[ms + 1].v.i)
                eval_stack[ms - 2].v.i = 1;
            else
                eval_stack[ms - 2].v.i = 0;
        }
        break;
    case FLOAT:
        if (eval_stack[ms + 1].t == FLOAT) {
            if (eval_stack[ms].v.f == eval_stack[ms + 1].v.f)
                eval_stack[ms - 2].v.i = 1;
            else
                eval_stack[ms - 2].v.i = 0;
        }
        break;
    case STRING:
        if (eval_stack[ms + 1].t == STRING) {
            if (strcmp(eval_stack[ms].v.s, eval_stack[ms + 1].v.s) == 0)
                eval_stack[ms - 2].v.i = 1;
            else
                eval_stack[ms - 2].v.i = 0;
        }
        break;
    case CHAR:
        if (eval_stack[ms + 1].t == CHAR) {
            if (eval_stack[ms].v.c == eval_stack[ms + 1].v.c)
                eval_stack[ms - 2].v.i = 1;
            else
                eval_stack[ms - 2].v.i = 0;
        }
        break;
    case SYMBOL:
        if (eval_stack[ms + 1].t == SYMBOL) {
            if (strcmp(eval_stack[ms].v.s, eval_stack[ms + 1].v.s) == 0)
                eval_stack[ms - 2].v.i = 1;
            else
                eval_stack[ms - 2].v.i = 0;
        }
        break;
    default:
        eval_stack[ms - 2].v.i = 0;
        break;
    }
    if (!read_rparen())
        parse_errh(neta_type2string(RPAREN), neta_type2string(get_next_parse().t))
    pop_trace();
    reset(ms - 2);
    return NORMAL;
}

enum return_type builtin_int2float()
{
    push_trace("int2float");
    i64 ms = milestone();
    eval_errh()
    if (get_current_eval().t != INTEGER)
        runtime_errh(neta_type2string(INTEGER), neta_type2string(get_current_eval().t))
    eval_stack[ms - 2].t = FLOAT;
    eval_stack[ms - 2].v.f = (f64)get_current_eval().v.i;
    if (!read_rparen())
        parse_errh(neta_type2string(RPAREN), neta_type2string(get_next_parse().t))
    pop_trace();
    reset(ms - 2);
    return NORMAL;
}
enum return_type builtin_float2int()
{
    push_trace("float2int");
    i64 ms = milestone();
    eval_errh()
    if (get_current_eval().t != FLOAT)
        runtime_errh(neta_type2string(FLOAT), neta_type2string(get_current_eval().t))
    eval_stack[ms - 2].t = INTEGER;
    eval_stack[ms - 2].v.i = (i64)get_current_eval().v.f;
    if (!read_rparen())
        parse_errh(neta_type2string(RPAREN), neta_type2string(get_next_parse().t))
    pop_trace();
    reset(ms - 2);
    return NORMAL;
}