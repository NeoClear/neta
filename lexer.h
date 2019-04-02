/*
 * lexer.h contains:
 * functions for exporting metadata in lexical analysis to tokens
 * used by flex
 */
#ifndef _LEXER_H_
#define _LEXER_H_

#include "io.h"
#include "data.h"

// Exporting metadata to tokens
boolean add_lparen();
boolean add_rparen();
boolean add_float(f64 f);
boolean add_integer(i64 i);
boolean add_string(char *s);
boolean add_char(char c);
boolean add_preserved_fun(char *s);
boolean add_identifier(char *s);

#endif