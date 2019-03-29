#ifndef _DEBUG_H_
#define _DEBUG_H_

#include "lexer.h"
#include "eval.h"

void print_parse_tree();
void print_eval_stack();
void neta_err();
void pi(i64 i);
void ps(char *s);
void pf(f64 f);

#endif