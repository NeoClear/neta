/*
 * data.h contains:
 * basic data types and the definition of values
 * useful functions(Should move to util.h)
 */

#ifndef _DATA_H_
#define _DATA_H_

#include <stdio.h>
#include <string.h>
#include "def.h"

// Defining basic data types


// From io.h
// char *clone(char *s);
// End here

// From util.h
// i64 max(i64 a, i64 b);
// i64 min(i64 a, i64 b);

// Comparison function for two strings
// Should move to util.h
// boolean greater_s(char *a, char *b);
// boolean eq_s(char *a, char *b);
// boolean less_s(char *a, char *b);
// End here

// Basic types for a token
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

// Basic types for a value
enum global_type
{
    function,
    variable,
    constant,
};

// Data structure of a global values
// In the form of the AVL tree node
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

// Root of global values(AVL tree)
extern struct global_variable *glov;

struct neta_node;

// The primitive generic type
union neta_value
{
    i64 i;
    f64 f;
    char *s;
    char c;
    struct neta_node *p;
};

// the node of parsing stack and evaluation stack
struct neta_node
{
    enum neta_type t;
    enum global_type gt;
    union neta_value v;
};

// From eval.h
extern struct neta_node parse_tree[inf];
extern i64 parse_top;

// Functions for AVL tree
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

// Debug functions
void print_gv(struct global_variable *tree);
// Should move to debug.h?
void print_global_variable_d(struct global_variable *t);


// Evaluation stack
extern struct neta_node eval_stack[inf];
// Top of evaluation stack
extern i64 eval_top;
// The pointer to parse stack while evaluating
extern i64 ptr;


#endif // !_DATA_H_
