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

#endif