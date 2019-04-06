#include "nlib.h"

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