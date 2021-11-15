#include "AST.h"

extern int lexical_error, syntax_error;

ast_node_t *create_node(char *type, token_t token)
{
    ast_node_t *new_node = (ast_node_t *)malloc(sizeof(ast_node_t));

    if (new_node == NULL)
        return NULL;

    new_node->token = token;
    new_node->type = type;
    new_node->nSibling = NULL;
    new_node->fChild = NULL;

    return new_node;
}

void add_children(ast_node_t *parent, int n_children, ...)
{
    if (n_children < 0)
        return;
    va_list args;
    va_start(args, n_children);

    parent->fChild = va_arg(args, ast_node_t *);
    ast_node_t *cur_child = parent->fChild, *next_child;

    for (int i = 1; i < n_children; i++)
    {
        next_child = va_arg(args, ast_node_t *);
        while (next_child)
        {
            cur_child->nSibling = next_child;
            cur_child = cur_child->nSibling;

            next_child = next_child->nSibling; // in case the child already has siblings
        }
    }
    va_end(args);
}

void add_siblings(ast_node_t *first, int n_siblings, ...)
{

    if (n_siblings < 0)
        return;
    va_list args;
    va_start(args, n_siblings);

    ast_node_t *cur_sib = first, *next;

    while (cur_sib->nSibling != NULL)
        cur_sib = cur_sib->nSibling;

    for (int i = 0; i < n_siblings; i++)
    {
        next = va_arg(args, ast_node_t *);
        if (next)
        {
            cur_sib->nSibling = next;
            cur_sib = cur_sib->nSibling;
        }
    }

    va_end(args);
    return;
}

// ast_node_t *add_siblings(ast_node_t *first, int n_siblings, ...)
// {

//     if (n_siblings < 0)
//         return first;
//     va_list args;
//     va_start(args, n_siblings);
//     int i = 0;
//     if (first == NULL)
//     {
//         first = va_arg(args, ast_node_t *);
//         i = 1;
//     }
//     ast_node_t *cur_sib = first;

//     while (cur_sib->nSibling != NULL)
//         cur_sib = cur_sib->nSibling;

//     for (i; i < n_siblings; i++)
//     {
//         cur_sib->nSibling = va_arg(args, ast_node_t *);
//         cur_sib = cur_sib->nSibling;
//     }

//     va_end(args);
//     return first;
// }

ast_node_t *split_vardecl(ast_node_t *node, token_t vardecl_tok)
{

    if (node == NULL)
        return NULL;

    int n_vars = 0;
    ast_node_t *current = node, *first = NULL, *type, *vars = node, *new_id;

    while (current->nSibling != NULL)
    {
        n_vars++;
        current = current->nSibling;
    }

    for (int i = 0; i < n_vars; i++)
    {
        vars = vars->nSibling;
        if (first == NULL)
        {
            first = create_node("VarDecl", vardecl_tok);
            current = first;
        }
        else
        {
            current->nSibling = create_node("VarDecl", vardecl_tok);
            current = current->nSibling;
        }
        type = create_node(node->type, node->token);
        current->fChild = type;
        new_id = create_node("Id", vars->token);
        add_siblings(current->fChild, 1, new_id);
    }
    return first;
}

void free_ast(ast_node_t *node)
{
    if (node->fChild != NULL)
        free_ast(node->fChild);
    if (node->nSibling != NULL)
        free_ast(node->nSibling);
    if (node->type)
        free(node->type);
    free(node);
}

void print_ast_node(char *type, token_t tok, int depth)
{
    for (int i = 0; i < depth; i++)
        printf("..");
    printf("%s", type);
    if (tok.text != NULL)
        printf("(%s)", tok.text);
    printf("\n");
}

void print_ast(ast_node_t *node, int depth)
{
    print_ast_node(node->type, node->token, depth);
    if (node->fChild != NULL)
        print_ast(node->fChild, depth + 1);
    if (node->nSibling != NULL)
        print_ast(node->nSibling, depth);
}

void print_program(ast_node_t *program)
{
    if (syntax_error == 0 && lexical_error == 0 && program != NULL)
        print_ast(program, 0);
}
