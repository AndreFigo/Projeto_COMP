#ifndef UTILS_H
#define UTILS_H

#include <string.h>
#include <stdarg.h>
#include "structures.h"

token_t create_token(char *text, int line, int col, int token_type);

char *get_content(char *str);
char *to_lower_case(char *str);
char *remove_double_quotes(char *str);

#endif