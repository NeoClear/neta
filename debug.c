#include "debug.h"

i64 err = 0;

void print_parse_tree()
{
    for (i64 i = 0; i < parse_top; i++) {
        printf("%d | (%lld, %llf)", parse_tree[i].t, parse_tree[i].v.i, parse_tree[i].v.f);
        if (parse_tree[i].t == PRESERVED_FUN)
            printf("%s", parse_tree[i].v.s);
        printf("\n");
    }
}

void print_eval_stack()
{
    for (i64 i = 0; i < eval_top; i++)
        printf("(%lld, %lf)\n", eval_stack[i].v.i, eval_stack[i].v.f);
    printf("%d\n", eval_top);
}

void neta_err()
{
    printf("Neta: %lld\n", err++);
}

void pi(i64 i)
{
    printf("%lld\n", i);
}
void ps(char *s)
{
    printf("%s\n", s);
}
void pf(f64 f)
{
    printf("%llf\n", f);
}