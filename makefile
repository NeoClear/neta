SRC = lex.yy.c lexer.c debug.c eval.c neta.c util.c builtin/arithmetic.c \
		builtin/setf.c data.c nlib.c builtin/prog.c err.c \
		builtin/symbol.c builtin/io.c builtin/if.c \
		builtin/str.c builtin/while.c builtin/assign.c \
		builtin/setl.c builtin/setc.c builtin/undef.c builtin/fun.c \
		builtin/funcall.c builtin/import.c builtin/type.c builtin/standard.c \
		builtin/parse.c
neta: lex.yy.c
	gcc -o neta $(SRC) -lfl

lex.yy.c: neta.l
	flex neta.l

.PHONY: clean run

clean:
	-rm lex.yy.c neta

run:
	./neta test.neta
