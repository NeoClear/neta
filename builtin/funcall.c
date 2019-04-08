#include "funcall.h"
#include "../eval.h"
#include "../err.h"
#include "../nlib.h"
#include "../data.h"

void copy_fun(struct neta_node *it)
{
    while (it != nil) {
        parse_tree[parse_top++] = *it;
        it = it->next;
    }
}

void read_fun_param()
{

}

void builtin_funcall(char *fn)
{
    struct neta_node *tp = search_gvnode(glov, fn)->value->p;
    i64 ms = milestone();
    i64 ptr_m = ptr;
    i64 parse_top_m = parse_top;
    while (get_next_parse().t != RPAREN) {
        eval();
    }
    ptr_m = ptr + 1;
    if (tp->t != LPAREN)
        err("SHIT");
    tp = tp->next;
    for (i64 it = ms; it < eval_top; it++) {
        struct neta_node *v = (struct neta_node *)malloc(sizeof(struct neta_node));
        *v = eval_stack[it];
        eval_stack[it] = *tp;
        eval_stack[it].t = VALUE;
        eval_stack[it].gt = VARIABLE;
        eval_stack[it].p = v;
        tp = tp->next;
    }
    if (tp->t != RPAREN)
        err("FUCK");
    tp = tp->next;
    ptr = parse_top;
    copy_fun(tp);
    eval();
    // printf("%s\n", neta_node2string(eval_stack[eval_top - 2]));
    eval_stack[ms - 2] = get_current_eval();
    reset(ms - 2);
    ptr = ptr_m;
    parse_top = parse_top_m;
}