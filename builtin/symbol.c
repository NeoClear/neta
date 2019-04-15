#include "symbol.h"
#include "../err.h"
#include "../debug.h"

boolean find_symbol(struct neta_node **node, char *name)
{
    struct neta_node *ret = nil;
    if (find_variable(&ret, name)) {
        *node = ret;
        return true;
    }
    return false;
}

boolean find_variable(struct neta_node **node, char *name)
{
    struct neta_node *ret = nil;
    
    if (find_local_variable(&ret, name)) {
        *node = ret;
        return true;
    }
    if (find_global_variable(&ret, name)) {
        *node = ret;
        return true;
    }
    return false;
}

boolean find_global_variable(struct neta_node **node, char *name)
{
    if (glov == nil || search_gvnode(glov, name) == nil || search_gvnode(glov, name)->gt != VARIABLE)
        return false;
    *node = search_gvnode(glov, name)->value;
    return true;
}

boolean find_local_variable(struct neta_node **node, char *name)
{
    for (i64 it = eval_top - 1; it >= 0; it--) {
        if (eval_stack[it].t == VALUE && eval_stack[it].gt == VARIABLE && strcmp(eval_stack[it].v.s, name) == 0) {
            *node = eval_stack[it].p;
            return true;
        }
    }
    return false;
}

boolean find_global_constant(struct neta_node **node, char *name)
{
    if (glov == nil || search_gvnode(glov, name) == nil || search_gvnode(glov, name)->gt != CONSTANT)
        return false;
    *node = search_gvnode(glov, name)->value;
    return true;
}