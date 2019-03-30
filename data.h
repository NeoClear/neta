#ifndef _DATA_H_
#define _DATA_H_

typedef unsigned char boolean;
#define true 1
#define false 0
#define inf 0xffffff

typedef long long i64;
typedef double f64;

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
};

extern struct global_variable glov[inf];
extern i64 glon;

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

#endif // !_DATA_H_
