#include "debug.h"

i64 err_s = 0;

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
    printf("Neta: %lld\n", err_s++);
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

char *print_value(struct neta_node v)
{
    char *r = (char *)malloc(sizeof(char) * inf24);
    switch (v.t) {
    case INTEGER:
        sprintf(r, "%lld", v.v.i);
        break;
    case FLOAT:
        sprintf(r, "%lf", v.v.f);
        break;
    case STRING:
        sprintf(r, "\"%s\"", v.v.s);
        break;
    case CHAR:
        sprintf(r, "\'%c\'", v.v.c);
        break;
    case PRESERVED_FUN:
        sprintf(r, "%s", v.v.s);
        break;
    case IDENTIFIER:
        sprintf(r, "%s", v.v.s);
        break;
    default:
        sprintf(r, "What The Hell? Couldn't Find Known Value");
    }
    return r;
}

void print_global_variable()
{
    print_gv(glov);
}

void print_global_variable_d(struct global_variable *t)
{
    if (t == nil)
        return;
    print_global_variable_d(t->left);
    // if (t->initialized)
    printf("%s: %s\n", t->name, print_value(*t->value));
    // else
        // printf("%s haven't been initialized\n", t->name);
    print_global_variable_d(t->right);
}