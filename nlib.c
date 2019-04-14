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

boolean is_less(char *s)
{
    if (strcmp(s, "<") == 0)
        return true;
    return false;
}

boolean is_equal(char *s)
{
    if (strcmp(s, "=") == 0)
        return true;
    return false;
}
boolean is_greater(char *s)
{
    if (strcmp(s, ">") == 0)
        return true;
    return false;
}
boolean is_less_equal(char *s)
{
    if (strcmp(s, "<=") == 0)
        return true;
    return false;
}
boolean is_not_equal(char *s)
{
    if (strcmp(s, "!=") == 0)
        return true;
    return false;
}
boolean is_greater_equal(char *s)
{
    if (strcmp(s, ">=") == 0)
        return true;
    return false;
}

boolean is_rand(char *s)
{
    if (strcmp(s, "rand") == 0)
        return true;
    return false;
}

boolean is_fun(char *s)
{
    if (strcmp(s, "fun") == 0)
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

boolean is_setl(char *s)
{
    if (strcmp(s, "setl") == 0)
        return true;
    return false;
}

boolean is_prog(char *s)
{
    if (strcmp(s, "prog") == 0 || strcmp(s, "!") == 0)
        return true;
    return false;
}

boolean is_if(char *s)
{
    if (strcmp(s, "if") == 0)
        return true;
    return false;
}

boolean is_while(char *s)
{
    if (strcmp(s, "while") == 0)
        return true;
    return false;
}

boolean is_assign(char *s)
{
    if (strcmp(s, "->") == 0 || strcmp(s, "assign") == 0)
        return true;
    return false;
}

boolean is_import(char *s)
{
    if (strcmp(s, "import") == 0)
        return true;
    return false;
}

boolean is_type(char *s)
{
    if (strcmp(s, "type") == 0)
        return true;
    return false;
}

boolean is_istype(char *s)
{
    if (strcmp(s, "istype") == 0)
        return true;
    return false;
}

boolean is_equal_val(char *s)
{
    if (strcmp(s, "equal") == 0)
        return true;
    return false;
}

boolean is_parse(char *s)
{
    if (strcmp(s, "parse") == 0)
        return true;
    return false;
}

boolean is_print(char *s)
{
    if (strcmp(s, "print") == 0)
        return true;
    return false;
}

boolean is_println(char *s)
{
    if (strcmp(s, "println") == 0)
        return true;
    return false;
}

boolean is_read(char *s)
{
    if (strcmp(s, "read") == 0)
        return true;
    return false;
}
boolean is_readln(char *s)
{
    if (strcmp(s, "readln") == 0)
        return true;
    return false;
}

boolean is_strlen(char *s)
{
    if (strcmp(s, "strlen") == 0)
        return true;
    return false;
}
boolean is_strcmp(char *s)
{
    if (strcmp(s, "strcmp") == 0)
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

boolean read_symbol()
{
    if (get_next_parse().t == SYMBOL) {
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

void reset(i64 start)
{
    eval_top = start + 1;
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
    case SYMBOL:
        return "CHAR";
    default:
        runtime_err("neta_type", "integer out of range");
    }
}

char *neta_node2string(struct neta_node n)
{
    char *s = (char *)malloc(sizeof(char) * inf24);
    switch (n.t)
    {
    case INTEGER:
        sprintf(s, "%lld", n.v.i);
        break;
    case FLOAT:
        sprintf(s, "%lf", n.v.f);
        break;
    case STRING:
        sprintf(s, "%s", n.v.s);
        break;
    case CHAR:
        sprintf(s, "%c", n.v.c);
        break;
    case SYMBOL:
        sprintf(s, "%s", n.v.s);
        break;
    case LPAREN:
        sprintf(s, "(");
        break;
    case RPAREN:
        sprintf(s, ")");
        break;
    case PRESERVED_FUN:
        sprintf(s, "%s", n.v.s);
        break;
    case IDENTIFIER:
        sprintf(s, "%s", n.v.s);
        break;
    default:
        runtime_err("neta_node", neta_type2string(n.t));
        break;
    }
    char *ret = (char *)malloc(sizeof(char) * (strlen(s) + 1));
    strcpy(ret, s);
    free(s);
    return ret;
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

void ignore_exp()
{
    i64 level = 0;
    do {
        enum neta_type t = parse_tree[ptr++].t;
        if (t == LPAREN)
            level++;
        else if (t == RPAREN)
            level--;
    } while (level);
    if (level < 0)
        parse_err("expression", neta_type2string(RPAREN));
}