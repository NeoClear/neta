# Detailss

## Layout

+ builtin/arithmetic: basic arithmetic functions like plus, minus, multiply, divide, greater, smaller, equal

+ builtin/setf: functions for the storage of global variables

+ builtin/setc: function for the storage of constants

+ builtin/predicate: functions for judging the type of the function

+ builtin/def: functions for the storage of global functions

+ builtin/undef: removement for global values

+ builtin/defl: storage of local functions

+ builtin/setl: storage of local variables

+ builtin/progn: dealing with a sequence of expressions

+ builtin/builtin: other builtin functions

+ builtin/symbol: the search of symbols(functions, variables and constants)

+ data: basic data types and values. variables for global value map. parse stack and eval stack

+ debug: debug functions

+ eval: main eval function

+ io: those function dealing with strings. could be merged to util

+ lexer: export metadata from flex to tokens

+ util: useful function for general purpose. look ahead functions should be exported to parser

+ nlib: useful function for neta implementation

+ parser: look ahead functions and back tracing functions(it shouldn't be called as parser actually)

+ error: encapsulation of errors

## Include Hierachy

+ builtin/arithmetic :: parser -> (util)

+ builtin/setf :: parser -> (util)

+ builtin/setc :: parser -> (util)

+ builtin/predicate :: parser -> builtin/symbol -> (util)

+ builtin/def :: data -> (util)

+ builtin/undef :: data -> (util)

+ builtin/defl :: parser -> (util)

+ builtin/setl :: parser -> (util)

+ builtin/builtin :: parser -> (util)

+ builtin/symbol :: data -> (util)

+ data

+ debug :: (others)

+ eval :: data -> (util)

+ lexer :: (util)

+ util

+ nlib :: data

+ parser :: data

+ error :: data

## Error Throwing

We have syntax error, parsing error and runtime error.

+ syntax error: handled in flex(like: two characters in '')

+ parsing error: mismatch of tokens(like: expected close paren, encountered preserved fun)(implement using only one function)

+ runtime error: error of types(like: expected double, encountered string)