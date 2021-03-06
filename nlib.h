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
boolean read_symbol();

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

// Preserved math funcs???
boolean is_rand(char *s);

// Keywords???
boolean is_fun(char *s);
boolean is_undef(char *s);
boolean is_range(char *s);
boolean is_setf(char *s);
boolean is_setc(char *s);
boolean is_setl(char *s);
boolean is_prog(char *s);
boolean is_if(char *s);
boolean is_while(char *s);
boolean is_assign(char *s);
boolean is_import(char *s);
boolean is_type(char *s);
boolean is_istype(char *s);
boolean is_equal_val(char *s);
boolean is_parse(char *s);
boolean is_eval(char *s);
boolean is_returnf(char *s);
boolean is_returnp(char *s);
boolean is_catch(char *s);
boolean is_throw(char *s);
boolean is_errmsg(char *s);
boolean is_def_yet(char *s);
boolean is_match(char *s);
boolean is_when(char *s);
boolean is_iff(char *s);
boolean is_break(char *s);
boolean is_continue(char *s);
boolean is_sym2id(char *s);
boolean is_str2sym(char *s);
boolean is_apply(char *s);
boolean is_listof(char *s);

// Preserved io funcitons???
boolean is_print(char *s);
boolean is_println(char *s);
boolean is_format(char *s);
boolean is_read(char *s);
boolean is_readln(char *s);

// Preserved string functions???
boolean is_strlen(char *s);
boolean is_strcmp(char *s);

boolean is_str2int(char *s);
boolean is_str2float(char *s);

boolean is_int2float(char *s);
boolean is_float2int(char *s);

i64 milestone();
i64 offset(i64 off);
i64 offset_m(i64 milestone, i64 off);
void eval_copy(i64 dest, i64 src);
void copy_reset(i64 dest, i64 src);
void reset(i64 start);

char *neta_type2string(enum neta_type t);
char *neta_node2string(struct neta_node n);
char *neta_node2string_f(struct neta_node n);
struct neta_node num2float(struct neta_node n);
struct neta_node num2int(struct neta_node n);

void ignore_exp();

i64 look_ahead();

boolean equal(struct neta_node a, struct neta_node b);

struct neta_node *new_neta_node();

#endif