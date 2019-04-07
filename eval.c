#include "eval.h"
#include "builtin/arithmetic.h"
#include "builtin/setf.h"
#include "nlib.h"
#include "builtin/prog.h"
#include "builtin/symbol.h"
#include "builtin/print.h"
#include "builtin/if.h"
#include "builtin/string.h"
#include "builtin/while.h"

void eval()
{
    while (ptr < parse_top) {
        if (read_lparen()) {
            // parse_to_eval();
            if (read_preserved_fun()/* get_current_eval().t == PRESERVED_FUN */) {
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
                } else if (is_less(get_current_eval().v.s)) {
                    builtin_less();
                    return;
                } else if (is_equal(get_current_eval().v.s)) {
                    builtin_equal();
                    return;
                } else if (is_greater(get_current_eval().v.s)) {
                    builtin_greater();
                    return;
                } else if (is_less_equal(get_current_eval().v.s)) {
                    builtin_less_equal();
                    return;
                } else if (is_not_equal(get_current_eval().v.s)) {
                    builtin_not_equal();
                    return;
                } else if (is_greater_equal(get_current_eval().v.s)) {
                    builtin_greater_equal();
                    return;
                } else if (is_setf(get_current_eval().v.s)) {
                    builtin_setf();
                    return;
                } else if (is_prog(get_current_eval().v.s)) {
                    builtin_prog();
                    return;
                } else if (is_if(get_current_eval().v.s)) {
                    builtin_if();
                    return;
                } else if (is_while(get_current_eval().v.s)) {
                    builtin_while();
                    return;
                } else if (is_print(get_current_eval().v.s)) {
                    builtin_print();
                    return;
                } else if (is_println(get_current_eval().v.s)) {
                    builtin_println();
                    return;
                } else if (is_strlen(get_current_eval().v.s)) {
                    builtin_strlen();
                    return;
                } else if (is_strcmp(get_current_eval().v.s)) {
                    builtin_strcmp();
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
