#include "nlib.h"
#include "err.h"

boolean is_plus(char *s)
{
    if (strcmp(s, "+") == 0)
        return true;
    return false;
}

boolean is_minus(char *s)
{
    if (strcmp(s, "-") == 0)
        return true;
    return false;
}

boolean is_mul(char *s)
{
    if (strcmp(s, "*") == 0)
        return true;
    return false;
}

boolean is_div(char *s)
{
    if (strcmp(s, "/") == 0)
        return true;
    return false;
}

boolean is_dplus(char *s)
{
    if (strcmp(s, "d+") == 0)
        return true;
    return false;
}
boolean is_dminus(char *s)
{
    if (strcmp(s, "d-") == 0)
        return true;
    return false;
}
boolean is_dmul(char *s)
{
    if (strcmp(s, "d*") == 0)
        return true;
    return false;
}
boolean is_ddiv(char *s)
{
    if (strcmp(s, "d/") == 0)
        return true;
    return false;
}

boolean is_def(char *s)
{
    if (strcmp(s, "def") == 0)
        return true;
    return false;
}

boolean is_undef(char *s)
{
    if (strcmp(s, "undef") == 0)
        return true;
    return false;
}

boolean is_range(char *s)
{
    if (strcmp(s, "..") == 0)
        return true;
    return false;
}

boolean is_setf(char *s)
{
    if (strcmp(s, "setf") == 0)
        return true;
    return false;
}

boolean is_setc(char *s)
{
    if (strcmp(s, "setc") == 0)
        return true;
    return false;
}

boolean is_prog(char *s)
{
    if (strcmp(s, "prog") == 0 || strcmp(s, "!") == 0)
        return true;
    return false;
}

struct neta_node get_next_parse()
{
    return parse_tree[ptr];
}

boolean parse_finished()
{
    if (ptr < parse_top)
        return false;
    return true;
}

void parse_to_eval()
{
    eval_stack[eval_top++] = parse_tree[ptr++];
}

struct neta_node get_current_eval()
{
    return eval_stack[eval_top - 1];
}

boolean read_lparen()
{
    if (get_next_parse().t == LPAREN) {
        parse_to_eval();
        return true;
    }
    return false;
}
boolean read_rparen()
{
    if (get_next_parse().t == RPAREN) {
        parse_to_eval();
        return true;
    }
    return false;
}
boolean read_identifier()
{
    if (get_next_parse().t == IDENTIFIER) {
        parse_to_eval();
        return true;
    }
    return false;
}
boolean read_preserved_fun()
{
    if (get_next_parse().t == PRESERVED_FUN) {
        parse_to_eval();
        return true;
    }
    return false;
}

boolean read_integer()
{
    if (get_next_parse().t == INTEGER) {
        parse_to_eval();
        return true;
    }
    return false;
}

boolean read_float()
{
    if (get_next_parse().t == FLOAT) {
        parse_to_eval();
        return true;
    }
    return false;
}

boolean read_string()
{
    if (get_next_parse().t == STRING) {
        parse_to_eval();
        return true;
    }
    return false;
}

boolean read_char()
{
    if (get_next_parse().t == CHAR) {
        parse_to_eval();
        return true;
    }
    return false;
}

i64 milestone()
{
    return eval_top;
}

i64 offset(i64 off)
{
    return eval_top + off;
}

i64 offset_m(i64 milestone, i64 off)
{
    return milestone + off;
}

void eval_copy(i64 dest, i64 src)
{
    eval_stack[dest] = eval_stack[src];
}

void copy_reset(i64 dest, i64 src)
{
    eval_copy(dest, src);
    eval_top = dest + 1;
}

char *neta_type2string(enum neta_type t)
{
    switch (t) {
    case LPAREN:
        return "LPAREN";
    case RPAREN:
        return "RPAREN";
    case PRESERVED_FUN:
        return "PRESERVED_FUN";
    case IDENTIFIER:
        return "IDENTIFIER";
    case INTEGER:
        return "INTEGER";
    case FLOAT:
        return "FLOAT";
    case STRING:
        return "STRING";
    case CHAR:
        return "CHAR";
    case LIST:
        return "LIST";
    default:
        runtime_err("neta_type", "integer out of range");
    }
}

struct neta_node num2float(struct neta_node n)
{
    switch (n.t)
    {
    case INTEGER:
        n.t = FLOAT;
        n.v.f = (f64)n.v.i;
        return n;
    case FLOAT:
        return n;
    default:
        runtime_err("Number", neta_type2string(n.t));
        return n;
    }
}
struct neta_node num2int(struct neta_node n)
{
    switch (n.t)
    {
    case INTEGER:
        return n;
    case FLOAT:
        n.t = INTEGER;
        n.v.i = (i64)n.v.f;
        return n;
    default:
        runtime_err("Number", neta_type2string(n.t));
        return n;
    }
}