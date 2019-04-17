#include "setf.h"
#include "../debug.h"
#include "../err.h"
#include "../nlib.h"
#include "../data.h"
#include <stdlib.h>

// Create a global constant and initialize it
void add_global_constant(char *name, struct neta_node value)
{
    glov = gvinsert(glov, name);
    search_gvnode(glov, name)->value = (struct neta_node *)malloc(sizeof(struct neta_node));
    search_gvnode(glov, name)->gt = CONSTANT;
    memcpy(search_gvnode(glov, name)->value, &value, sizeof(struct neta_node));
}

// Create a global constant without initialization
void create_global_constant(char *name)
{
    glov = gvinsert(glov, name);
    search_gvnode(glov, name)->value = (struct neta_node *)malloc(sizeof(struct neta_node));
    search_gvnode(glov, name)->gt = CONSTANT;
}

// The integrated function which handles the creation and initialization of a global constant
void initialize_global_constant()
{
    i64 ms = milestone();;
    read_identifier();
    eval();
    if (is_err)
        return;
    add_global_constant(eval_stack[ms].v.s, eval_stack[ms + 1]);
    if (!read_rparen())
        parse_errh(neta_type2string(RPAREN), neta_type2string(get_next_parse().t))
}

// The builtin setc function
enum return_type builtin_setc()
{
    i64 ms = milestone();
    // Read open paren
    while (!read_rparen()) {
        if (read_lparen()) {
            // Initialize constant with value
            initialize_global_constant();
            if (is_err)
                return NORMAL;
            continue;
        } else if (read_identifier()) {
            // Create constant without value
            create_global_constant(get_current_eval().v.s);
            continue;
        } else {
            errh("At builtin_setc()\n")
        }
    }
    eval_stack[ms - 2] = default_return;
    reset(ms - 2);
    return NORMAL;
}