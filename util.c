#include "util.h"

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