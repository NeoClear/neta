#include "symbol.h"
#include "../err.h"

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
    if (find_global_variable(&ret, name)) {
        *node = ret;
        return true;
    }
    return false;
}

boolean find_global_variable(struct neta_node **node, char *name)
{
    if (search_gvnode(glov, name) == nil || search_gvnode(glov, name)->gt != VARIABLE)
        return false;
    *node = search_gvnode(glov, name)->value;
    return true;
}