SRC = lex.yy.c lexer.c debug.c eval.c neta.c util.c builtin/arithmetic.c \
		builtin/setf.c data.c nlib.c builtin/prog.c err.c \
		builtin/symbol.c builtin/print.c builtin/if.c \
		builtin/string.c builtin/while.c
neta: lex.yy.c
	gcc -o neta $(SRC) -ll

lex.yy.c: neta.l
	flex neta.l

.PHONY: clean run

clean:
	-rm lex.yy.c neta

run:
	./neta test.neta
