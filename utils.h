#ifndef UTILS_H
#define UTILS_H

#include <string.h>

typedef struct Token
{
    char *text;
    int n_line;
    int n_col;
} token_t;

token_t create_token(char *text, int line, int col, int token_type);

#endif