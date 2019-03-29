neta: lex.yy.c
	gcc -o neta lex.yy.c io.c lexer.c debug.c eval.c neta.c -ll

lex.yy.c: neta.l
	flex neta.l

.PHONY: clean run

clean:
	-rm lex.yy.c neta

run:
	./neta test.neta