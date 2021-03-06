#ifndef _STANDARD_H_
#define _STANDARD_H_

enum return_type builtin_equal_val();
enum return_type builtin_int2float();
enum return_type builtin_float2int();

enum return_type builtin_catch();
enum return_type builtin_throw();
enum return_type builtin_errmsg();

enum return_type builtin_match();

enum return_type builtin_when();

enum return_type builtin_sym2id();
enum return_type builtin_str2sym();

enum return_type builtin_apply();

#endif // !