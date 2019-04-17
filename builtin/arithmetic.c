#include "arithmetic.h"
#include "../debug.h"
#include "../util.h"
#include "../data.h"
#include "../err.h"
#include "../nlib.h"
#include <stdlib.h>

void builtin_plus()
{
    push_trace("+");
    i64 ms = milestone();
    i64 ans = 0;
    // Read and eval params
    while (!read_rparen()) {
        eval();
    }
    // Add them
    for (i64 i = ms; i <= offset(-2); i++) {
        eval_stack[i] = num2int(eval_stack[i]);
        ans += eval_stack[i].v.i;
    }
    // Place the answer and reset eval stack
    eval_stack[ms - 2].t = INTEGER;
    eval_stack[ms - 2].v.i = ans;
    pop_trace();
    reset(ms - 2);
}

void builtin_minus()
{
    push_trace("-");
    i64 ms = milestone();
    i64 ans = 0;
    // Read and eval params
    while (!read_rparen()) {
        eval();
    }
    ans = num2int(eval_stack[ms]).v.i;
    // Minus them
    for (i64 i = ms + 1; i <= offset(-2); i++) {
        eval_stack[i] = num2int(eval_stack[i]);
        ans -= eval_stack[i].v.i;
    }
    // Place the answer and reset eval stack
    eval_stack[ms - 2].t = INTEGER;
    eval_stack[ms - 2].v.i = ans;
    pop_trace();
    reset(ms - 2);
}

void builtin_mul()
{
    push_trace("*");
    i64 ms = milestone();
    i64 ans = 1;
    // Read and eval params
    while (!read_rparen()) {
        eval();
    }
    // Times them
    for (i64 i = ms; i <= offset(-2); i++) {
        eval_stack[i] = num2int(eval_stack[i]);
        ans *= eval_stack[i].v.i;
    }
    // Place the answer and reset eval stack
    eval_stack[ms - 2].t = INTEGER;
    eval_stack[ms - 2].v.i = ans;
    pop_trace();
    reset(ms - 2);
}

void builtin_div()
{
    push_trace("/");
    i64 ms = milestone();
    i64 ans = 0;
    // Read and eval params
    while (!read_rparen()) {
        eval();
    }
    ans = num2int(eval_stack[ms]).v.i;
    // Divide them
    for (i64 i = ms + 1; i <= offset(-2); i++) {
        eval_stack[i] = num2int(eval_stack[i]);
        if (eval_stack[i].v.i != 0)
            ans /= eval_stack[i].v.i;
        else
            runtime_err("none zero", "zero");
    }
    // Place the answer and reset eval stack
    eval_stack[ms - 2].t = INTEGER;
    eval_stack[ms - 2].v.i = ans;
    pop_trace();
    reset(ms - 2);
}

void builtin_dplus()
{
    push_trace("d+");
    i64 ms = milestone();
    f64 ans = 0;
    // Read and eval params    
    while (!read_rparen()) {
        eval();
    }
    // Add them
    for (i64 i = ms; i <= offset(-2); i++) {
        eval_stack[i] = num2float(eval_stack[i]);
        ans += eval_stack[i].v.f;
    }
    // Place the answer and reset eval stack
    eval_stack[ms - 2].t = FLOAT;
    eval_stack[ms - 2].v.f = ans;
    pop_trace();
    reset(ms - 2);
}

void builtin_dminus()
{
    push_trace("d-");
    i64 ms = milestone();
    f64 ans = 0;
    // Read and eval params
    while (!read_rparen()) {
        eval();
    }
    ans = num2float(eval_stack[ms]).v.f;
    // Minus them
    for (i64 i = ms + 1; i <= offset(-2); i++) {
        eval_stack[i] = num2float(eval_stack[i]);
        ans -= eval_stack[i].v.f;
    }
    // Place the answer and reset eval stack
    eval_stack[ms - 2].t = FLOAT;
    eval_stack[ms - 2].v.f = ans;
    pop_trace();
    reset(ms - 2);
}

void builtin_dmul()
{
    push_trace("d*");
    i64 ms = milestone();
    f64 ans = 1;
    // Read and eval params
    while (!read_rparen()) {
        eval();
    }
    // Times them
    for (i64 i = ms; i <= offset(-2); i++) {
        eval_stack[i] = num2float(eval_stack[i]);
        ans *= eval_stack[i].v.f;
    }
    // Place the answer and reset eval stack
    eval_stack[ms - 2].t = FLOAT;
    eval_stack[ms - 2].v.f = ans;
    pop_trace();
    reset(ms - 2);
}

void builtin_ddiv()
{
    push_trace("d/");
    i64 ms = milestone();
    f64 ans = 0;
    // Read and eval params
    while (!read_rparen()) {
        eval();
    }
    // Divide them
    ans = num2float(eval_stack[ms]).v.f;
    for (i64 i = ms + 1; i <= offset(-2); i++) {
        eval_stack[i] = num2float(eval_stack[i]);
        if (eval_stack[i].v.f != 0)
            ans /= eval_stack[i].v.f;
        else
            runtime_err("none zero", "zero");
    }
    // Place the answer and reset eval stack
    eval_stack[ms - 2].t = FLOAT;
    eval_stack[ms - 2].v.f = ans;
    pop_trace();
    reset(ms - 2);
}

