#ifndef _SYMBOL_H_
#define _SYMBOL_H_

#include "../data.h"
#include "../def.h"

boolean find_symbol(struct neta_node **node, char *name);
boolean find_variable(struct neta_node **node, char *name);
boolean find_global_variable(struct neta_node **node, char *name);
boolean find_local_variable(struct neta_node **node, char *name);

#endif