#include "prog.h"
#include "../def.h"
#include "../data.h"
#include "../nlib.h"
#include "../eval.h"

void builtin_prog()
{
    i64 milestone = eval_top;
    while (!read_rparen()) {
        eval();
    }
    eval_stack[milestone - 2] = eval_stack[eval_top - 2];
    eval_top = milestone - 1;
}