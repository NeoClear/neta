/*
 * debug.h contains:
 * functions which make debuging easier
 */

#ifndef _DEBUG_H_
#define _DEBUG_H_

#include "lexer.h"
#include "eval.h"
#include "data.h"

// Print the parse tree

// Further notes should be made here
void print_parse_tree();
void print_eval_stack();
void print_global_variable();
void print_function(char *s);
void neta_err();
void pi(i64 i);
void ps(char *s);
void pf(f64 f);

#endif