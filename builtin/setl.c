#include "setl.h"
#include "../nlib.h"
#include "../err.h"
#include "../eval.h"
#include <stdlib.h>

void add_local_variable(char *name, struct neta_node value)
{
    eval_stack[eval_top - 2].v.s = name;
    eval_stack[eval_top - 2].t = VALUE;
    eval_stack[eval_top - 2].gt = VARIABLE;
    eval_stack[eval_top - 2].p = (struct neta_node *)malloc(sizeof(struct neta_node));
    *eval_stack[eval_top - 2].p = value;
}

void create_local_variable(char *name)
{
    eval_stack[eval_top - 1].v.s = name;
    eval_stack[eval_top - 1].t = VALUE;
    eval_stack[eval_top - 1].gt = VARIABLE;
    eval_stack[eval_top - 1].p = (struct neta_node *)malloc(sizeof(struct neta_node));
}

void initialize_local_variable()
{
    if (!read_lparen())
        parse_err(neta_type2string(LPAREN), neta_type2string(get_next_parse().t));
    eval_top--;
    if (!read_identifier())
        parse_err(neta_type2string(IDENTIFIER), neta_type2string(get_next_parse().t));
    eval();
    add_local_variable(eval_stack[eval_top - 2].v.s, get_current_eval());
    eval_top--;
    if (!read_rparen())
        parse_err(neta_type2string(RPAREN), neta_type2string(get_next_parse().t));
    eval_top--;
}

void builtin_setl()
{
    eval_top -= 2;
    while (!read_rparen()) {
        if (read_identifier())
            create_local_variable(get_current_eval().v.s);
        else
            initialize_local_variable();
    }
    eval_top--;
}