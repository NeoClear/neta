#include "eval.h"
#include "err.h"
#include <stdlib.h>
#include <string.h>
#include "debug.h"
#include "data.h"
#include "lexer.h"
#include "nlib.h"
#include "builtin/arithmetic.h"
#include "builtin/setf.h"
#include "nlib.h"
#include "builtin/prog.h"
#include "builtin/symbol.h"
#include "builtin/io.h"
#include "builtin/if.h"
#include "builtin/str.h"
#include "builtin/while.h"
#include "builtin/assign.h"
#include "builtin/setl.h"
#include "builtin/setc.h"
#include "builtin/fun.h"
#include "builtin/undef.h"
#include "builtin/funcall.h"
#include "builtin/import.h"
#include "builtin/type.h"
#include "builtin/standard.h"
#include "builtin/parse.h"

enum return_type eval()
{
    while (ptr < parse_top) {
        if (read_lparen()) {
            // parse_to_eval();
            if (read_preserved_fun()/* get_current_eval().t == PRESERVED_FUN */) {
                if (is_plus(get_current_eval().v.s)) {
                    builtin_plus();
                    return NORMAL;
                } else if (is_minus(get_current_eval().v.s)) {
                    builtin_minus();
                    return NORMAL;
                } else if (is_mul(get_current_eval().v.s)) {
                    builtin_mul();
                    return NORMAL;
                } else if (is_div(get_current_eval().v.s)) {
                    builtin_div();
                    return NORMAL;
                } else if (is_dplus(get_current_eval().v.s)) {
                    builtin_dplus();
                    return NORMAL;
                } else if (is_dminus(get_current_eval().v.s)) {
                    builtin_dminus();
                    return NORMAL;
                } else if (is_dmul(get_current_eval().v.s)) {
                    builtin_dmul();
                    return NORMAL;
                } else if (is_ddiv(get_current_eval().v.s)) {
                    builtin_ddiv();
                    return NORMAL;
                } else if (is_less(get_current_eval().v.s)) {
                    builtin_less();
                    return NORMAL;
                } else if (is_equal(get_current_eval().v.s)) {
                    builtin_equal();
                    return NORMAL;
                } else if (is_greater(get_current_eval().v.s)) {
                    builtin_greater();
                    return NORMAL;
                } else if (is_less_equal(get_current_eval().v.s)) {
                    builtin_less_equal();
                    return NORMAL;
                } else if (is_not_equal(get_current_eval().v.s)) {
                    builtin_not_equal();
                    return NORMAL;
                } else if (is_greater_equal(get_current_eval().v.s)) {
                    builtin_greater_equal();
                    return NORMAL;
                } else if (is_rand(get_current_eval().v.s)) {
                    builtin_rand();
                    return NORMAL;
                } else if (is_setf(get_current_eval().v.s)) {
                    builtin_setf();
                    return NORMAL;
                } else if (is_setl(get_current_eval().v.s)) {
                    builtin_setl();
                    return NORMAL;
                } else if (is_setc(get_current_eval().v.s)) {
                    builtin_setc();
                    return NORMAL;
                } else if (is_prog(get_current_eval().v.s)) {
                    return builtin_prog();
                } else if (is_if(get_current_eval().v.s)) {
                    return builtin_if();
                } else if (is_while(get_current_eval().v.s)) {
                    return builtin_while();
                } else if (is_assign(get_current_eval().v.s)) {
                    builtin_assign();
                    return NORMAL;
                } else if (is_fun(get_current_eval().v.s)) {
                    builtin_fun();
                    return NORMAL;
                } else if (is_undef(get_current_eval().v.s)) {
                    builtin_undef();
                    return NORMAL;
                } else if (is_import(get_current_eval().v.s)) {
                    builtin_import();
                    return NORMAL;
                } else if (is_type(get_current_eval().v.s)) {
                    builtin_type();
                    return NORMAL;
                } else if (is_istype(get_current_eval().v.s)) {
                    builtin_istype();
                    return NORMAL;
                } else if (is_equal_val(get_current_eval().v.s)) {
                    builtin_equal_val();
                    return NORMAL;
                } else if (is_parse(get_current_eval().v.s)) {
                    builtin_parse();
                    return NORMAL;
                } else if (is_eval(get_current_eval().v.s)) {
                    builtin_eval();
                    return NORMAL;
                } else if (is_returnf(get_current_eval().v.s)) {
                    builtin_returnf();
                    return FUNC;
                } else if (is_returnp(get_current_eval().v.s)) {
                    builtin_returnp();
                    return PROG;
                } else if (is_catch(get_current_eval().v.s)) {
                    builtin_catch();
                    return NORMAL;
                } else if (is_throw(get_current_eval().v.s)) {
                    builtin_throw();
                    return NORMAL;
                } else if (is_errmsg(get_current_eval().v.s)) {
                    builtin_errmsg();
                    return NORMAL;
                } else if (is_print(get_current_eval().v.s)) {
                    builtin_print();
                    return NORMAL;
                } else if (is_println(get_current_eval().v.s)) {
                    builtin_println();
                    return NORMAL;
                } else if (is_read(get_current_eval().v.s)) {
                    builtin_read();
                    return NORMAL;
                } else if (is_readln(get_current_eval().v.s)) {
                    builtin_readln();
                    return NORMAL;
                } else if (is_strlen(get_current_eval().v.s)) {
                    builtin_strlen();
                    return NORMAL;
                } else if (is_strcmp(get_current_eval().v.s)) {
                    builtin_strcmp();
                    return NORMAL;
                } else if (is_str2int(get_current_eval().v.s)) {
                    builtin_str2int();
                    return NORMAL;
                } else if (is_str2float(get_current_eval().v.s)) {
                    builtin_str2float();
                    return NORMAL;
                } else if (is_int2float(get_current_eval().v.s)) {
                    builtin_int2float();
                    return NORMAL;
                } else if (is_float2int(get_current_eval().v.s)) {
                    builtin_float2int();
                    return NORMAL;
                } else {
                    errh("You will never reach a undefined preserved function")
                }
            } else if (read_identifier()) {
                if (glov != nil && search_gvnode(glov, get_current_eval().v.s) != nil && search_gvnode(glov, get_current_eval().v.s)->gt == FUNCTION) {
                    builtin_funcall(get_current_eval().v.s);
                    return NORMAL;
                } else {
                     errh("could not find function")
                    //  neta_err();
                    // useless
                    // ptr--;
                    // eval_top--;
                    // eval();
                    // if (!read_rparen())
                    //     parse_errh(neta_type2string(RPAREN), neta_type2string(get_next_parse().t))
                }
            }
        } else if (read_integer()) {
            return NORMAL;
        } else if (read_float()) {
            return NORMAL;
        } else if (read_string()) {
            return NORMAL;
        } else if (read_char()) {
            return NORMAL;
        } else if (read_identifier()) {
            struct neta_node *local = nil;
            if (find_variable(&local, get_current_eval().v.s)) {
                eval_stack[eval_top - 1] = *local;
                return NORMAL;
            } else if (find_global_constant(&local, get_current_eval().v.s)) {
                eval_stack[eval_top - 1] = *local;
                return NORMAL;
            } else {
                errh("could not find variable")
                return NORMAL;
            }
        } else if (read_preserved_fun()) {
            errh("You can't give a keyword or built-in function directly")
            return NORMAL;
        } else if (read_symbol()) {
            return NORMAL;
        }
    }
}
