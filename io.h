#ifndef _IO_H_
#define _IO_H_

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "data.h"

extern char *buffer;

void set_buffer(char *s);

i64 read_i64();
f64 read_f64();

char *drop_shell(char *s);
char *clone(char *s);

#endif