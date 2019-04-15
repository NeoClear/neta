#include "arithmetic.h"
#include "../debug.h"
#include "../util.h"
#include "../data.h"
#include "../err.h"
#include <stdlib.h>

void builtin_plus()
{
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
    eval_stack[offset_m(ms, -2)].t = INTEGER;
    eval_stack[offset_m(ms, -2)].v.i = ans;
    eval_top = ms - 1;
}

void builtin_minus()
{
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
    eval_stack[offset_m(ms, -2)].t = INTEGER;
    eval_stack[offset_m(ms, -2)].v.i = ans;
    eval_top = ms - 1;
}

void builtin_mul()
{
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
    eval_stack[offset_m(ms, -2)].t = INTEGER;
    eval_stack[offset_m(ms, -2)].v.i = ans;
    eval_top = ms - 1;
}

void builtin_div()
{
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
    eval_stack[offset_m(ms, -2)].t = INTEGER;
    eval_stack[offset_m(ms, -2)].v.i = ans;
    eval_top = ms - 1;
}

void builtin_dplus()
{
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
    eval_stack[offset_m(ms, -2)].t = FLOAT;
    eval_stack[offset_m(ms, -2)].v.f = ans;
    eval_top = ms - 1;
}

void builtin_dminus()
{
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
    eval_stack[offset_m(ms, -2)].t = FLOAT;
    eval_stack[offset_m(ms, -2)].v.f = ans;
    eval_top = ms - 1;
}

void builtin_dmul()
{
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
    eval_stack[offset_m(ms, -2)].t = FLOAT;
    eval_stack[offset_m(ms, -2)].v.f = ans;
    eval_top = ms - 1;
}

void builtin_ddiv()
{
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
    eval_stack[offset_m(ms, -2)].t = FLOAT;
    eval_stack[offset_m(ms, -2)].v.f = ans;
    eval_top = ms - 1;
}

void builtin_less()
{
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
    eval_top = ms - 1;
}
void builtin_equal()
{
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
    eval_top = ms - 1;
}
void builtin_greater()
{
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
    eval_top = ms - 1;
}
void builtin_less_equal()
{
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
    eval_top = ms - 1;
}
void builtin_not_equal()
{
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
    eval_top = ms - 1;
}
void builtin_greater_equal()
{
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
    eval_top = ms - 1;
}

void builtin_rand()
{
    i64 ms = milestone();
    if (!read_rparen())
        parse_err(neta_type2string(RPAREN), neta_type2string(get_next_parse().t));
    eval_stack[ms - 2].t = INTEGER;
    eval_stack[ms - 2].v.i = rand();
    reset(ms - 2);
}