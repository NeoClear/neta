#include "eval.h"
#include "err.h"
#include "builtin/arithmetic.h"
#include "builtin/setf.h"
#include "nlib.h"
#include "builtin/prog.h"
#include "builtin/symbol.h"
#include "builtin/print.h"
#include "builtin/if.h"
#include "builtin/string.h"
#include "builtin/while.h"
#include "builtin/assign.h"
#include "builtin/setl.h"
#include "builtin/setc.h"
#include "builtin/fun.h"
#include "builtin/undef.h"
#include "builtin/funcall.h"
#include "builtin/import.h"

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
                } else if (is_setl(get_current_eval().v.s)) {
                    builtin_setl();
                    return;
                } else if (is_setc(get_current_eval().v.s)) {
                    builtin_setc();
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
                } else if (is_assign(get_current_eval().v.s)) {
                    builtin_assign();
                    return;
                } else if (is_fun(get_current_eval().v.s)) {
                    builtin_fun();
                    return;
                } else if (is_undef(get_current_eval().v.s)) {
                    builtin_undef();
                    return;
                } else if (is_import(get_current_eval().v.s)) {
                    builtin_import();
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
                    err("You will never reach a undefined preserved function");
                }
            } else if (read_identifier()) {
                if (search_gvnode(glov, get_current_eval().v.s) != 0 && search_gvnode(glov, get_current_eval().v.s)->gt == FUNCTION) {
                    builtin_funcall(get_current_eval().v.s);
                    return;
                } else {
                    ptr--;
                    eval_top--;
                    eval();
                    if (!read_rparen())
                        parse_err(neta_type2string(RPAREN), neta_type2string(get_next_parse().t));
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
            struct neta_node *local = nil;
            if (find_variable(&local, get_current_eval().v.s)) {
                eval_stack[eval_top - 1] = *local;
                return;
            } else if (find_global_constant(&local, get_current_eval().v.s)) {
                eval_stack[eval_top - 1] = *local;
                return;
            } else
                err("could not find variable");
        } else if (read_preserved_fun()) {
            err("You can't give a keyword or built-in function directly");
        }
    }
}
