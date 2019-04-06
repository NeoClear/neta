#include "symbol.h"
#include "../err.h"

struct neta_node *find_symbol(char *name)
{
    struct neta_node *ret = nil;
    if (find_global_variable(&ret, name))
        return ret;
    // Abolished later
    err("SHIT");
    return ret;
}

boolean find_global_variable(struct neta_node **node, char *name)
{
    if (search_gvnode(glov, name) == nil)
        return false;
    *node = search_gvnode(glov, name)->value;
    return true;
}