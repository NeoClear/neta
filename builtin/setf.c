#include "setf.h"
#include "../debug.h"
#include "../err.h"
#include "../nlib.h"
#include <stdlib.h>

// Create a global variable and initialize it
void add_global_variable(char *name, struct neta_node value)
{
    glov = gvinsert(glov, name);
    search_gvnode(glov, name)->value = (struct neta_node *)malloc(sizeof(struct neta_node));
    search_gvnode(glov, name)->gt = VARIABLE;
    memcpy(search_gvnode(glov, name)->value, &value, sizeof(struct neta_node));
}

// Create a global variable without initialization
void create_global_variable(char *name)
{
    glov = gvinsert(glov, name);
    search_gvnode(glov, name)->value = (struct neta_node *)malloc(sizeof(struct neta_node));
    search_gvnode(glov, name)->gt = VARIABLE;
}

// The integrated function which handles the creation and initialization of a global variable
void initialize_global_variable()
{
    i64 ms = milestone();
    read_identifier();
    eval();
    if (is_err)
        return;
    add_global_variable(eval_stack[ms].v.s, eval_stack[ms + 1]);
    if (!read_rparen())
        parse_errh(neta_type2string(RPAREN), neta_type2string(get_next_parse().t))
}

// The builtin setf function
enum return_type builtin_setf()
{
    i64 ms = milestone();
    // Read open paren
    while (!read_rparen()) {
        if (read_lparen()) {
            // Initialize variable with value
            initialize_global_variable();
            if (is_err)
                return;
            continue;
        } else if (read_identifier()) {
            // Create variable without value
            create_global_variable(get_current_eval().v.s);
            continue;
        } else {
            errh("At builtin_setf()\n")
        }
    }
    eval_stack[ms - 2] = default_return;
    reset(ms - 2);
    return NORMAL;
}