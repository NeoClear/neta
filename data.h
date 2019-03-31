#ifndef _DATA_H_
#define _DATA_H_

#include <stdio.h>
#include <string.h>
// #include "util.h"
// #include "io.h"

typedef unsigned char boolean;
#define true 1
#define false 0
#define inf 0xffffff
#define inf8 0xf
#define inf16 0xff
#define inf24 0xfff
#define inf32 0xffff
#define nil NULL

typedef long long i64;
typedef double f64;

// From io.h
char *clone(char *s);
// End here

// From util.h
i64 max(i64 a, i64 b);
i64 min(i64 a, i64 b);

boolean greater_s(char *a, char *b);
boolean eq_s(char *a, char *b);
boolean less_s(char *a, char *b);
// End here

enum neta_type
{
    LPAREN,
    RPAREN,
    PRESERVED_FUN,
    IDENTIFIER,
    INTEGER,
    FLOAT,
    STRING,
    CHAR,
};
enum global_type
{
    function,
    variable,
    constant,
};

struct global_variable
{
    char *name;
    enum global_type gt;
    struct neta_node *value;
    boolean initialized;

    struct global_variable *left;
    struct global_variable *right;
    i64 height;
};

extern struct global_variable *glov;

struct neta_node;

union neta_value
{
    i64 i;
    f64 f;
    char *s;
    char c;
    struct neta_node *p;
};

struct neta_node
{
    enum neta_type t;
    enum global_type gt;
    union neta_value v;
};

extern struct neta_node parse_tree[inf];
extern i64 parse_top;

struct global_variable *new_gvnode(char *name, struct global_variable *l, struct global_variable *r);
struct global_variable *search_gvnode(struct global_variable *tree, char *k);
struct global_variable *min_gvnode(struct global_variable *tree);
struct global_variable *max_gvnode(struct global_variable *tree);
struct global_variable *ll_rotate(struct global_variable *tree);
struct global_variable *rr_rotate(struct global_variable *tree);
struct global_variable *lr_rotate(struct global_variable *tree);
struct global_variable *rl_rotate(struct global_variable *tree);
struct global_variable *gvinsert(struct global_variable *tree, char *k);
struct global_variable *delete_node(struct global_variable *tree, char *node);

void print_gv(struct global_variable *tree);
void print_global_variable_d(struct global_variable *t);

#endif // !_DATA_H_
