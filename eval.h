#ifndef _EVAL_H_
#define _EVAL_H_

#include <string.h>
#include "lexer.h"
#include "debug.h"

extern struct neta_node eval_stack[inf];
extern i64 eval_top;

void eval();

#endif