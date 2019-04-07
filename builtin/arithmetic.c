#include "arithmetic.h"
#include "../debug.h"
#include "../util.h"
#include "../data.h"
#include "../err.h"

void builtin_plus()
{
    i64 ms = milestone();
    i64 ans = 0;
    while (!read_rparen()) {
        eval();
    }
    for (i64 i = ms; i <= offset(-2); i++) {
        eval_stack[i] = num2int(eval_stack[i]);
        ans += eval_stack[i].v.i;
    }
    eval_stack[offset_m(ms, -2)].t = INTEGER;
    eval_stack[offset_m(ms, -2)].v.i = ans;
    eval_top = ms - 1;
}

void builtin_minus()
{
    i64 ms = milestone();
    i64 ans = 0;
    while (!read_rparen()) {
        eval();
    }
    ans = num2int(eval_stack[ms]).v.i;
    for (i64 i = ms + 1; i <= offset(-2); i++) {
        eval_stack[i] = num2int(eval_stack[i]);
        ans -= eval_stack[i].v.i;
    }
    eval_stack[offset_m(ms, -2)].t = INTEGER;
    eval_stack[offset_m(ms, -2)].v.i = ans;
    eval_top = ms - 1;
}

void builtin_mul()
{
    i64 ms = milestone();
    i64 ans = 1;
    while (!read_rparen()) {
        eval();
    }
    for (i64 i = ms; i <= offset(-2); i++) {
        eval_stack[i] = num2int(eval_stack[i]);
        ans *= eval_stack[i].v.i;
    }
    eval_stack[offset_m(ms, -2)].t = INTEGER;
    eval_stack[offset_m(ms, -2)].v.i = ans;
    eval_top = ms - 1;
}

void builtin_div()
{
    i64 ms = milestone();
    i64 ans = 0;
    while (!read_rparen()) {
        eval();
    }
    ans = num2int(eval_stack[ms]).v.i;
    for (i64 i = ms + 1; i <= offset(-2); i++) {
        eval_stack[i] = num2int(eval_stack[i]);
        if (eval_stack[i].v.i != 0)
            ans /= eval_stack[i].v.i;
        else
            runtime_err("none zero", "zero");
    }
    eval_stack[offset_m(ms, -2)].t = INTEGER;
    eval_stack[offset_m(ms, -2)].v.i = ans;
    eval_top = ms - 1;
}

void builtin_dplus()
{
    i64 ms = milestone();
    f64 ans = 0;
    while (!read_rparen()) {
        eval();
    }
    for (i64 i = ms; i <= offset(-2); i++) {
        eval_stack[i] = num2float(eval_stack[i]);
        ans += eval_stack[i].v.f;
    }
    eval_stack[offset_m(ms, -2)].t = FLOAT;
    eval_stack[offset_m(ms, -2)].v.f = ans;
    eval_top = ms - 1;
}

void builtin_dminus()
{
    i64 ms = milestone();
    f64 ans = 0;
    while (!read_rparen()) {
        eval();
    }
    ans = num2float(eval_stack[ms]).v.f;
    for (i64 i = ms + 1; i <= offset(-2); i++) {
        eval_stack[i] = num2float(eval_stack[i]);
        ans -= eval_stack[i].v.f;
    }
    eval_stack[offset_m(ms, -2)].t = FLOAT;
    eval_stack[offset_m(ms, -2)].v.f = ans;
    eval_top = ms - 1;
}

void builtin_dmul()
{
    i64 ms = milestone();
    f64 ans = 1;
    while (!read_rparen()) {
        eval();
    }
    for (i64 i = ms; i <= offset(-2); i++) {
        eval_stack[i] = num2float(eval_stack[i]);
        ans *= eval_stack[i].v.f;
    }
    eval_stack[offset_m(ms, -2)].t = FLOAT;
    eval_stack[offset_m(ms, -2)].v.f = ans;
    eval_top = ms - 1;
}

void builtin_ddiv()
{
    i64 ms = milestone();
    f64 ans = 0;
    while (!read_rparen()) {
        eval();
    }
    ans = num2float(eval_stack[ms]).v.f;
    for (i64 i = ms + 1; i <= offset(-2); i++) {
        eval_stack[i] = num2float(eval_stack[i]);
        if (eval_stack[i].v.f != 0)
            ans /= eval_stack[i].v.f;
        else
            runtime_err("none zero", "zero");
    }
    eval_stack[offset_m(ms, -2)].t = FLOAT;
    eval_stack[offset_m(ms, -2)].v.f = ans;
    eval_top = ms - 1;
}