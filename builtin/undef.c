#include "undef.h"
#include "../err.h"
#include "../data.h"
#include "../debug.h"
#include "../nlib.h"

void delete_global_value(char *name)
{
    if (glov == nil || search_gvnode(glov, name) == nil)
        err("value not found");
    glov = delete_gvnode(glov, name);
}

void builtin_undef()
{
    i64 ms = milestone();
    while (!read_rparen()) {
        if (!read_identifier())
            runtime_err(neta_type2string(IDENTIFIER), neta_type2string(get_next_parse().t));
        delete_global_value(get_current_eval().v.s);
    }
    reset(ms - 2);
}