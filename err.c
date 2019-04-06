#include "err.h"
#include <stdio.h>
#include <stdlib.h>

void err(char *s)
{
    fprintf(stderr, "stderr: %s\n", s);
    exit(0);
}

void parse_err(char *expect, char *encounter)
{
    fprintf(stderr, "parsing error: expected %s, encountered %s\n", expect, encounter);
    exit(0);
}

void runtime_err(char *expect, char *encounter)
{
    fprintf(stderr, "runtime error: expected %s, encountered %s\n", expect, encounter);
    exit(0);
}
