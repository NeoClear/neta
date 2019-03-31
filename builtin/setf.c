#include "setf.h"

void add_global_variable(char *name, struct neta_node value)
{
    glov = gvinsert(glov, name);
    search_gvnode(glov, name)->initialized = true;
    search_gvnode(glov, name)->value = (struct neta_node *)malloc(sizeof(struct neta_node));
    memcpy(search_gvnode(glov, name)->value, &value, sizeof(struct neta_node));

    // g->value = (struct neta_node *)malloc(sizeof(struct neta_node));
    // memcpy(g->value, &value, sizeof(struct neta_node));
    // gvinsert(glov, g);
    // glov[glon].name = name;
    // glov[glon].initialized = true;
    // glov[glon].value = (struct neta_node *)malloc(sizeof(struct neta_node));
    // memcpy(glov[glon].value, &value, sizeof(struct neta_node));
    // glon++;
}

void create_global_variable(char *name)
{
    glov = gvinsert(glov, name);
    // neta_err();
    // print_gv(glov);
    if (search_gvnode(glov, name) != nil)
        search_gvnode(glov, name)->initialized = false;
    else {

    }
        // neta_err();
    // glov[glon].name = name;
    // glov[glon++].initialized = false;
}

void initialize_variable()
{
    i64 milestone = eval_top;
    read_identifier();
    eval();
    add_global_variable(eval_stack[milestone].v.s, eval_stack[milestone + 1]);
    if (!read_rparen())
        printf("FUCK IT\n");
}

void builtin_setf()
{
    i64 milestone = eval_top;
    while (get_next_parse().t != RPAREN) {
        // parse_to_eval();
        if (read_lparen()) {
            initialize_variable();
            // parse_to_eval();
            continue;
        } else if (read_identifier()) {
            // neta_err();
            create_global_variable(get_current_eval().v.s);
            continue;
        } else {
            neta_err();
        }
    }
    parse_to_eval();
    eval_top = milestone - 2;
}