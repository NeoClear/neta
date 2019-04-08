#include "util.h"
#include <string.h>

i64 max(i64 a, i64 b)
{
    if (a > b)
        return a;
    return b;
}

i64 min(i64 a, i64 b)
{
    if (a < b)
        return a;
    return b;
}

boolean greater_s(char *a, char *b)
{
    if (strcmp(a, b) > 0)
        return true;
    return false;
}

boolean eq_s(char *a, char *b)
{
    if (strcmp(a, b) == 0)
        return true;
    return false;
}

boolean less_s(char *a, char *b)
{
    if (strcmp(a, b) < 0)
        return true;
    return false;
}

char *buffer;
int bp = 0;

char getchar_buffer()
{
    char r;
    r = buffer[bp];
    bp++;
    return r;
}

void set_buffer(char *s)
{
    buffer = s;
    bp = 0;
}

f64 read_f64()
{
    f64 ans = 0.0;
    f64 divide = 1.0;
    int flag = 0;
    f64 f = 1.0;
    int ch = getchar_buffer();
    while (!isdigit(ch)) {
        if (ch == '-')
            f = -1.0;
        ch = getchar_buffer();
    }
    while (isdigit(ch) || ch == '.') {
        if (ch == '.') {
            ch = getchar_buffer();
            flag = 1;
        }
        ans = ans * 10.0 + (f64)((ch - '0'));
        if (flag)
            divide *= 10.0;
        ch = getchar_buffer();
    }
    return ans * f / divide;
}

i64 read_i64()
{
    i64 ans = 0, f = 1;
    int ch = getchar_buffer();
    while (!isdigit(ch)) {
        if (ch == '-') {
            f = -1;
        }
        ch = getchar_buffer();
    }
    while (isdigit(ch)) {
        ans = ans * 10 + ch - '0';
        ch = getchar_buffer();
    }
    return ans * f;
}

char *drop_shell(char *s)
{
    char *n = (char *)malloc((strlen(s) - 1) * sizeof(char));
    for (int i = 0; i < strlen(s) - 2; i++) {
        n[i] = s[i + 1];
    }
    n[strlen(s) - 2] = '\0';
    return n;
}

char *clone(char *s)
{
    char *n = (char *)malloc((strlen(s) + 1) * sizeof(char));
    for (int i = 0; i < strlen(s); i++)
        n[i] = s[i];
    n[strlen(s)] = '\0';
    return n;
}

char *int2string(i64 i)
{
    char *s = (char *)malloc(sizeof(char) * inf24);
    sprintf(s, "%lld", i);
    char *ret = (char *)malloc(sizeof(char) * (strlen(s) + 1));
    free(s);
    return ret;
}
char *double2string(f64 f)
{
    char *s = (char *)malloc(sizeof(char) * inf24);
    sprintf(s, "%lf", f);
    char *ret = (char *)malloc(sizeof(char) * (strlen(s) + 1));
    free(s);
    return ret;
}