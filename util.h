/*
 * util.h contains:
 * useful functions about general solutions
 * look ahead functions(move to a new module)
 */
#ifndef _UTIL_H_
#define _UTIL_H_

#include "eval.h"
#include "lexer.h"
#include "data.h"

struct neta_node get_next_parse();
struct neta_node get_current_eval();
boolean parse_finished();

void parse_to_eval();

boolean read_lparen();
boolean read_rparen();
boolean read_identifier();
boolean read_preserved_fun();
boolean read_integer();
boolean read_float();
boolean read_string();
boolean read_char();

i64 max(i64 a, i64 b);
i64 min(i64 a, i64 b);

boolean greater_s(char *a, char *b);
boolean eq_s(char *a, char *b);
boolean less_s(char *a, char *b);

#endif
