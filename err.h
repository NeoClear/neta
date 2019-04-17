#ifndef _ERR_H_
#define _ERR_H_

#include "def.h"

// #define error_handle if (is_err) return

#define eval_errh() \
    eval(); \
    if (is_err) \
        return NORMAL;

#define errh(s) \
    err(s); \
    if (is_err) \
        return NORMAL;

#define parse_errh(a, b) \
    parse_err(a, b); \
    if (is_err) \
        return NORMAL;

#define runtime_errh(a, b) \
    runtime_err(a, b); \
    if (is_err) \
        return NORMAL;

#define code_incomplete_errh() \
    code_incomplete_err(); \
    if (is_err) \
        return;

enum error_type
{
    STRICT,
    PARSE,
    EVAL,
};

extern enum error_type error_mode;
extern boolean is_err;

// Standard errors
void err(char *s);
// Parsing errors
void parse_err(char *expect, char *encounter);
// Runtime errors
void runtime_err(char *expect, char *encounter);

void code_incomplete_err();

#endif