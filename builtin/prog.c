#include "prog.h"
#include "../def.h"
#include "../data.h"
#include "../nlib.h"
#include "../eval.h"
#include "../err.h"
#include "../debug.h"

enum return_type builtin_prog()
{
    i64 ms = milestone();
    i64 ptr_j = look_ahead();
    // Eval all and place last one as answer
    while (!read_rparen()) {
        enum return_type t = eval();
        // printf("%d\n", t);
        if (t == PROG) {
            eval_stack[ms - 2] = get_current_eval();
            ptr = ptr_j;
            reset(ms - 2);
            return NORMAL;
        } else if (t == FUNC) {
            eval_stack[ms - 2] = get_current_eval();
            ptr = ptr_j;
            reset(ms - 2);
            return FUNC;
        }
    }
    copy_reset(offset_m(ms, -2), offset(-2));
    // eval_stack[ms - 2] = eval_stack[eval_top - 2];
    // eval_top = ms - 1;
    return NORMAL;
}

enum return_type builtin_returnp()
{
    i64 ms = milestone();
    eval_errh()
    eval_stack[ms - 2] = get_current_eval();
    if (!read_rparen())
        parse_errh(neta_type2string(RPAREN), neta_type2string(get_next_parse().t))
    reset(ms - 2);
    return NORMAL;
}