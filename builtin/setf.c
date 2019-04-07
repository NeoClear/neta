#include "setf.h"
#include "../debug.h"

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
    search_gvnode(glov, name)->gt = VARIABLE;
}

// The integrated function which handles the creation and initialization of a global variable
void initialize_variable()
{
    i64 milestone = eval_top;
    read_identifier();
    eval();
    add_global_variable(eval_stack[milestone].v.s, eval_stack[milestone + 1]);
    if (!read_rparen())
        printf("FUCK IT\n");
}

// The builtin setf function
void builtin_setf()
{
    i64 milestone = eval_top;
    while (!read_rparen()) {
        if (read_lparen()) {
            initialize_variable();
            continue;
        } else if (read_identifier()) {
            create_global_variable(get_current_eval().v.s);
            continue;
        } else {
            ps("At builtin_setf()\n");
        }
    }
    eval_top = milestone - 1;
}