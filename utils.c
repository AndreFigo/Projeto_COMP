#include "utils.h"
#include "y.tab.h"
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

token_t create_token(char *text, int line, int col, int token_type)
{
    token_t t;
    t.n_col = col;
    t.n_line = line;
    //!!!!
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

int str_len_llvm(char *str)
{
    int count = 0, i = 0;
    while (str[i] != 0)
    {
        if (str[i++] == '\\')
            count -= 2;
        count++;
    }
    return count;
}

char *remove_double_quotes(char *str)
{
    // printf("%s\n", str);
    char *string = (char *)malloc(strlen(str) * sizeof(char) * 2 + 1);
    int i = 1, j = 0;
    int barra = 0;
    char result[5];
    while (str[i] != 0)
    {
        if (barra)
        {

            barra = 0;
            if (str[i] == 'n')
            {
                *(string + j++) = '0';
                *(string + j++) = 'A';
            }
            if (str[i] == 'r')
            {
                *(string + j++) = '0';
                *(string + j++) = 'D';
            }
            if (str[i] == 't')
            {
                *(string + j++) = '0';
                *(string + j++) = '9';
            }
            if (str[i] == 'f')
            {
                *(string + j++) = '0';
                *(string + j++) = 'C';
            }
            if (str[i] == '\\')
            {
                *(string + j++) = '5';
                *(string + j++) = 'C';
            }
            if (str[i] == '\"')
            {
                *(string + j++) = '2';
                *(string + j++) = '2';
            }
            i++;

            // printf("%c\n", str[i]);
        }
        else
        {

            if (str[i] == '%')
            {
                *(string + j++) = '%';
                *(string + j++) = str[i++];
            }

            if (str[i] == '\\')
            {

                //*(string + j++) = '\\';
                *(string + j++) = str[i++];
                barra = 1;
            }

            else
            {
                *(string + j++) = str[i++];
            }
        }
    }

    *(string + j - 1) = 0;
    // printf("%s\n", string);
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