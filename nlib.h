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

// Preserved arithmetical functions???
boolean is_plus(char *s);
boolean is_minus(char *s);
boolean is_mul(char *s);
boolean is_div(char *s);
boolean is_dplus(char *s);
boolean is_dminus(char *s);
boolean is_dmul(char *s);
boolean is_ddiv(char *s);

// Preserved conpare functions???
boolean is_less(char *s);
boolean is_equal(char *s);
boolean is_greater(char *s);
boolean is_less_equal(char *s);
boolean is_not_equal(char *s);
boolean is_greater_equal(char *s);

// Keywords???
boolean is_def(char *s);
boolean is_undef(char *s);
boolean is_range(char *s);
boolean is_setf(char *s);
boolean is_setc(char *s);
boolean is_prog(char *s);
boolean is_if(char *s);

// Preserved io funcitons???
boolean is_print(char *s);
boolean is_println(char *s);

// Preserved string functions???
boolean is_strlen(char *s);
boolean is_strcmp(char *s);

i64 milestone();
i64 offset(i64 off);
i64 offset_m(i64 milestone, i64 off);
void eval_copy(i64 dest, i64 src);
void copy_reset(i64 dest, i64 src);
void reset(i64 start);

char *neta_type2string(enum neta_type t);
char *neta_node2string(struct neta_node n);
struct neta_node num2float(struct neta_node n);
struct neta_node num2int(struct neta_node n);

void ignore_exp();

#endif