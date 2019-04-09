# MANUAL

## Basic Concepts

In neta, everything is an expression, which stands for a value. Although its grammar is complicated in some sense, they all represent a value. Let's take some examples.

```neta
(+ 2 3)
```

It represents 5 :: Integer. And

```neta
(d+ 2 2.2)
```

represents 4.2 :: Float

Some keywords in other languages like "if" of python. "if" is just a sentence in python and it does not represent any values. But in neta, it represents a value.

```neta
(if 1
    1
    0)
```

It represents 1 if first expression refers to true, and represents 0 if first expression refers to false.

And as for a while expression

```neta
(while 1
    (!
        (println "star")
        "star"))
```

It represents "star" if while has at least one loop, and integer 0 if while has no loops at all.

The definition of variables, constants and functions has a return value, although they are useless and meaningless

```neta
(setf x y (z 666))

(setc (p "imba"))

(setl (z "imba"))

(fun fib (x)
    (if (<= x 2)
        1
        (+ (fib (- x 2)) (fib (- x 1)))))
```

They all represent a value.

## Basic Types

In neta, there are six basic types. They are:

```neta
1
1
1.1
"star"
'c'
[1, 2.3333, "66", 't']
```

From top to buttom, they are Integer, Bool, Float, String, Char and List.
List haven't been implemented, so you can't use it now.
Bool is a subset of Integer. It is false if it is 0, and it is true otherwise.

## Basic Arithmetic functions

Of course, neta has plus, minus, times and divition functions. Unlike other programming languages, those arithmetic functions are really functions in neta, while they are operators in other conventional languages. Examples:

```neta
(+ 1 2 3 4)

(- 2 3)

(* 1 2 3 4)

(/ 1 2)
```

They operate on Integers. If you want to operate on Floats, you can use the following functions.

```neta
(d+ 1 2 3 4.44)
(d- 1 2.2)
(d* 5.5 2.32 7.8)
(d/ 6 4.2)
```

Besides plus and minus, there are comparison functions inside arithmetic package. They are:

```neta
(< 1 2)
(= 6 6)
(> 5 6.2)
(<= 3 4)
(!= 6 6)
(>= 7 2.2)
```

Those functions could deal with numbers. It accepts Integers and Floats and return the truth value.

## Basic String Functions

Currently neta only has two functions which deal with string. They are:

```neta
(strlen "Star Platinum")

(strcmp "INNOVATION" "MARU")
```

strlen returns the length of a string and strcmp returns -1 if the first is less than the second in lexicalgraphical order, returns 0 if two are the same and returns 1 if the first is greater than the second.

## Basic Print Functions

```neta
(print "a" 1 1.1 'c')

(println "a" 1 1.1 'c')
```

print and println accept basic types as parameters and they can accept numerous params. The only difference between them is that println prints a newline.

## Basic If And While Structure

As we all know, neta has if and while expressions.

```neta
(if 1
    (println 1)
    (println 2))
```

if executes the second expression if the first is true, and executes the third expression if the first is false.

```neta
(println (if 1
            2
            3))
```

It prints 2 since if represents the second expression if the first expression is true. Unlike other languages, you must write the second part whether you need the second part or not.

```neta
(while 1
    (println "AMD YES!!!"))
```

It prints "AMD YES!!!" constantly because while executes the second expression if the first expression is true and stop if the first expression is false. It represents the value of the second expression of the last loop, and represents Integer 0 if the loop doesn't executes at all.

## Definition Of Variables, Constants And Functions

There are mainly two ways to define a vaiable.

```neta
(setf (a 2333) (b 6666))
(setl (c 5) (d "pimba"))
```

The setf expression defines global variable, meaning that you can have access to it everywhere. As for setl expression, it defines local variables, meaning that the variable would be freed once the current block had been finished. To extend the topic further, you should be aware of the prog expression.

```neta
(prog
    (println 1)
    (println 2))
```

prog expression takes several expressions and return the value of the last expression. prog expression is widely used if you want to extend your codes with a lot of expresisons. And setl is used with prog expression since prog expression is the only expression that takes several expressions and create a closed environment for local variables.

And prog expression can be abbreviate as follows:

```neta
(!
    (println 1)
    (println 2))
```

If you want to define a global constant, you can use setc expression:

```neta
(setc (PI 3.14159))
```

You can't define a local constant because a local constant is useless in all situations. Only global constants are needed.

A variable should be able to modify its value, so here comes assign expression.

```neta
(assign (it 6))
(assign (inno "terran king"))
```

assign expression takes several parens and in each paren, it takes the left as the variable you are going to assign the value and the right is the value. You can only modify a variable's value. And it has an abbreviation:

```neta
(-> (it 6))
(-> (inno "terran king"))
```

Currently you can only define a global function, using fun expression

```neta
(fun tyty (race team)
    (!
        (println race)
        (println team)))
```

fun expression accepts a function name, a parameter list and the function body. Since the function body is just one expression, you should use prog expression to extend the function body in most cases.

And the function in neta supports self recursion, which is pretty fancy and awesome.

```neta
(fun fib (x)
    (if (<= x 2)
        1
        (+ (fib (- x 2)) (fib (- x 1)))))
```

Above is the function for calculating fibonacci numbers using self recursion. Let's run it:

```neta
(println (fib 8))
```

And it prints 21

If you define a function without any parameter, you should also place a pair of paren there. Like:

```neta
(fun tyty ()
    (println "TYTY"))

(tyty)
```

And it prints "TYTY"

## Try It

Let's have an examle which prints 16 to 1

```neta
(setf (it 16))
(while (> it 0)
    (!
        (println it)
        (-> (it (- it 1)))))
```

Isn't it awesome???