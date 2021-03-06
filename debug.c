#include "debug.h"
#include "nlib.h"
#include <stdlib.h>

i64 err_s = 0;

void print_parse_tree()
{
    for (i64 i = 0; i < parse_top; i++)
        printf("%s\n", neta_node2string(parse_tree[i]));
}

void print_eval_stack()
{
    for (i64 i = 0; i < eval_top; i++)
        printf("%s\n", neta_node2string(eval_stack[i]));
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

void print_function(char *s)
{
    struct neta_node *head = search_gvnode(glov, s)->value;
    if (head->p == nil)
        return;
    struct neta_node *it = head->p;
    while (it != nil) {
        printf("%s", neta_node2string(*it));
        it = it->next;
    }
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