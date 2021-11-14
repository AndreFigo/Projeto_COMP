#ifndef UTILS_H
#define UTILS_H

#include <string.h>
#include <stdarg.h>
#include "structures.h"

token_t create_token(char *text, int line, int col, int token_type);

#endif