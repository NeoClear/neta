#include "funcall.h"
#include "../eval.h"
#include "../err.h"
#include "../nlib.h"
#include "../data.h"
#include "../util.h"
#include <stdlib.h>
#include "../debug.h"

// Copy function content to parse stack
void copy_fun(struct neta_node *it)
{
    while (it != nil) {
        parse_tree[parse_top++] = *it;
        it = it->next;
    }
}

enum return_type builtin_funcall(char *fn)
{
    // Find function
    struct neta_node *tp = search_gvnode(glov, fn)->value->p;
    push_trace(clone(fn));
    i64 ms = milestone();
    i64 ptr_m = ptr;
    i64 parse_top_m = parse_top;
    // Eval parameters
    while (get_next_parse().t != RPAREN) {
        eval_errh()
    }
    // Set recall point
    ptr_m = ptr + 1;
    // Read open paren
    if (tp->t != LPAREN)
        errh("SHIT")
    tp = tp->next;
    // Create local variables
    for (i64 it = ms; it < eval_top; it++) {
        struct neta_node *v = (struct neta_node *)malloc(sizeof(struct neta_node));
        *v = eval_stack[it];
        eval_stack[it] = *tp;
        eval_stack[it].t = VALUE;
        eval_stack[it].gt = VARIABLE;
        eval_stack[it].p = v;
        tp = tp->next;
    }
    // Read close paren
    if (tp->t != RPAREN)
        errh("FUCK")
    tp = tp->next;
    // Set recall point 
    ptr = parse_top;
    // Copy function body
    copy_fun(tp);
    eval();
    // Place answer and reset eval stack
    eval_stack[ms - 2] = get_current_eval();
    reset(ms - 2);
    ptr = ptr_m;
    parse_top = parse_top_m;
    pop_trace();
    return NORMAL;
}

enum return_type builtin_returnf()
{
    i64 ms = milestone();
    eval_errh()
    // ps(neta_node2string(get_current_eval()));
    eval_stack[ms - 2] = get_current_eval();
    if (!read_rparen())
        parse_errh(neta_type2string(RPAREN), neta_type2string(get_next_parse().t))
    reset(ms - 2);
    return NORMAL;
}