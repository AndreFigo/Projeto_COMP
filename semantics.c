#include "semantics.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "utils.h"
#include "checks.h"

extern table_t *current_table, *global_table;
extern int semantic_error;

table_t *create_table(int global)
{
    table_t *newTable = (table_t *)malloc(sizeof(table_t));

    if (!newTable)
        return NULL;

    newTable->is_global = global;
    newTable->name = NULL;
    newTable->params = NULL;
    newTable->return_type = "none";
    newTable->next = NULL;
    newTable->first = NULL;

    return newTable;
}

int add_table(table_t *table)
{
    // add table to list
    table_t *aux = global_table;
    for (; aux->next; aux = aux->next)
    {
        if (aux->name && table->name && strcmp(table->name, aux->name) == 0)
        {
            // !: print error
            return 1;
        }
    }

    aux->next = table;
    //add function to global table
    insert_elem_func();
    return 0;
}
int search_table(ast_node_t *node)
{

    // 1 = error and 0 = valid
    //search current
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
                node->type = strdup(aux->type);
                aux->is_used = 1;
                return 0;
            }
        }
    }
    //then search global
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
                node->type = strdup(aux->type);
                aux->is_used = 1;

                return 0;
            }
        }
    }
    return 1;
}

int insert_elem_func()
{

    table_elem_t *new_elem = (table_elem_t *)malloc(sizeof(table_elem_t));

    if (!new_elem)
        return 1;

    new_elem->is_used = 0;
    new_elem->is_param = 0;
    new_elem->is_func = 1;
    new_elem->type = current_table->return_type;
    new_elem->name = current_table->name;
    new_elem->next = NULL;
    new_elem->params = current_table->params;

    // !not a copy!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    if (!global_table->first)
        global_table->first = new_elem;
    else
    {
        table_elem_t *aux;
        for (aux = global_table->first; aux->next; aux = aux->next)
            ;
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

    table_elem_t *aux = current_table->first;
    if (aux == NULL)
        current_table->first = new_elem;
    else
    {
        for (; aux->next; aux = aux->next)
        {
            if (strcmp(aux->name, new_elem->name) == 0)
            {
                return 1; //!error
            }
        }
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

int create_symtab(ast_node_t *node)
{
    if (!strcmp(node->node_name, "Program"))
    {
        //cria table global
        //ver os filhos e adicionar na tabela
        global_table = current_table = create_table(1);
        if (node->fChild)
            create_symtab(node->fChild);
    }
    else if (!strcmp(node->node_name, "FuncDecl"))
    {
        //create new table
        current_table = create_table(0);
        //ver func header para preencher o no da tabela
        check_header(node->fChild);
        if (add_table(current_table))
        {
            //!erro se estiver repetid
        }
        check_body(node->fChild->nSibling);
        //add to table list
        //add func to global table
        //percorrer o func body e preencher os elems da tabela
        current_table = global_table;
    }
    else if (!strcmp(node->node_name, "VarDecl"))
    {
        //create new table elem
        if (insert_elem_var(0, node))
        {
            //!deu erro
        }
        //add to current table
    }
    if (node->nSibling)
        create_symtab(node->nSibling);
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
