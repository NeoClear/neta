#ifndef _SETF_H_
#define _SETF_H_

#include "../lexer.h"
#include "../debug.h"
#include "../eval.h"
#include "../data.h"


void builtin_setf();
void add_global_variable(char *name, struct neta_node value);

#endif