#include "if.h"
#include "../nlib.h"
#include "../eval.h"
#include "../err.h"

void builtin_if()
{
    i64 ms = milestone();
    eval();
    if (get_current_eval().t == INTEGER) {
        if (get_current_eval().v.i == 0) {
            ignore_exp();
            eval();
            // eval();
        } else {
            eval();
            ignore_exp();
            // eval();
        }
        // eval_copy(ms - 2, ms + 1);
        copy_reset(offset_m(ms, -2), offset_m(ms, 1));
    } else
        runtime_err(neta_type2string(INTEGER), neta_type2string(get_current_eval().t));
    if (!read_rparen())
        parse_err(neta_type2string(RPAREN), neta_type2string(get_next_parse().t));
}