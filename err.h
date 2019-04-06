#ifndef _ERR_H_
#define _ERR_H_

// Standard errors
void err(char *s);
// Parsing errors
void parse_err(char *expect, char *encounter);
// Runtime errors
void runtime_err(char *expect, char *encounter);

#endif