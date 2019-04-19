/*
 * util.h contains:
 * useful functions about general solutions
 * look ahead functions(move to a new module)
 */
#ifndef _UTIL_H_
#define _UTIL_H_

#include "lexer.h"
#include "data.h"

i64 max(i64 a, i64 b);
i64 min(i64 a, i64 b);

boolean greater_s(char *a, char *b);
boolean eq_s(char *a, char *b);
boolean less_s(char *a, char *b);

extern char *buffer;

void set_buffer(char *s);

i64 read_i64();
f64 read_f64();

char *drop_shell(char *s);
char *clone(char *s);
char *drop_at(char *s);
char *add_at(char *s);

char *int2string(i64 i);
char *double2string(f64 f);

#endif
