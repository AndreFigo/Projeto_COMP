#include "semantics.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "utils.h"
#include "checks.h"
#include "AST.h"

extern table_t *current_table, *global_table;
extern int semantic_error;

void free_params(param_t *params)
{
    if (params->next)
        free_params(params->next);
    if (params->type)
        free(params->type);
    free(params);
}

void free_table_elems(table_elem_t *elem)
{

    if (elem->next)
        free_table_elems(elem->next);
    if (elem->name)
        free(elem->name);
    if (elem->type)
        free(elem->type);
    if (elem->params)
        free_params(elem->params);
    free(elem);
}

void free_tables(table_t *table)
{
    if (table->next)
        free_tables(table->next);
    // if (table->params)
    //     free_params(table->params);
    if (table->first)
        free_table_elems(table->first);
    if (table->name)
        free(table->name);
    if (table->return_type)
        free(table->return_type);

    free(table);
}

table_t *create_table(int global)
{
    table_t *newTable = (table_t *)malloc(sizeof(table_t));

    if (!newTable)
        return NULL;

    newTable->is_global = global;
    newTable->name = NULL;
    newTable->params = NULL;
    newTable->return_type = strdup("none");
    newTable->next = NULL;
    newTable->first = NULL;

    return newTable;
}

void add_table(table_t *table, ast_node_t *node)
{
    // add table to list
    // add function to global table
    if (!insert_elem_func())
    {

        table_t *aux = global_table;
        for (; aux->next; aux = aux->next)
            ;

        aux->next = table;
    }
}
int search_table(ast_node_t *node)
{

    // 1 = error and 0 = valid
    // search current
    if (current_table->first != NULL)
    {
        table_elem_t *aux = current_table->first;
        for (; aux; aux = aux->next)
        {
            if (!strcmp(node->token.text, aux->name))
            {
                if (aux->is_func)
                {
                    node->elem = aux;
                    node->is_func = 1;
                }
                if (node->type)
                    free(node->type); //!!!!!
                node->type = strdup(aux->type);
                aux->is_used = 1;
                return 0;
            }
        }
    }
    // then search global
    if (global_table->first != NULL)
    {
        table_elem_t *aux = global_table->first;
        for (; aux; aux = aux->next)
        {
            if (!strcmp(node->token.text, aux->name))
            {
                if (aux->is_func)
                {
                    node->elem = aux;
                    node->is_func = 1;
                }
                if (node->type)
                    free(node->type);
                node->type = strdup(aux->type);
                aux->is_used = 1;

                return 0;
            }
        }
    }
    if (node->type)
        free(node->type);
    node->type = strdup("undef");
    node->not_found = 1;
    return 1;
}

table_t *find_table(ast_node_t *func_header)
{

    table_t *aux = global_table->next;

    for (; aux; aux = aux->next)
    {
        if (!strcmp(aux->name, func_header->fChild->token.text))
        {
            return aux;
        }
    }
    return NULL;
}

void find_unused(table_t *table)
{

    for (; table; table = table->next)
    {
        for (table_elem_t *elem = table->first; elem; elem = elem->next)
        {
            if (!elem->is_param && !elem->is_used && strcmp(elem->name, "return"))
            {
                print_symbol_declared_but_never_used(elem->line, elem->col, elem->name);
            }
        }
    }
}

int insert_elem_func()
{

    table_elem_t *new_elem = (table_elem_t *)malloc(sizeof(table_elem_t));

    if (!new_elem)
        return 1;

    new_elem->is_used = 0;
    new_elem->is_param = 0;
    new_elem->is_func = 1;
    new_elem->type = strdup(current_table->return_type);
    new_elem->name = strdup(current_table->name);
    new_elem->next = NULL;
    new_elem->params = current_table->params;
    new_elem->col = 0;
    new_elem->line = 0;

    // !not a copy!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    if (!global_table->first)
        global_table->first = new_elem;
    else
    {
        table_elem_t *aux;
        for (aux = global_table->first; aux->next; aux = aux->next)
        {
            if (!strcmp(new_elem->name, aux->name))
            {
                return 1;
            }
        }

        aux->next = new_elem;
    }

    return 0;
}

int insert_elem_var(int param, ast_node_t *node)
{
    // node is vardecl ou paramdecl
    // 0 = ok, 1=error
    table_elem_t *new_elem = (table_elem_t *)malloc(sizeof(table_elem_t));

    if (!new_elem)
        return 1;

    new_elem->is_used = 0;
    new_elem->is_param = param;
    new_elem->is_func = 0;
    new_elem->type = strdup(node->fChild->node_name);
    new_elem->name = strdup(node->fChild->nSibling->token.text);
    new_elem->next = NULL;
    new_elem->params = NULL;
    new_elem->col = node->fChild->nSibling->token.n_col;
    new_elem->line = node->fChild->nSibling->token.n_line;

    int erro = 0;

    table_elem_t *aux = current_table->first;
    if (aux == NULL)
        current_table->first = new_elem;
    else
    {
        for (; aux->next; aux = aux->next)
        {
            if (strcmp(aux->name, new_elem->name) == 0)
            {
                //! erro
                print_symbol_already_defined(node->fChild->nSibling->token);
                if (!param)
                    return 1;
                erro = 1;
            }
        }
        if (strcmp(aux->name, new_elem->name) == 0)
        {
            //! erro
            print_symbol_already_defined(node->fChild->nSibling->token);
            if (!param)
                return 1;
            erro = 1;
        }
        if (!erro)
            aux->next = new_elem;
    }
    if (param)
    {
        param_t *par = (param_t *)malloc(sizeof(param_t));
        if (par == NULL)
            return 1;

        par->type = strdup(node->fChild->node_name);
        par->next = NULL;
        param_t *aux = current_table->params;
        if (!aux)
        {
            current_table->params = par;
        }
        else
        {
            for (; aux->next; aux = aux->next)
                ;
            aux->next = par;
        }
    }
    return 0;
}

