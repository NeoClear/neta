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
#include "data.h"
#include "nlib.h"

// Main evaluation function
void eval();

#endif