#include "while.h"
#include "../eval.h"
#include "../err.h"
#include "../data.h"
#include "../nlib.h"

void builtin_while()
{
    i64 backtrace = ptr;
    i64 ms = milestone();
    
    // Reset the starting point
    eval_stack[ms - 2].t = INTEGER;
    eval_stack[ms - 2].v.i = 0;

    boolean once = false;
    while (true) {
        eval();
        if (get_current_eval().t != INTEGER)
            runtime_err(neta_type2string(INTEGER), neta_type2string(get_current_eval().t));
        if (get_current_eval().v.i == 0)
            break;
        else {
            eval();
            eval_stack[ms - 2] = get_current_eval();
            ptr = backtrace;
            eval_top -= 2;
            neta_err();
        }
    }
    ignore_exp();
    if (!read_rparen())
        parse_err(neta_type2string(RPAREN), neta_type2string(get_next_parse().t));
    reset(ms - 2);
}