#include "err.h"
#include "def.h"
#include <stdio.h>
#include <stdlib.h>

enum error_type error_mode = STRICT;
boolean is_err = false;

// Print standard error
void err(char *s)
{
    fprintf(stderr, "stderr: %s\n", s);
    if (error_mode == STRICT)
        exit(0);
    is_err = true;
}

// Print parse error
void parse_err(char *expect, char *encounter)
{
    fprintf(stderr, "parsing error: expected %s, encountered %s\n", expect, encounter);
    if (error_mode == STRICT)
        exit(0);
    is_err = true;
}

// Print runtime error
void runtime_err(char *expect, char *encounter)
{
    fprintf(stderr, "runtime error: expected %s, encountered %s\n", expect, encounter);
    if (error_mode == STRICT)
        exit(0);
    is_err = true;
}

void code_incomplete_err()
{
    fprintf(stderr, "Code Incomplete\n");
    if (error_mode == STRICT)
        exit(0);
    is_err = true;
}