void builtin_less()
{
    push_trace("<");
    i64 ms = milestone();
    eval();
    // Read param one
    if (get_current_eval().t != INTEGER && get_current_eval().t != FLOAT)
        runtime_err("number", neta_type2string(get_current_eval().t));
    eval();
    // Read param two
    if (get_current_eval().t != INTEGER && get_current_eval().t != FLOAT)
        runtime_err("number", neta_type2string(get_current_eval().t));
    // Read close paren
    if (!read_rparen())
        parse_err(neta_type2string(RPAREN), neta_type2string(get_next_parse().t));
    // Place the answer and reset eval stack
    eval_stack[ms - 2].t = INTEGER;
    if (num2float(eval_stack[ms]).v.f < num2float(eval_stack[ms + 1]).v.f)
        eval_stack[ms - 2].v.i = 1;
    else
        eval_stack[ms - 2].v.i = 0;
    pop_trace();
    reset(ms - 2);
}
void builtin_equal()
{
    push_trace("=");
    i64 ms = milestone();
    eval();
    // Read param one
    if (get_current_eval().t != INTEGER && get_current_eval().t != FLOAT)
        runtime_err("number", neta_type2string(get_current_eval().t));
    eval();
    // Read param two
    if (get_current_eval().t != INTEGER && get_current_eval().t != FLOAT)
        runtime_err("number", neta_type2string(get_current_eval().t));
    // Read close paren
    if (!read_rparen())
        parse_err(neta_type2string(RPAREN), neta_type2string(get_next_parse().t));
    // Place the answer and reset eval stack
    eval_stack[ms - 2].t = INTEGER;
    if (num2float(eval_stack[ms]).v.f == num2float(eval_stack[ms + 1]).v.f)
        eval_stack[ms - 2].v.i = 1;
    else
        eval_stack[ms - 2].v.i = 0;
    pop_trace();
    reset(ms - 2);
}
void builtin_greater()
{
    push_trace(">");
    i64 ms = milestone();
    eval();
    // Read param one
    if (get_current_eval().t != INTEGER && get_current_eval().t != FLOAT)
        runtime_err("number", neta_type2string(get_current_eval().t));
    eval();
    // Read param two
    if (get_current_eval().t != INTEGER && get_current_eval().t != FLOAT)
        runtime_err("number", neta_type2string(get_current_eval().t));
    // Read close paren
    if (!read_rparen())
        parse_err(neta_type2string(RPAREN), neta_type2string(get_next_parse().t));
    // Place the answer and reset eval stack
    eval_stack[ms - 2].t = INTEGER;
    if (num2float(eval_stack[ms]).v.f > num2float(eval_stack[ms + 1]).v.f)
        eval_stack[ms - 2].v.i = 1;
    else
        eval_stack[ms - 2].v.i = 0;
    pop_trace();
    reset(ms - 2);
}
void builtin_less_equal()
{
    push_trace("<=");
    i64 ms = milestone();
    eval();
    // Read param one
    if (get_current_eval().t != INTEGER && get_current_eval().t != FLOAT)
        runtime_err("number", neta_type2string(get_current_eval().t));
    eval();
    // Read param two
    if (get_current_eval().t != INTEGER && get_current_eval().t != FLOAT)
        runtime_err("number", neta_type2string(get_current_eval().t));
    // Read close paren
    if (!read_rparen())
        parse_err(neta_type2string(RPAREN), neta_type2string(get_next_parse().t));
    // Place the answer and reset eval stack
    eval_stack[ms - 2].t = INTEGER;
    if (num2float(eval_stack[ms]).v.f <= num2float(eval_stack[ms + 1]).v.f)
        eval_stack[ms - 2].v.i = 1;
    else
        eval_stack[ms - 2].v.i = 0;
    pop_trace();
    reset(ms - 2);
}
void builtin_not_equal()
{
    push_trace("!=");
    i64 ms = milestone();
    eval();
    // Read param one
    if (get_current_eval().t != INTEGER && get_current_eval().t != FLOAT)
        runtime_err("number", neta_type2string(get_current_eval().t));
    eval();
    // Read param two
    if (get_current_eval().t != INTEGER && get_current_eval().t != FLOAT)
        runtime_err("number", neta_type2string(get_current_eval().t));
    // Read close paren
    if (!read_rparen())
        parse_err(neta_type2string(RPAREN), neta_type2string(get_next_parse().t));
    // Place the answer and reset eval stack
    eval_stack[ms - 2].t = INTEGER;
    if (num2float(eval_stack[ms]).v.f != num2float(eval_stack[ms + 1]).v.f)
        eval_stack[ms - 2].v.i = 1;
    else
        eval_stack[ms - 2].v.i = 0;
    pop_trace();
    reset(ms - 2);
}
void builtin_greater_equal()
{
    push_trace(">=");
    i64 ms = milestone();
    eval();
    // Read param one
    if (get_current_eval().t != INTEGER && get_current_eval().t != FLOAT)
        runtime_err("number", neta_type2string(get_current_eval().t));
    eval();
    // Read param two
    if (get_current_eval().t != INTEGER && get_current_eval().t != FLOAT)
        runtime_err("number", neta_type2string(get_current_eval().t));
    // Read close paren
    if (!read_rparen())
        parse_err(neta_type2string(RPAREN), neta_type2string(get_next_parse().t));
    // Place the answer and reset eval stack
    eval_stack[ms - 2].t = INTEGER;
    if (num2float(eval_stack[ms]).v.f >= num2float(eval_stack[ms + 1]).v.f)
        eval_stack[ms - 2].v.i = 1;
    else
        eval_stack[ms - 2].v.i = 0;
    pop_trace();
    reset(ms - 2);
}

void builtin_rand()
{
    push_trace("rand");
    i64 ms = milestone();
    if (!read_rparen())
        parse_err(neta_type2string(RPAREN), neta_type2string(get_next_parse().t));
    eval_stack[ms - 2].t = INTEGER;
    eval_stack[ms - 2].v.i = rand();
    pop_trace();
    reset(ms - 2);
}