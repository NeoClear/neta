#include "if.h"
#include "../nlib.h"
#include "../eval.h"
#include "../err.h"

enum return_type builtin_if()
{
    i64 ms = milestone();
    i64 ptr_j = look_ahead();
    enum return_type t;
    eval_errh()
    // Read condition
    if (get_current_eval().t == INTEGER) {
        if (get_current_eval().v.i == 0) {
            // True
            ignore_exp();
            t = eval();
        } else {
            // False
            t = eval();
            ignore_exp();
        }
        // Place answer
        eval_stack[ms - 2] = eval_stack[ms + 1];
    } else
        runtime_errh(neta_type2string(INTEGER), neta_type2string(get_current_eval().t))
    // Read close paren
    if (!read_rparen())
        parse_errh(neta_type2string(RPAREN), neta_type2string(get_next_parse().t))
    // Reset eval stack
    reset(ms - 2);
    return t;
}