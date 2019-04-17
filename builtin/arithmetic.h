#ifndef _ARITHMETIC_H_
#define _ARITHMETIC_H_

// Builtin arithmetic functions
enum return_type builtin_plus();
enum return_type builtin_minus();
enum return_type builtin_mul();
enum return_type builtin_div();
enum return_type builtin_dplus();
enum return_type builtin_dminus();
enum return_type builtin_dmul();
enum return_type builtin_ddiv();

// Builtin compare functions
enum return_type builtin_less();
enum return_type builtin_equal();
enum return_type builtin_greater();
enum return_type builtin_less_equal();
enum return_type builtin_not_equal();
enum return_type builtin_greater_equal();

enum return_type builtin_rand();

#endif
