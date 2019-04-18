#include "data.h"
#include <stdlib.h>
#include "util.h"

// Parsing Stack
// Called parse_tree because of historical issues
struct neta_node parse_tree[inf];
i64 parse_top = 0;

// Root for AVL tree
struct global_variable *glov = nil;

i64 ptr = 0;
struct neta_node eval_stack[inf];
i64 eval_top = 0;

char *backtrace[inf];
i64 trace_top;

struct neta_node default_return = {
    .t = SYMBOL,
    .v.s = "@nil",
};

// Measures the height of a AVL tree
int height(struct global_variable *t)
{
    if (t == nil)
        return 0;
    return t->height;
}

// Generate a new AVL node
struct global_variable *new_gvnode(char *name, struct global_variable *l, struct global_variable *r)
{
    struct global_variable *ret = (struct global_variable *)malloc(sizeof(struct global_variable));
    ret->name = name;
    ret->left = l;
    ret->right = r;
    ret->height = 1;
    return ret;
}

// Search AVL node
struct global_variable *search_gvnode(struct global_variable *tree, char *k)
{
    while (tree != nil && !eq_s(tree->name, k)) {
        if (less_s(k, tree->name))
            tree = tree->left;
        else
            tree = tree->right;
    }
    return tree;
}

// Get the smallest node of a AVL tree
struct global_variable *min_gvnode(struct global_variable *tree)
{
    if (tree == nil)
        return nil;
    while (tree->left != nil)
        tree = tree->left;
    return tree;
}

// Get the biggest node of a AVL tree
struct global_variable *max_gvnode(struct global_variable *tree)
{
    if (tree == nil)
        return nil;
    while (tree->right != nil)
        tree = tree->right;
    return tree;
}

// left-left rotate of a AVL tree
struct global_variable *ll_rotate(struct global_variable *tree)
{
    struct global_variable *lef;
    lef = tree->left;
    tree->left = lef->right;
    lef->right = tree;
    tree->height = max(height(tree->left), height(tree->right)) + 1;
    lef->height = max(height(lef->left), height(lef->right)) + 1;
    return lef;
}

// right-right rotate of a AVL tree
struct global_variable *rr_rotate(struct global_variable *tree)
{
    struct global_variable *rig;
    rig = tree->right;
    tree->right = rig->left;
    rig->left = tree;
    tree->height = max(height(tree->left), height(tree->right)) + 1;
    rig->height = max(height(rig->left), height(rig->right)) + 1;
    return rig;
}

// left-right rotate of a AVL tree
struct global_variable *lr_rotate(struct global_variable *tree)
{
    tree->left = rr_rotate(tree->left);
    return ll_rotate(tree);
}

// right-left rotate of a AVL tree
struct global_variable *rl_rotate(struct global_variable *tree)
{
    tree->right = ll_rotate(tree->right);
    return rr_rotate(tree);
}

// Insert a node to the AVL tree
struct global_variable *gvinsert(struct global_variable *tree, char *k)
{
    // If root is nil then initialize root
    if (tree == nil) {
        tree = new_gvnode(k, nil, nil);
    } else if (less_s(k, tree->name)) {
        tree->left = gvinsert(tree->left, k);
        if (height(tree->left) - height(tree->right) == 2) {
            if (less_s(k, tree->left->name))
                tree = ll_rotate(tree);
            else {
                tree = lr_rotate(tree);
            }
        }
    } else if (greater_s(k, tree->name)) {
        tree->right = gvinsert(tree->right, k);
        if (height(tree->right) - height(tree->left) == 2) {
            if (greater_s(k, tree->right->name))
                tree = rr_rotate(tree);
            else
                tree = rl_rotate(tree);
        }
    } else {
        printf("SHIT\n");
    }

    tree->height = max(height(tree->left), height(tree->right)) + 1;
    return tree;
}

// delete a node in AVL tree
struct global_variable *delete_gvnode(struct global_variable *tree, char *node)
{
    if (tree == nil || node == nil)
        return nil;
    if (less_s(node, tree->name)) {
        tree->left = delete_gvnode(tree->left, node);
        if (height(tree->right) - height(tree->left) == 2) {
            if (height(tree->right->left) > height(tree->right->right))
                tree = rl_rotate(tree);
            else
                tree = rr_rotate(tree);
        }
    } else if (greater_s(node, tree->name)) {
        tree->right = delete_gvnode(tree->right, node);
        if (height(tree->left) - height(tree->right) == 2) {
            if (height(tree->left->right) > height(tree->left->left))
                tree = lr_rotate(tree);
            else
                tree = ll_rotate(tree);
        }
    } else {
        // Delete Current Node
        if (tree->left != nil && tree->right != nil) {
            if (height(tree->left) > height(tree->right)) {
                struct global_variable *m = max_gvnode(tree->left);
                tree->name = clone(m->name);
                tree->left = delete_gvnode(tree->left, m->name);
            } else {
                struct global_variable *n = min_gvnode(tree->right);
                tree->name = clone(n->name);
                tree->right = delete_gvnode(tree->right, n->name);
            }
        } else {
            struct global_variable *t = tree;
            if (tree->left == nil)
                tree = tree->right;
            else
                tree = tree->left;
            free(t);
        }
    }
    return tree;
}

// print the tree
void print_gv(struct global_variable *tree)
{
    if (tree == nil)
        return;
    print_gv(tree->left);
    printf("%s\n", tree->name);
    print_gv(tree->right);
}

void push_trace(char *s)
{
    backtrace[trace_top++] = s;
}
void pop_trace()
{
    trace_top--;
}

void print_trace()
{
    for (i64 i = 0; i < trace_top; i++) {
        printf("%s\n", backtrace[i]);
    }
}