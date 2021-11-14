#ifndef STRUCTURES_H
#define STRUCTURES_H

typedef struct token
{
    char *text;
    int n_line;
    int n_col;
} token_t;

typedef struct ast_node ast_node_t;
struct ast_node
{
    char *type;
    token_t token;        //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    ast_node_t *fChild;   // first child
    ast_node_t *nSibling; // next sibling
};

#endif