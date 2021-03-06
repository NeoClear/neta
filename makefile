OBJ = app.o lexer.o debug.o eval.o neta.o util.o builtin/arithmetic.o \
builtin/setf.o data.o nlib.o builtin/prog.o err.o \
builtin/symbol.o builtin/io.o builtin/if.o \
builtin/str.o builtin/while.o builtin/assign.o \
builtin/setl.o builtin/setc.o builtin/undef.o builtin/fun.o \
builtin/funcall.o builtin/import.o builtin/type.o builtin/standard.o \
builtin/parse.o builtin/list.o

neta: $(OBJ)
	cc -o neta  $(OBJ) -lfl

neta.o: neta.c

lexer.o: lexer.h data.h

debug.o: debug.h nlib.h lexer.h eval.h data.h

eval.o: eval.h lexer.h debug.h data.h nlib.h err.h \
	builtin/arithmetic.h builtin/setf.h nlib.h \
	builtin/prog.h builtin/symbol.h builtin/io.h \
	builtin/if.h builtin/str.h builtin/while.h \
	builtin/assign.h builtin/setl.h builtin/setc.h \
	builtin/fun.h builtin/undef.h builtin/funcall.h \
	builtin/import.h builtin/type.h builtin/standard.h \
	builtin/parse.h builtin/list.h

neta.o: neta.c eval.h debug.h data.h util.h nlib.h
	cc -c neta.c -ll

util.o: util.c util.h

builtin/arithmetic.o: builtin/arithmetic.c builtin/arithmetic.h debug.h util.h data.h err.h nlib.h

builtin/setf.o: builtin/setf.c builtin/setf.h data.h util.h nlib.h

data.o: data.c data.h def.h

nlib.o: nlib.c nlib.h def.h data.h err.h

builtin/prog.o: builtin/prog.c builtin/prog.h def.h data.h nlib.h eval.h

err.o: err.c err.h

builtin/symbol.o: builtin/symbol.c builtin/symbol.h data.h def.h err.h debug.h

builtin/io.o: builtin/io.c builtin/io.h data.h nlib.h debug.h eval.h err.h

builtin/if.o: builtin/if.c builtin/if.h nlib.h eval.h err.h data.h

builtin/str.o: builtin/str.c builtin/str.h err.h nlib.h eval.h util.h data.h

builtin/while.o: builtin/while.c builtin/while.h err.h eval.h data.h nlib.h

builtin/assign.o: builtin/assign.c builtin/assign.h data.h eval.h nlib.h err.h builtin/symbol.h

builtin/setl.o: builtin/setl.c builtin/setl.h nlib.h err.h eval.h data.h

builtin/setc.o: builtin/setc.c builtin/setc.h nlib.h err.h eval.h data.h

builtin/undef.o: builtin/undef.c err.h data.h debug.h builtin/undef.h nlib.h

builtin/fun.o: builtin/fun.c builtin/fun.h nlib.h err.h debug.h data.h

builtin/funcall.o: builtin/funcall.c builtin/funcall.h eval.h err.h nlib.h data.h

builtin/import.o: builtin/import.c builtin/import.h eval.h nlib.h err.h data.h

builtin/type.o: builtin/type.c builtin/type.h eval.h nlib.h err.h data.h

builtin/standard.o: builtin/standard.c builtin/standard.h eval.h nlib.h err.h data.h util.h

builtin/parse.o: builtin/parse.c builtin/parse.h eval.h nlib.h err.h data.h

builtin/list.o: builtin/list.c builtin/list.h eval.h nlib.h err.h data.h

neta.c: neta.l
	flex -t neta.l > neta.c

.PHONY:
	clean
	install
	uninstall

clean:
	-rm -rf *.o builtin/*.o neta.c neta


install:
	-mv neta /usr/bin

uninstall:
	-rm /usr/bin/neta
