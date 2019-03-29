#include "eval.h"

i64 ptr = 0;
struct neta_node eval_stack[inf];
i64 eval_top = 0;

void eval();

boolean is_plus(char *s)
{
    if (strcmp(s, "+") == 0)
        return true;
    return false;
}

boolean is_minus(char *s)
{
    if (strcmp(s, "-") == 0)
        return true;
    return false;
}

boolean is_mul(char *s)
{
    if (strcmp(s, "*") == 0)
        return true;
    return false;
}

boolean is_div(char *s)
{
    if (strcmp(s, "/") == 0)
        return true;
    return false;
}

boolean is_def(char *s)
{
    if (strcmp(s, "def") == 0)
        return true;
    return false;
}

boolean is_undef(char *s)
{
    if (strcmp(s, "undef") == 0)
        return true;
    return false;
}

boolean is_var(char *s)
{
    if (strcmp(s, "var") == 0)
        return true;
    return false;
}

boolean is_val(char *s)
{
    if (strcmp(s, "val") == 0)
        return true;
    return false;
}

boolean is_range(char *s)
{
    if (strcmp(s, "..") == 0)
        return true;
    return false;
}

void builtin_plus()
{
    i64 start = eval_top;
    i64 end;
    struct neta_node v = eval_stack[start];
    boolean has_double = false;
    while (eval_stack[eval_top - 1].t != RPAREN && ptr <= parse_top) {
        if (parse_tree[ptr].t == LPAREN) {
            eval();
        }
        eval_stack[eval_top++] = parse_tree[ptr++];
    }
    end = eval_top - 2;
    double d = 0;
    for (i64 i = start; i <= end; i++) {
        if (eval_stack[i].t == INTEGER)
            d += (f64)eval_stack[i].v.i;
        else if (eval_stack[i].t == FLOAT) {
            has_double = true;
            d += eval_stack[i].v.f;
        } else {
            printf("Unknown Number\n");
            exit(0);
        }
    }

    if (has_double) {
        eval_stack[start - 2].t = FLOAT;
        eval_stack[start - 2].v.f = d;
    } else {
        eval_stack[start - 2].t = INTEGER;
        eval_stack[start - 2].v.i = (i64)d;
    }
    eval_top = start - 1;
}

void builtin_minus()
{
    i64 start = eval_top;
    i64 end;
    struct neta_node v = eval_stack[start];
    boolean has_double;
    while (eval_stack[eval_top - 1].t != RPAREN && ptr <= parse_top) {
        if (parse_tree[ptr].t == LPAREN) {
            eval();
        }
        eval_stack[eval_top++] = parse_tree[ptr++];
    }
    end = eval_top - 2;
    double d;
    if (eval_stack[start].t == FLOAT) {
        has_double = true;
        d = eval_stack[start].v.f;
    } else if (eval_stack[start].t == INTEGER) {
        has_double = false;
        d = (f64)eval_stack[start].v.i;
    }
    for (i64 i = start + 1; i <= end; i++) {
        if (eval_stack[i].t == INTEGER)
            d -= (f64)eval_stack[i].v.i;
        else if (eval_stack[i].t == FLOAT) {
            has_double = true;
            d -= eval_stack[i].v.f;
        } else {
            printf("Unknown Number\n");
            exit(0);
        }
    }
    if (has_double) {
        eval_stack[start - 2].t = FLOAT;
        eval_stack[start - 2].v.f = d;
    } else {
        eval_stack[start - 2].t = INTEGER;
        eval_stack[start - 2].v.i = (i64)d;
    }
    eval_top = start - 1;
}

void builtin_mul()
{
    i64 start = eval_top;
    i64 end;
    struct neta_node v = eval_stack[start];
    boolean has_double = false;
    while (eval_stack[eval_top - 1].t != RPAREN && ptr <= parse_top) {
        if (parse_tree[ptr].t == LPAREN) {
            eval();
        }
        eval_stack[eval_top++] = parse_tree[ptr++];
    }
    end = eval_top - 2;
    double d = 1;
    for (i64 i = start; i <= end; i++) {
        if (d == 0.0)
            break;
        if (eval_stack[i].t == INTEGER)
            d *= (f64)eval_stack[i].v.i;
        else if (eval_stack[i].t == FLOAT) {
            has_double = true;
            d *= eval_stack[i].v.f;
        } else {
            printf("Unknown Number\n");
            exit(0);
        }
    }

    if (has_double) {
        eval_stack[start - 2].t = FLOAT;
        eval_stack[start - 2].v.f = d;
    } else {
        eval_stack[start - 2].t = INTEGER;
        eval_stack[start - 2].v.i = (i64)d;
    }
    eval_top = start - 1;
}

void builtin_div()
{
    i64 start = eval_top;
    i64 end;
    struct neta_node v = eval_stack[start];
    while (eval_stack[eval_top - 1].t != RPAREN && ptr <= parse_top) {
        if (parse_tree[ptr].t == LPAREN) {
            eval();
        }
        eval_stack[eval_top++] = parse_tree[ptr++];
    }
    end = eval_top - 2;
    double d;
    if (eval_stack[start].t == FLOAT)
        d = eval_stack[start].v.f;
    else if (eval_stack[start].t == INTEGER)
        d = (f64)eval_stack[start].v.i;
    for (i64 i = start + 1; i <= end; i++) {
        if (eval_stack[i].t == INTEGER) {
            if (eval_stack[i].v.i == 0) {
                printf("Div By Zero\n");
                exit(0);
            }
            d /= (f64)eval_stack[i].v.i;
            
        } else if (eval_stack[i].t == FLOAT) {
            if (eval_stack[i].v.f == 0) {
                printf("Div By Zero\n");
                exit(0);
            }
            d /= eval_stack[i].v.f;
        } else {
            printf("Unknown Number\n");
            exit(0);
        }
    }

    eval_stack[start - 2].t = FLOAT;
    eval_stack[start - 2].v.f = d;

    eval_top = start - 1;
}

void eval()
{
    while (ptr < parse_top) {        
        eval_stack[eval_top++] = parse_tree[ptr++];
        if (eval_stack[eval_top - 1].t == PRESERVED_FUN) {
            if (is_plus(eval_stack[eval_top - 1].v.s)) {
                builtin_plus();
                return;
            } else if (is_minus(eval_stack[eval_top - 1].v.s)) {
                builtin_minus();
                return;
            } else if (is_mul(eval_stack[eval_top - 1].v.s)) {
                builtin_mul();
                return;
            } else if (is_div(eval_stack[eval_top - 1].v.s)) {
                builtin_div();
                return;
            }
        }
    }
}
