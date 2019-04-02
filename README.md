# The Neta Functional Programmimng Language Intepreter

## Why Neta

+ To illustrate that there is no worst programming language. There is always a worse one.

+ To prove that writing an interpreter is not unreachable. Even a high school student could implement one.

+ Functional programming languages are of great use if you study their characteristics, although they are quite useless in industry.

## How To Install It

+ Make sure you have installed **flex**, **gcc** and **make** in your system.

+ Clone its source code from **[download here](https://github.com/NeoClear/neta.git)**.

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

+ This project lasts for about 6 months. Starting from the end of March, the supprt of this project won't last to September. It is the prototype for another awesome compiler project which I haven't come up with the name yet. The enhanced project will be the compiler of a kotlin-like language which supports modern characteristics. The compiler is able to translate the source code to **llvm IR**, which you can translate to executable programs or run it on llvm directly.

+ Students can use it as extra-curricular materials about programming on unix-like systems and the use of flex and gcc.

## Reference

+ Ansi Common Lisp

+ CS143 Stanford Online Course

+ Video Materials for CS143

## Info

+ Author: NeoClear

+ Email: neoclear@outlook.com

Feel free to post bugs to me!