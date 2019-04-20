#include "assign.h"
#include "../eval.h"
#include "../nlib.h"
#include "symbol.h"
#include "../err.h"
#include "../debug.h"

void sub_assign()
{
    // Read open paren
    if (!read_lparen()) {
        parse_err(neta_type2string(LPAREN), neta_type2string(get_next_parse().t));
        if (is_err)
            return;
    }
    // Read identifier
    if (!read_identifier()) {
        parse_err(neta_type2string(IDENTIFIER), neta_type2string(get_next_parse().t));
        if (is_err)
            return;
    }
    struct neta_node *ret = nil;
    // Try to find variable
    if (find_variable(&ret, get_current_eval().v.s)) {
        if (ret == nil) {
            err("null variables");
            if (is_err)
                return;
        }
        eval();
        if (is_err)
            return;
        *ret = get_current_eval();
    } else {
        // err("could not find variable");
        if (is_err)
            return;
    }
    // Read close paren
    if (!read_rparen()) {
        parse_err(neta_type2string(RPAREN), neta_type2string(get_next_parse().t));
        if (is_err)
            return;
    }
}

enum return_type builtin_assign()
{
    // print_parse_tree();
    i64 ms = milestone();
    // Deal with groups of assignment until meets a close paren
    while (!read_rparen()) {
        sub_assign();
        if (is_err)
            return NORMAL;
    }
    eval_stack[ms - 2] = default_return;
    reset(ms - 2);
    return NORMAL;
}