#include "fun.h"
#include "../nlib.h"
#include "../err.h"
#include "../debug.h"

void read_fun_body(struct neta_node *head)
{
    struct neta_node *p, *q;
    if (!read_lparen())
        parse_err(neta_type2string(LPAREN), neta_type2string(get_next_parse().t));
    head->p = (struct neta_node *)malloc(sizeof(struct neta_node));
    p = head->p;
    *p = get_current_eval();
    p->next = nil;
    q = p;
    while (!read_rparen()) {
        if (!read_identifier())
            parse_err(neta_type2string(IDENTIFIER), neta_type2string(get_next_parse().t));
        p = (struct neta_node *)malloc(sizeof(struct neta_node));
        *p = get_current_eval();
        p->next = nil;
        q->next = p;
        q = p;
    }
    p = (struct neta_node *)malloc(sizeof(struct neta_node));
    *p = get_current_eval();
    p->next = nil;
    q->next = p;
    q = p;

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
        parse_err("expression", neta_type2string(RPAREN));

}

void builtin_fun()
{
    i64 ms = milestone();
    if (!read_identifier())
        parse_err(neta_type2string(IDENTIFIER), neta_type2string(get_next_parse().t));
    char *name = get_current_eval().v.s;
    glov = gvinsert(glov, name);
    search_gvnode(glov, name)->value = (struct neta_node *)malloc(sizeof(struct neta_node));
    search_gvnode(glov, name)->gt = FUNCTION;
    search_gvnode(glov, name)->value->p = nil;
    search_gvnode(glov, name)->value->gt = LIST;
    read_fun_body(search_gvnode(glov, name)->value);
    if (!read_rparen())
        parse_err(neta_type2string(RPAREN), neta_type2string(get_next_parse().t));
    reset(ms - 2);
}