#include "print.h"
#include "../data.h"
#include "../nlib.h"
#include "../debug.h"

void builtin_print()
{
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
    eval_stack[offset_m(ms, -2)].t = INTEGER;
    eval_stack[offset_m(ms, -2)].v.i = 0;
    eval_top = ms - 1;
}

void builtin_println()
{
    builtin_print();
    printf("\n");
}