#include "io.h"

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