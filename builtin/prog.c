#include "prog.h"
#include "../def.h"
#include "../data.h"
#include "../nlib.h"
#include "../eval.h"

void builtin_prog()
{
    i64 ms = milestone();
    // Eval all and place last one as answer
    while (!read_rparen()) {
        eval();
    }
    copy_reset(offset_m(ms, -2), offset(-2));
    // eval_stack[ms - 2] = eval_stack[eval_top - 2];
    // eval_top = ms - 1;
}