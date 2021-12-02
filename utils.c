#include "utils.h"
#include "y.tab.h"
#include <stdlib.h>
#include <ctype.h>

token_t create_token(char *text, int line, int col, int token_type)
{
    token_t t;
    t.n_col = col;
    t.n_line = line;

    t.text = strdup(text);

    return t;
}

char *get_content(char *str)
{

    char *string = (char *)malloc(strlen(str) * sizeof(char) + 1);
    int i = 0, j = 0;
    while (str[i++] != '(')
        ;
    while (str[i] != '\0')
        *(string + j++) = str[i++];

    *(string + j - 1) = 0;
    return string;
}

char *to_lower_case(char *str)
{
    char *lower = (char *)malloc(strlen(str) * sizeof(char) + 1);
    for (int i = 0; i < strlen(str) + 1; i++)
    {
        *(lower + i) = tolower(str[i]);
    }
    return lower;
}