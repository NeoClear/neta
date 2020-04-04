/*
 * neta.c contains:
 * main function
 */

#include <stdio.h>
#include "eval.h"
#include "debug.h"
#include "data.h"
#include "util.h"
#include "nlib.h"
#include <stdlib.h>
#include <time.h>
#include "err.h"
#include <string.h>

extern FILE *yyin;
extern int yyleng;

int yylex();

void init()
{
    srand((i64)time(nil));
}

int main(int argc, char **argv) {
    argc--, argv++;
    
    
    if (argc == 0) {
        char repl[1024] = "                                 \
        (fun repl-help () {                                 \
            (println \"SHIT\")                              \
        })                                                  \
        (fun repl () {                                      \
            (setl command (conti 1))                        \
            (while 1 {                                      \
                (print \"neta -> \")                        \
                (-> (command (readln)))                     \
                (match command                              \
                    \":help\" (repl-help)                   \
                    \":quit\" (return-f @nil)               \
                    @default (println (eval command)))      \
            })                                              \
        })                                                  \
        (repl)";
        FILE *tmp = fopen("/tmp/repl.neta", "w");
        fwrite(repl, sizeof(char), strlen(repl), tmp);
        fclose(tmp);
        yyin = fopen("/tmp/repl.neta", "r");
    } else {
        yyin = fopen(argv[0], "r");
    }
    yylex();
    init();
    // print_parse_tree();
    while (!parse_finished()) {
        eval();
        if (is_err) {
            fprintf(stderr, "Unhandled Error: %s\n", err_msg);
            exit(0);
        }
        eval_top = 0;
    }
    return 0;
}