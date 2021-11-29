#ifndef STRUCTURES_H
#define STRUCTURES_H

typedef struct token
{
    char *text;
    int n_line;
    int n_col;
} token_t;

typedef struct param param_t;
struct param
{
    char *type;
    param_t *next;
};

typedef struct table_elem table_elem_t;
struct table_elem
{
    char *name;
    char *type;
    param_t *params;
    int is_param;
    int is_func;
    int is_used;

    table_elem_t *next;
};

typedef struct table table_t;
struct table
{
    char *name;
    int is_global;
    param_t *params;
    char *return_type;

    table_elem_t *first;

    table_t *next;
};

typedef struct ast_node ast_node_t;
struct ast_node
{
    char *node_name;
    char *type;
    int is_func;
    table_elem_t *elem;
    token_t token;        //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    ast_node_t *fChild;   // first child
    ast_node_t *nSibling; // next sibling
};
#endif