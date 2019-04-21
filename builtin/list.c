#include "list.h"
#include "../eval.h"
#include "../nlib.h"
#include "../err.h"
#include "../def.h"

enum return_type sub_listof()
{

}

enum return_type builtin_listof()
{
    i64 ms = milestone();
    eval_stack[ms - 2].t = LIST;
    while (!read_rparen()) {
        eval_errh()
    }
    if (ms == offset(-1)) {
        eval_stack[ms - 2].p = nil;
        reset(ms - 2);
        return NORMAL;
    } else {
        eval_stack[ms - 2].p = new_neta_node();
        *eval_stack[ms - 2].p = eval_stack[ms];
        eval_stack[ms - 2].p->next = nil;
        struct neta_node *p = eval_stack[ms - 2].p, *q = eval_stack[ms - 2].p;
        for (i64 i = ms + 1; i <= offset(-2); i++) {
            p = new_neta_node();
            *p = eval_stack[i];
            p->next = nil;
            q->next = p;
            q = p;
        }
        reset(ms - 2);
        return NORMAL;
    }
}