table_elem_t *create_return_elem()
{
    table_elem_t *new_elem = (table_elem_t *)malloc(sizeof(table_elem_t));

    new_elem->is_used = 0;
    new_elem->is_param = 0;
    new_elem->is_func = 0;
    new_elem->name = strdup("return");
    new_elem->next = NULL;
    new_elem->params = NULL;

    if (current_table->return_type)
        new_elem->type = strdup(current_table->return_type);
    else
        new_elem->type = strdup("none");

    return new_elem;
}

void create_symtab(ast_node_t *node)
{
    if (!strcmp(node->node_name, "Program"))
    {
        // cria table global
        // ver os filhos e adicionar na tabela
        global_table = current_table = create_table(1);
        if (node->fChild)
            create_symtab(node->fChild);
    }
    else if (!strcmp(node->node_name, "FuncDecl"))
    {
        // create new table
        current_table = create_table(0);
        // ver func header para preencher o no da tabela
        if (!check_header(node->fChild))
        {

            add_table(current_table, node);
        }
        // add to table list
        // add func to global table
        // percorrer o func body e preencher os elems da tabela
        current_table = global_table;
    }
    else if (!strcmp(node->node_name, "VarDecl"))
    {
        // add to current table
        insert_elem_var(0, node);
    }
    if (node->nSibling)
        create_symtab(node->nSibling);
}

void check_symtab(ast_node_t *node)
{

    if (!strcmp(node->node_name, "Program"))
    {
        // cria table global
        // ver os filhos
        if (node->fChild)
            check_symtab(node->fChild);
    }
    else if (!strcmp(node->node_name, "FuncDecl"))
    {
        // create new table

        if (node->fChild->type == NULL)
        {

            current_table = find_table(node->fChild);
            // ver func header para preencher o no da tabela

            if (current_table)
                check_body(node->fChild->nSibling);
            // add to table list
            // add func to global table
            // percorrer o func body e preencher os elems da tabela
            current_table = global_table;
        }
    }

    if (node->nSibling)
        check_symtab(node->nSibling);
}

void print_table(table_t *table)
{
    param_t *par;
    if (table->is_global)
        printf("===== Global Symbol Table =====\n");
    else
    {
        par = table->params;
        printf("===== Function %s(", table->name);
        if (par)
        {
            for (; par->next; par = par->next)
                printf("%s,", to_lower_case(par->type));
            printf("%s", to_lower_case(par->type));
        }
        printf(") Symbol Table =====\n");
    }

    table_elem_t *elem = table->first;
    for (; elem; elem = elem->next)
    {
        printf("%s\t", elem->name);

        if (elem->is_func)
        {
            printf("(");
            if (elem->params)
            {
                for (par = elem->params; par->next; par = par->next)
                    printf("%s,", to_lower_case(par->type));

                printf("%s", to_lower_case(par->type));
            }

            printf(")");
        }
        printf("\t%s", to_lower_case(elem->type));
        if (elem->is_param)
            printf("\tparam");

        printf("\n");
    }
}

void print_tables()
{
    table_t *aux = global_table;
    for (; aux; aux = aux->next)
    {
        print_table(aux);
        printf("\n");
    }
}

void print_symbol_already_defined(token_t token)
{
    printf("Line %d, column %d: Symbol %s already defined\n", token.n_line, token.n_col, token.text);
    semantic_error = 1;
}

void print_cannot_find_symbol(token_t token)
{
    printf("Line %d, column %d: Cannot find symbol %s\n", token.n_line, token.n_col, token.text);
    semantic_error = 1;
}

void print_cannot_find_symbol_func(ast_node_t *node, ast_node_t *params_nodes)
{
    // TODO: REVIEW THIS
    printf("Line %d, column %d: Cannot find symbol %s(", node->token.n_line, node->token.n_col, node->token.text);
    if (node)
    {
        ast_node_t *param = params_nodes;
        if (param)
        {
            for (; param->nSibling; param = param->nSibling)
            {
                printf("%s,", to_lower_case(param->type));
            }

            printf("%s", to_lower_case(param->type));
        }
    }
    printf(")\n");
    semantic_error = 1;
}

void print_cannot_be_applied_to_type(token_t token, char *type)
{
    printf("Line %d, column %d: Operator %s cannot be applied to type %s\n", token.n_line, token.n_col, token.text, to_lower_case(type));
    semantic_error = 1;
}

void print_cannot_be_applied_to_types(token_t token, char *typeA, char *typeB)
{
    printf("Line %d, column %d: Operator %s cannot be applied to types %s, %s\n", token.n_line, token.n_col, token.text, to_lower_case(typeA), to_lower_case(typeB));
    semantic_error = 1;
}
void print_incompatible_type(token_t token, token_t child_token, char *type)
{
    printf("Line %d, column %d: Incompatible type %s in %s statement\n", child_token.n_line, child_token.n_col, to_lower_case(type), token.text);
    semantic_error = 1;
}

void print_symbol_declared_but_never_used(int line, int col, char *var)
{
    printf("Line %d, column %d: Symbol %s declared but never used\n", line, col, var);
    semantic_error = 1;
}
