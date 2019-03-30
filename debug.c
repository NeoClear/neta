#include "debug.h"

i64 err = 0;

void print_parse_tree()
{
    for (i64 i = 0; i < parse_top; i++) {
        printf("%d | (%lld, %lf)", parse_tree[i].t, parse_tree[i].v.i, parse_tree[i].v.f);
        if (parse_tree[i].t == PRESERVED_FUN)
            printf("%s", parse_tree[i].v.s);
        printf("\n");
    }
}

void print_eval_stack()
{
    for (i64 i = 0; i < eval_top; i++)
        printf("(%lld, %lf)\n", eval_stack[i].v.i, eval_stack[i].v.f);
    printf("%lld\n", eval_top);
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
    printf("%lf\n", f);
}

void print_value(struct neta_node v)
{
    switch (v.t) {
    case INTEGER:
        printf("%lld", v.v.i);
        break;
    case FLOAT:
        printf("%lf", v.v.f);
        break;
    case STRING:
        printf("\"%s\"", v.v.s);
        break;
    case CHAR:
        printf("\'%c\'", v.v.c);
        break;
    case PRESERVED_FUN:
        printf("%s", v.v.s);
        break;
    case IDENTIFIER:
        printf("%s", v.v.s);
        break;
    default:
        printf("What The Hell? Couldn't Find Known Value");
    }
}

void print_global_variable()
{
    for (i64 i = 0; i < glon; i++) {
        printf("%s, %d, ", glov[i].name, glov[i].initialized);
        if (glov[i].initialized)
            print_value(*glov[i].value);
        else
            printf("Variable Not Initialized");
        printf("\n");
    }
}