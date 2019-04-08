#include "setf.h"
#include "../debug.h"
#include "../err.h"

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
    i64 milestone = eval_top;
    read_identifier();
    eval();
    add_global_constant(eval_stack[milestone].v.s, eval_stack[milestone + 1]);
    if (!read_rparen())
        parse_err(neta_type2string(RPAREN), neta_type2string(get_next_parse().t));
}

// The builtin setc function
void builtin_setc()
{
    i64 milestone = eval_top;
    while (!read_rparen()) {
        if (read_lparen()) {
            initialize_global_constant();
            continue;
        } else if (read_identifier()) {
            create_global_constant(get_current_eval().v.s);
            continue;
        } else {
            err("At builtin_setc()\n");
        }
    }
    eval_top = milestone - 1;
}