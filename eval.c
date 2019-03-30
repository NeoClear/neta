#include "eval.h"
#include "builtin/arithmetic.h"
#include "builtin/setf.h"

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

boolean is_setf(char *s)
{
    if (strcmp(s, "setf") == 0)
        return true;
    return false;
}

boolean is_setc(char *s)
{
    if (strcmp(s, "setc") == 0)
        return true;
    return false;
}

void eval()
{
    while (ptr < parse_top) {
        if (read_lparen()) {
            parse_to_eval();
            if (get_current_eval().t == PRESERVED_FUN) {
                if (is_plus(get_current_eval().v.s)) {
                    builtin_plus();
                    return;
                } else if (is_minus(get_current_eval().v.s)) {
                    builtin_minus();
                    return;
                } else if (is_mul(get_current_eval().v.s)) {
                    builtin_mul();
                    return;
                } else if (is_div(get_current_eval().v.s)) {
                    builtin_div();
                    return;
                } else if (is_setf(get_current_eval().v.s)) {
                    builtin_setf();
                    return;
                }
            }
        } else if (read_integer()) {
            return;
        } else if (read_float()) {
            return;
        } else if (read_string()) {
            return;
        } else if (read_char()) {
            return;
        } else if (read_identifier()) {
            
        } else if (read_preserved_fun()) {
            printf("You can't give a keyword or built-in function directly\n");
        }
    }
}
