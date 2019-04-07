#include "assign.h"
#include "../eval.h"
#include "../nlib.h"
#include "symbol.h"
#include "../err.h"

void sub_assign()
{
    if (!read_lparen())
        parse_err(neta_type2string(LPAREN), neta_type2string(get_next_parse().t));
    if (!read_identifier())
        parse_err(neta_type2string(IDENTIFIER), neta_type2string(get_next_parse().t));
    struct neta_node *ret = nil;
    if (find_variable(&ret, get_current_eval().v.s)) {
        eval();
        *ret = get_current_eval();
    } else
        err("could not find variable");
    if (!read_rparen())
        parse_err(neta_type2string(RPAREN), neta_type2string(get_next_parse().t));
}

void builtin_assign()
{
    i64 ms = milestone();
    while (!read_rparen())
        sub_assign();
    reset(ms - 2);
}