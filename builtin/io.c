#include "io.h"
#include "../data.h"
#include "../nlib.h"
#include "../debug.h"
#include "../err.h"
#include "../util.h"

void builtin_print()
{
    push_trace("print");
    i64 ms = milestone();
    // Evaluate params
    while (!read_rparen()) {
        eval();
    }
    // Print them
    for (i64 i = ms; i <= offset(-2); i++) {
        printf("%s", neta_node2string(eval_stack[i]));
    }
    // Reset answer
    eval_stack[ms - 2] = default_return;
    pop_trace();
    eval_top = ms - 1;
}

void builtin_println()
{
    builtin_print();
    printf("\n");
}

void builtin_read()
{
    push_trace("read");
    i64 ms = milestone();
    eval_stack[ms - 2].t = STRING;
    char s[inf24];
    scanf("%s", s);
    eval_stack[ms - 2].v.s = clone(s);
    if (!read_rparen())
        parse_err(neta_type2string(RPAREN), neta_type2string(get_next_parse().t));
    pop_trace();
    reset(ms - 2);
}
void builtin_readln()
{
    push_trace("readln");
    i64 ms = milestone();
    eval_stack[ms - 2].t = STRING;
    char s[inf24];
    gets(s);
    eval_stack[ms - 2].v.s = clone(s);
    if (!read_rparen())
        parse_err(neta_type2string(RPAREN), neta_type2string(get_next_parse().t));
    pop_trace();
    reset(ms - 2);
}
