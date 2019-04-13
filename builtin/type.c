#include "type.h"
#include "../eval.h"
#include "../nlib.h"
#include "../err.h"

void builtin_type()
{
    i64 ms = milestone();
    eval_stack[ms - 2].t = STRING;
    eval();
    switch (get_current_eval().t) {
    case INTEGER:
        eval_stack[ms - 2].v.s = "integer";
        break;
    case FLOAT:
        eval_stack[ms - 2].v.s = "float";
        break;
    case STRING:
        eval_stack[ms - 2].v.s = "string";
        break;
    case CHAR:
        eval_stack[ms - 2].v.s = "char";
        break;
    default:
        runtime_err("basic type", neta_type2string(get_current_eval().t));
        break;
    }
    if (!read_rparen())
        parse_err(neta_type2string(RPAREN), neta_type2string(get_next_parse().t));
    reset(ms - 2);
}

void builtin_istype()
{
    i64 ms = milestone();
    eval_stack[ms - 2].t = INTEGER;
    eval();
    eval();
    if (get_current_eval().t != STRING)
        runtime_err(neta_type2string(STRING), neta_type2string(get_current_eval().t));

    switch (eval_stack[ms].t) {
    case INTEGER:
        if (strcmp(eval_stack[ms + 1].v.s, "integer") == 0)
            eval_stack[ms - 2].v.i = 1;
        else
            eval_stack[ms - 2].v.i = 0;
        break;
    case FLOAT:
        if (strcmp(eval_stack[ms + 1].v.s, "float") == 0)
            eval_stack[ms - 2].v.i = 1;
        else
            eval_stack[ms - 2].v.i = 0;
        break;
    case STRING:
        if (strcmp(eval_stack[ms + 1].v.s, "string") == 0)
            eval_stack[ms - 2].v.i = 1;
        else
            eval_stack[ms - 2].v.i = 0;
        break;
    case CHAR:
        if (strcmp(eval_stack[ms + 1].v.s, "char") == 0)
            eval_stack[ms - 2].v.i = 1;
        else
            eval_stack[ms - 2].v.i = 0;
        break;
    default:
        runtime_err("basic type", neta_type2string(get_current_eval().t));
        break;
    }
    if (!read_rparen())
        parse_err(neta_type2string(RPAREN), neta_type2string(get_next_parse().t));
    reset(ms - 2);
}