#include "type.h"
#include "../eval.h"
#include "../nlib.h"
#include "../err.h"

enum return_type builtin_type()
{
    push_trace("type");
    i64 ms = milestone();
    eval_stack[ms - 2].t = SYMBOL;
    eval_errh()
    switch (get_current_eval().t) {
    case INTEGER:
        eval_stack[ms - 2].v.s = "@int";
        break;
    case FLOAT:
        eval_stack[ms - 2].v.s = "@float";
        break;
    case STRING:
        eval_stack[ms - 2].v.s = "@string";
        break;
    case CHAR:
        eval_stack[ms - 2].v.s = "@char";
        break;
    case SYMBOL:
        eval_stack[ms - 2].v.s = "@symbol";
        break;
    case LIST:
        eval_stack[ms - 2].v.s = "@list";
    default:
        runtime_errh("basic type", neta_type2string(get_current_eval().t))
        break;
    }
    if (!read_rparen())
        parse_errh(neta_type2string(RPAREN), neta_type2string(get_next_parse().t))
    pop_trace();
    reset(ms - 2);
    return NORMAL;
}

enum return_type builtin_istype()
{
    push_trace("is_type");
    i64 ms = milestone();
    eval_stack[ms - 2].t = INTEGER;
    eval_errh()
    eval_errh()
    if (get_current_eval().t != SYMBOL)
        runtime_errh(neta_type2string(SYMBOL), neta_type2string(get_current_eval().t))

    switch (eval_stack[ms].t) {
    case INTEGER:
        if (strcmp(eval_stack[ms + 1].v.s, "@int") == 0)
            eval_stack[ms - 2].v.i = 1;
        else
            eval_stack[ms - 2].v.i = 0;
        break;
    case FLOAT:
        if (strcmp(eval_stack[ms + 1].v.s, "@float'") == 0)
            eval_stack[ms - 2].v.i = 1;
        else
            eval_stack[ms - 2].v.i = 0;
        break;
    case STRING:
        if (strcmp(eval_stack[ms + 1].v.s, "@string") == 0)
            eval_stack[ms - 2].v.i = 1;
        else
            eval_stack[ms - 2].v.i = 0;
        break;
    case CHAR:
        if (strcmp(eval_stack[ms + 1].v.s, "@char") == 0)
            eval_stack[ms - 2].v.i = 1;
        else
            eval_stack[ms - 2].v.i = 0;
        break;
    case SYMBOL:
        if (strcmp(eval_stack[ms + 1].v.s, "@symbol") == 0)
            eval_stack[ms - 2].v.i = 1;
        else
            eval_stack[ms - 2].v.i = 0;
        break;
    case LIST:
        if (strcmp(eval_stack[ms + 1].v.s, "@list") == 0)
            eval_stack[ms - 2].v.i = 1;
        else
            eval_stack[ms - 2].v.i = 0;
        break;
    default:
        runtime_errh("basic type", neta_type2string(get_current_eval().t))
        break;
    }
    if (!read_rparen())
        parse_errh(neta_type2string(RPAREN), neta_type2string(get_next_parse().t))
    pop_trace();
    reset(ms - 2);
    return NORMAL;
}