#include "while.h"
#include "../eval.h"
#include "../err.h"
#include "../data.h"
#include "../nlib.h"

enum return_type builtin_while()
{
    i64 trace = ptr;
    i64 ms = milestone();
    i64 ptr_j = look_ahead();
    // Reset the starting point
    eval_stack[ms - 2] = default_return;

    boolean once = false;

    enum return_type t = NORMAL;

    while (true) {
        eval();
        if (get_current_eval().t != INTEGER)
            runtime_err(neta_type2string(INTEGER), neta_type2string(get_current_eval().t));
        if (get_current_eval().v.i == 0)
            break;
        else {
            t = eval();
            eval_stack[ms - 2] = get_current_eval();
            if (t != NORMAL) {
                ptr = ptr_j;
                reset(ms - 2);
                return t;
            }
            // eval_stack[ms - 2] = get_current_eval();
            ptr = trace;
            eval_top -= 2;
        }
    }
    ignore_exp();
    if (!read_rparen())
        parse_err(neta_type2string(RPAREN), neta_type2string(get_next_parse().t));
    reset(ms - 2);
    return t;
}