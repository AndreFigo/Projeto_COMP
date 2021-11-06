#include "utils.h"
#include "y.tab.h"

token_t create_token(char *text, int line, int col, int token_type)
{
    token_t t;
    t.n_col = col;
    t.n_line = line;
    if (token_type == INTLIT || token_type == STRLIT || token_type == REALLIT || token_type == ID || token_type == RESERVED)
    {
        t.text = (char *)strdup(text);
    }
    return t;
}
