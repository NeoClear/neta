#ifndef _NLIB_H_
#define _NLIB_H_

#include "def.h"
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

boolean is_plus(char *s);
boolean is_minus(char *s);
boolean is_mul(char *s);
boolean is_div(char *s);
boolean is_dplus(char *s);
boolean is_dminus(char *s);
boolean is_dmul(char *s);
boolean is_ddiv(char *s);
boolean is_def(char *s);
boolean is_undef(char *s);
boolean is_range(char *s);
boolean is_setf(char *s);
boolean is_setc(char *s);
boolean is_prog(char *s);

i64 milestone();
i64 offset(i64 off);
i64 offset_m(i64 milestone, i64 off);
void eval_copy(i64 dest, i64 src);
void copy_reset(i64 dest, i64 src);

char *neta_type2string(enum neta_type t);
struct neta_node num2float(struct neta_node n);
struct neta_node num2int(struct neta_node n);

#endif