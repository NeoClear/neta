#ifndef _SETF_H_
#define _SETF_H_

#include "../data.h"

// Builtin setf function
enum return_type builtin_setf();
void add_global_variable(char *name, struct neta_node value);

#endif