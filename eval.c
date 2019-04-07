#include "eval.h"
#include "builtin/arithmetic.h"
#include "builtin/setf.h"
#include "nlib.h"
#include "builtin/prog.h"
#include "builtin/symbol.h"

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
                } else if (is_dplus(get_current_eval().v.s)) {
                    builtin_dplus();
                    return;
                } else if (is_dminus(get_current_eval().v.s)) {
                    builtin_dminus();
                    return;
                } else if (is_dmul(get_current_eval().v.s)) {
                    builtin_dmul();
                    return;
                } else if (is_ddiv(get_current_eval().v.s)) {
                    builtin_ddiv();
                    return;
                } else if (is_setf(get_current_eval().v.s)) {
                    builtin_setf();
                    return;
                } else if (is_prog(get_current_eval().v.s)) {
                    builtin_prog();
                    return;
                } else {
                    eval();
                    read_rparen();
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
            struct neta_node *local = find_symbol(get_current_eval().v.s);
            eval_stack[eval_top - 1] = *local;
            return;
        } else if (read_preserved_fun()) {
            printf("You can't give a keyword or built-in function directly\n");
        }
    }
}
