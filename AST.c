#include "AST.h"
#include "utils.h"
#include "utils.h"
extern int lexical_error, syntax_error;
extern int s_flag;
ast_node_t *create_node(char *node_name, token_t token)
{
    ast_node_t *new_node = (ast_node_t *)malloc(sizeof(ast_node_t));

    if (new_node == NULL)
        return NULL;

    new_node->token = token;
    new_node->node_name = strdup(node_name);
    new_node->nSibling = NULL;
    new_node->fChild = NULL;
    new_node->is_func = 0;
    new_node->not_found = 0;
    new_node->type = NULL;
    new_node->elem = NULL;

    return new_node;
}

void add_children(ast_node_t *parent, int n_children, ...)
{
    // printf("5\n");
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

            next_child = next_child->nSibling; // in case the child already has s   iblings
        }
    }
    va_end(args);
    // printf("6\n");
}

ast_node_t *add_siblings(ast_node_t *first, int n_siblings, ...)
{

    // printf("3\n");
    if (n_siblings < 0)
        return first;

    va_list args;
    va_start(args, n_siblings);

    ast_node_t *cur_sib = first, *next;

    if (first != NULL)
    {
        while (cur_sib->nSibling != NULL)
            cur_sib = cur_sib->nSibling;
    }

    for (int i = 0; i < n_siblings; i++)
    {
        next = va_arg(args, ast_node_t *);
        if (next && !first)
        {
            first = next;
            cur_sib = first;
        }
        else if (next)
        {
            cur_sib->nSibling = next;
            cur_sib = cur_sib->nSibling;
        }
    }

    va_end(args);
    return first;
    // printf("4\n");
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
    // printf("1\n");
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
        type = create_node(node->node_name, node->token);
        type->token.text = strdup(type->token.text);
        current->fChild = type;
        new_id = create_node("Id", vars->token);
        add_siblings(current->fChild, 1, new_id);
    }
    // printf("2\n");

    return first;
}

void free_ast(ast_node_t *node)
{
    if (node->fChild != NULL)
        free_ast(node->fChild);
    if (node->nSibling != NULL)
        free_ast(node->nSibling);
    if (node->token.text)
        free(node->token.text);

    if (node->node_name)
        free(node->node_name);
    if (node->type)
        free(node->type);

    free(node);
}

void print_ast_node(char *node_name, token_t tok, int depth)
{
    for (int i = 0; i < depth; i++)
        printf("..");
    printf("%s", node_name);
    if (!strcmp(node_name, "StrLit") || !strcmp(node_name, "RealLit") || !strcmp(node_name, "IntLit") || !strcmp(node_name, "Id"))
        printf("(%s)", tok.text);
    printf("\n");
}

void print_ast_node_anottated(ast_node_t *node, int depth)
{
    for (int i = 0; i < depth; i++)
        printf("..");
    printf("%s", node->node_name);
    if (!strcmp(node->node_name, "StrLit") || !strcmp(node->node_name, "RealLit") || !strcmp(node->node_name, "IntLit") || !strcmp(node->node_name, "Id"))
        printf("(%s)", node->token.text);

    if (node->is_func)
    {
        printf(" - (");
        table_elem_t *elem = node->elem;
        param_t *param = elem->params;
        if (param)
        {
            for (; param->next; param = param->next)
            {
                printf("%s,", to_lower_case(param->type));
            }
            printf("%s", to_lower_case(param->type));
        }
        printf(")");
    }
    else if (node->type && strcmp(node->type, "none"))
    {
        printf(" - %s", to_lower_case(node->type));
    }

    printf("\n");
}

void print_ast(ast_node_t *node, int depth)
{
    if (s_flag)
        print_ast_node_anottated(node, depth);
    else
        print_ast_node(node->node_name, node->token, depth);
    if (node->fChild != NULL)
        print_ast(node->fChild, depth + 1);
    if (node->nSibling != NULL)
        print_ast(node->nSibling, depth);
}

void print_program(ast_node_t *program)
{
    // if (program != NULL)
    if (syntax_error == 0 && lexical_error == 0 && program != NULL)
        print_ast(program, 0);
}
