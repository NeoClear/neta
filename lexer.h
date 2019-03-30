#ifndef _LEXER_H_
#define _LEXER_H_

#include "io.h"
#include "custom/table.h"

typedef unsigned char boolean;
#define true 1
#define false 0
#define inf 0xffffff

enum neta_type
{
    LPAREN,
    RPAREN,
    PRESERVED_FUN,
    IDENTIFIER,
    INTEGER,
    FLOAT,
    STRING,
    CHAR,
};
enum global_type
{
    function,
    variable,
    constant,
};

struct global_variable
{
    char *name;
    enum global_type gt;
    struct neta_node *value;
    boolean initialized;
};

extern struct global_variable glov[inf];
extern i64 glon;

struct neta_node;

union neta_value
{
    i64 i;
    f64 f;
    char *s;
    char c;
    struct neta_node *p;
};

struct neta_node
{
    enum neta_type t;
    enum global_type gt;
    union neta_value v;
};

extern struct neta_node parse_tree[inf];
extern i64 parse_top;

boolean add_lparen();
boolean add_rparen();
boolean add_float(f64 f);
boolean add_integer(i64 i);
boolean add_string(char *s);
boolean add_char(char c);
boolean add_preserved_fun(char *s);
boolean add_identifier(char *s);

#endif