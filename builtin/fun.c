#include "fun.h"
#include "../nlib.h"
#include "../err.h"
#include "../debug.h"
#include <stdlib.h>

void read_fun_body(struct neta_node *head)
{
    struct neta_node *p, *q;
    // Read open paren of param list
    if (!read_lparen())
        parse_errh(neta_type2string(LPAREN), neta_type2string(get_next_parse().t))
    head->p = (struct neta_node *)malloc(sizeof(struct neta_node));
    p = head->p;
    *p = get_current_eval();
    p->next = nil;
    q = p;
    // Read content of param list
    while (!read_rparen()) {
        if (!read_identifier())
            parse_errh(neta_type2string(IDENTIFIER), neta_type2string(get_next_parse().t))
        p = (struct neta_node *)malloc(sizeof(struct neta_node));
        *p = get_current_eval();
        p->next = nil;
        q->next = p;
        q = p;
    }
    // Read close paren
    p = (struct neta_node *)malloc(sizeof(struct neta_node));
    *p = get_current_eval();
    p->next = nil;
    q->next = p;
    q = p;
    // Read function body
    i64 level = 0;
    do {
        parse_to_eval();
        p = (struct neta_node *)malloc(sizeof(struct neta_node));
        *p = get_current_eval();
        p->next = nil;
        q->next = p;
        q = p;

        if (get_current_eval().t == LPAREN)
            level++;
        else if (get_current_eval().t == RPAREN)
            level--;
    } while (level);
    if (level < 0)
        parse_errh("expression", neta_type2string(RPAREN))

}

enum return_type builtin_fun()
{
    i64 ms = milestone();
    // Read function name
    if (!read_identifier())
        parse_errh(neta_type2string(IDENTIFIER), neta_type2string(get_next_parse().t))
    char *name = get_current_eval().v.s;
    // Create a global node for function
    glov = gvinsert(glov, name);
    search_gvnode(glov, name)->value = (struct neta_node *)malloc(sizeof(struct neta_node));
    search_gvnode(glov, name)->gt = FUNCTION;
    search_gvnode(glov, name)->value->p = nil;
    search_gvnode(glov, name)->value->gt = LIST;
    // Read function param list and function body
    read_fun_body(search_gvnode(glov, name)->value);
    // Read close paren
    if (!read_rparen())
        parse_errh(neta_type2string(RPAREN), neta_type2string(get_next_parse().t))
    eval_stack[ms - 2] = default_return;
    reset(ms - 2);
    return NORMAL;
}

enum return_type builtin_def_yet()
{
    i64 ms = milestone();
    if (!read_identifier())
        runtime_errh(neta_type2string(IDENTIFIER), neta_type2string(get_next_parse().t));

    eval_stack[ms - 2].t = INTEGER;
    if (glov != nil && search_gvnode(glov, get_current_eval().v.s) != nil) {
        eval_stack[ms - 2].v.i = 1;
    } else
        eval_stack[ms - 2].v.i = 0;

    if (!read_rparen())
        parse_errh(neta_type2string(RPAREN), neta_type2string(get_next_parse().t));
    reset(ms - 2);
    return NORMAL;
}