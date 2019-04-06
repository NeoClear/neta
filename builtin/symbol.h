#ifndef _SYMBOL_H_
#define _SYMBOL_H_

#include "../data.h"
#include "../def.h"

struct neta_node *find_symbol(char *name);
boolean find_global_variable(struct neta_node **node, char *name);

#endif