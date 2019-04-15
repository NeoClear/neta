# The Neta Functional Programmimng Language Intepreter

## Why Neta

+ To illustrate that there is no worst programming language. There is always a worse one.

+ To prove that writing an interpreter is not unreachable. Even a high school student could implement one.

+ Functional programming languages are of great use if you study their characteristics, although they are quite useless in industry.

## How To Install It

+ Make sure you have installed **flex**, **gcc** and **make** in your system.

+ Clone its source code from **[download here](https://codeload.github.com/NeoClear/neta/zip/master)**.

+ Run **make**.

+ Now you have a interpreter as an executable program.

Notice: The makefile works on Mac. If you uses Linux, you should change **gcc -ll** to **gcc -lfl**. If you uses Windows, then it takes some time for you to settle the environment.

## Basic Concept

+ It uses AVL tree to store global variables, functions and constants. (It contains some problems, but no big problem)

+ It uses **Linked List** to store functions, but **Array** is used for the **Evaluation Stack**.

+ The function **Eval** deals with all the expressions, and **Eval** distributes different tasks to specific functions. those second-hand functions could call eval recursively.

+ **Flex** is used while dealing with lexical analysis.

+ Type checks are not executed in the period of analysis. It is checked in runtime.

## Support

+ This project lasts for about 6 months. Starting from the end of March 2019, the supprt of this project won't last to September 2019. It is the prototype for another awesome compiler project which I haven't come up with the name yet(maybe called "King Crimson" or "kincrim"). The enhanced project will be the compiler of a kotlin-like language which supports modern characteristics. The compiler is able to translate the source code to **llvm IR**, which you can translate to executable programs or run it on llvm directly.

+ Students can use it as extra-curricular materials about programming on unix-like systems and the use of flex and gcc.

## Reference

+ Ansi Common Lisp **[click here](https://acl.readthedocs.io/en/latest/zhCN/)**

+ CS143 Stanford Online Course **[click here](http://web.stanford.edu/class/archive/cs/cs143/cs143.1128/)**

+ Video Materials for CS143 **[click here](https://www.bilibili.com/video/av18939632)**

## Info

+ Author: NeoClear

+ Email: neoclear@outlook.com

Feel free to post bugs to me!

## Time Table

+ Start time: 2019-3-29

+ Main part finished at: 2019-4-8

+ **Including:**
    + basic arithmetic functions
    + basic string functions
    + if expression
    + while expression
    + assigning expression
    + print functions
    + definition of local variables
    + definition of global variables
    + definition of global constants
    + definition of global functions
    + call of global functions(support self recursion)
    + access of variables and constants