#include "err.h"
#include <stdio.h>
#include <stdlib.h>

// Print standard error
void err(char *s)
{
    fprintf(stderr, "stderr: %s\n", s);
    exit(0);
}

// Print parse error
void parse_err(char *expect, char *encounter)
{
    fprintf(stderr, "parsing error: expected %s, encountered %s\n", expect, encounter);
    exit(0);
}

// Print runtime error
void runtime_err(char *expect, char *encounter)
{
    fprintf(stderr, "runtime error: expected %s, encountered %s\n", expect, encounter);
    exit(0);
}

void code_incomplete_err()
{
    fprintf(stderr, "Code Incomplete\n");
    exit(0);
}