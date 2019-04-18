#include "standard.h"
#include "../eval.h"
#include "../err.h"
#include "../nlib.h"
#include "../debug.h"

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

enum return_type builtin_catch()
{
    i64 ms = milestone();
    i64 ptr_j = look_ahead();
    eval();
    if (is_err) {
        if (err_tp == PARSING_ERR)
            return NORMAL;
        is_err = false;
    }
    reset(ms - 2);
    ptr = ptr_j;
    return NORMAL;
}
enum return_type builtin_throw()
{
    i64 ms = milestone();
    eval_errh()
    if (get_current_eval().t != SYMBOL)
        runtime_errh(neta_type2string(SYMBOL), neta_type2string(get_current_eval().t))
    is_err = true;
    err_tp = RUNTIME_ERR;
    err_msg = get_current_eval().v.s;
    return NORMAL;
}
enum return_type builtin_errmsg()
{
    i64 ms = milestone();
    eval_stack[ms - 2].t = STRING;
    eval_stack[ms - 2].v.s = err_msg;
    err_msg = "";
    if (!read_rparen())
        parse_errh(neta_type2string(RPAREN), neta_type2string(get_next_parse().t))
    reset(ms - 2);
    return NORMAL;
}

boolean sub_match(i64 ms)
{
    eval();
    if (is_err)
        return false;
    // printf("%s - %s\n", neta_node2string(eval_stack[ms]), neta_node2string(get_current_eval()));
    if (equal(eval_stack[ms], get_current_eval())) {
        eval();
        if (is_err)
            return false;
        return true;
    } else {
        ignore_exp();
        return false;
    }
    return false;
}

enum return_type builtin_match()
{
    i64 ms = milestone();
    i64 ptr_j = look_ahead();
    eval_stack[ms - 2] = default_return;
    eval_errh()
    while (!read_rparen()) {
        if (sub_match(ms)) {
            ptr = ptr_j;
            eval_stack[ms - 2] = get_current_eval();
            reset(ms - 2);
            return NORMAL;
        } else if (is_err)
            return NORMAL;
        else
            eval_top = ms + 1;
    }
    reset(ms - 2);
}

boolean sub_when(i64 ms)
{
    eval();
    if (is_err)
        return false;
    if (get_current_eval().t != INTEGER)
        runtime_errh(neta_type2string(INTEGER), neta_type2string(get_current_eval().t))
    if (get_current_eval().v.i != 0) {
        eval();
        if (is_err)
            return false;
        return true;
    } else {
        ignore_exp();
        return false;
    }
    return false;
}

enum return_type builtin_when()
{
    i64 ms = milestone();
    i64 ptr_j = look_ahead();
    eval_stack[ms - 2] = default_return;
    // eval_errh()
    while (!read_rparen()) {
        if (sub_when(ms)) {
            ptr = ptr_j;
            eval_stack[ms - 2] = get_current_eval();
            reset(ms - 2);
            return NORMAL;
        } else if (is_err)
            return NORMAL;
        else
            eval_top = ms + 1;
    }
    reset(ms - 2);
}
