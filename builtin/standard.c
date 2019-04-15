#include "standard.h"
#include "../eval.h"
#include "../err.h"
#include "../nlib.h"

void builtin_equal_val()
{
    i64 ms = milestone();
    eval();
    eval();
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
        parse_err(neta_type2string(RPAREN), neta_type2string(get_next_parse().t));
    reset(ms - 2);
}