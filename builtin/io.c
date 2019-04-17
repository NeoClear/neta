#include "io.h"
#include "../data.h"
#include "../nlib.h"
#include "../debug.h"
#include "../err.h"
#include "../util.h"

enum return_type builtin_print()
{
    push_trace("print");
    // Reset answer
    i64 ms = milestone();
    eval_stack[ms - 2] = default_return;
    // Evaluate params
    while (!read_rparen()) {
        eval_errh()
    }
    // Print them
    for (i64 i = ms; i <= offset(-2); i++) {
        printf("%s", neta_node2string(eval_stack[i]));
    }

    pop_trace();
    eval_top = ms - 1;
}

enum return_type builtin_println()
{
    builtin_print();
    printf("\n");
}

enum return_type builtin_read()
{
    push_trace("read");
    i64 ms = milestone();
    eval_stack[ms - 2].t = STRING;
    char s[inf24];
    scanf("%s", s);
    eval_stack[ms - 2].v.s = clone(s);
    if (!read_rparen())
        parse_errh(neta_type2string(RPAREN), neta_type2string(get_next_parse().t))
    pop_trace();
    reset(ms - 2);
    return NORMAL;
}
enum return_type builtin_readln()
{
    push_trace("readln");
    i64 ms = milestone();
    eval_stack[ms - 2].t = STRING;
    char s[inf24];
    gets(s);
    eval_stack[ms - 2].v.s = clone(s);
    if (!read_rparen())
        parse_errh(neta_type2string(RPAREN), neta_type2string(get_next_parse().t))
    pop_trace();
    reset(ms - 2);
    return NORMAL;
}
