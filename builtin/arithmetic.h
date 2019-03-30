#ifndef _ARITHMETIC_H_
#define _ARITHMETIC_H_

#include <string.h>
#include "../lexer.h"
#include "../debug.h"
#include "../eval.h"
#include "../util.h"
#include "../custom/table.h"

void builtin_plus();
void builtin_minus();
void builtin_mul();
void builtin_div();

#endif