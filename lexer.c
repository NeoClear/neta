#include "lexer.h"

struct neta_node parse_tree[inf];
i64 parse_top = 0;

boolean add_lparen()
{
    parse_tree[parse_top++].t = LPAREN;
    return true;
}

boolean add_rparen()
{
    parse_tree[parse_top++].t = RPAREN;
    return true;
}

boolean add_integer(i64 i)
{
    parse_tree[parse_top].t = INTEGER;
    parse_tree[parse_top++].v.i = i;
    return true;
}

boolean add_float(f64 f)
{
    parse_tree[parse_top].t = FLOAT;
    parse_tree[parse_top++].v.f = f;
    return true;
}

boolean add_string(char *s)
{
    parse_tree[parse_top].t = STRING;
    parse_tree[parse_top++].v.s = s;
    return true;
}

boolean add_char(char c)
{
    parse_tree[parse_top].t = CHAR;
    parse_tree[parse_top++].v.c = c;
    return true;
}

boolean add_preserved_fun(char *s)
{
    parse_tree[parse_top].t = PRESERVED_FUN;
    parse_tree[parse_top++].v.s = s;
    return true;
}

boolean add_identifier(char *s)
{
    parse_tree[parse_top].t = IDENTIFIER;
    parse_tree[parse_top++].v.s = s;
    return true;
}
