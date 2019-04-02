/*
 * eval.h contains:
 * evaluation stack for the program(important!!!)
 * main evaluation function(important)
 */
#ifndef _EVAL_H_
#define _EVAL_H_

#include <string.h>
#include "lexer.h"
#include "debug.h"
#include "builtin/arithmetic.h"
#include "data.h"

// Evaluation stack
extern struct neta_node eval_stack[inf];
// Top of evaluation stack
extern i64 eval_top;
// The pointer to parse stack while evaluating
extern i64 ptr;

// Main evaluation function
void eval();

#endif