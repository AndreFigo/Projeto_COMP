#include "checks.h"
#include "semantics.h"

extern table_t *current_table, *global_table;
extern int semantic_error;

int check_header(ast_node_t *header)
{

    ast_node_t *current_node = header->fChild;

    current_table->name = strdup(current_node->token.text);

    current_node = current_node->nSibling;
    if (strcmp(current_node->node_name, "FuncParams"))
    {
        current_table->return_type = strdup(current_node->node_name);
        current_node = current_node->nSibling;
    }
    current_table->first = create_return_elem();

    //FuncParams node

    for (current_node = current_node->fChild; current_node; current_node = current_node->nSibling)
    {
        //criar table_elem
        if (!insert_elem_var(1, current_node))
        {
            //!deu erro
        }

        //add param
    }
}

int check_call(ast_node_t *node)
{
    //check id return type
    //check number of params and children
    ast_node_t *id_node = node->fChild;     // function name
    ast_node_t *params = id_node->nSibling; //params to search on table
    int params_given = 0, params_needed = 0;

    if (!id_node->is_func)
        return 1;

    //check params (childs) in the AST
    for (; params; params = params->nSibling)
        params_given++;

    //search the params on the table
    for (param_t *aux = id_node->elem->params; aux; aux = aux->next)
        params_needed++;

    if (params_given != params_needed)
    {
        //!erro
    }
    else
    {
        // if the params number are equal, checks if they have the same type
        param_t *aux = id_node->elem->params;
        params = id_node->nSibling;
        while (params)
        {
            if (strcmp(params->type, aux->type))
            {
                //!erro
                semantic_error = 1;
                return 1;
            }
            params = params->nSibling;
            aux = aux->next;
        }
    }
    if (strcmp(id_node->type, "none"))
        node->type = strdup(id_node->type);
    return 0;
}

int check_logical_operators(ast_node_t *node)
{
    ast_node_t *left_node = node->fChild;         //id name
    ast_node_t *right_node = left_node->nSibling; //expression
    if (strcmp(left_node->type, right_node->type))
    {
        //!erro invalid type
        return 1;
    }
    node->type = strdup("Bool");
    return 0;
}

int check_arithmetic_operators(ast_node_t *node)
{
    ast_node_t *left_node = node->fChild;         //id name
    ast_node_t *right_node = left_node->nSibling; //expression
    if (strcmp(left_node->type, right_node->type))
    {
        //!erro invalid type
        return 1;
    }
    node->type = strdup(left_node->type);
    return 0;
}

int check_unary_operator(ast_node_t *node)
{
    ast_node_t *child_node = node->fChild; //id name

    node->type = strdup(child_node->type);
    return 0;
}

int check_parse_args(ast_node_t *node)
{
    ast_node_t *left_node = node->fChild;         //id name
    ast_node_t *right_node = left_node->nSibling; //expression
    if (strcmp(left_node->type, "Int") || strcmp(right_node->type, "Int"))
    {
        //!erro invalid type
        return 1;
    }
    node->type = strdup("Int");
    return 0;
}

int check_assign(ast_node_t *node)
{
    ast_node_t *id_node = node->fChild;        //id name
    ast_node_t *expr_node = id_node->nSibling; //expression

    if (id_node == NULL || expr_node == NULL)
    {
        return 1;
    }

    if (id_node->is_func)
    {
        //!invalid id
        return 1;
    }

    if (strcmp(id_node->type, expr_node->type))
    {
        //!erro invalid type
        return 1;
    }

    node->type = strdup(id_node->type);
    return 0;
}

int check_body(ast_node_t *node)
{
    if (!strcmp(node->node_name, "FuncBody"))
    {
        if (node->fChild)
            check_body(node->fChild);
    }

    else if (!strcmp(node->node_name, "VarDecl"))
    {
        if (insert_elem_var(0, node))
        {
            //!deu erro
        }
        //add to current table
    }
    else if (!strcmp(node->node_name, "If"))
    {
        if (node->fChild)
            check_body(node->fChild);
    }
    else if (!strcmp(node->node_name, "For"))
    {
        if (node->fChild)
            check_body(node->fChild);
    }
    else if (!strcmp(node->node_name, "Print"))
    {
        //nothing to do
        check_body(node->fChild);
    }
    else if (!strcmp(node->node_name, "Return"))
    {
        if (node->fChild)
            check_body(node->fChild);
    }
    else if (!strcmp(node->node_name, "ParseArgs"))
    {
        check_body(node->fChild);
        check_parse_args(node);
    }
    else if (!strcmp(node->node_name, "Block"))
    {
        if (node->fChild)
            check_body(node->fChild);
    }
    else if (!strcmp(node->node_name, "Or"))
    {
        check_body(node->fChild);
        check_logical_operators(node);
    }
    else if (!strcmp(node->node_name, "And"))
    {
        check_body(node->fChild);
        check_logical_operators(node);
    }
    else if (!strcmp(node->node_name, "Eq"))
    {
        check_body(node->fChild);
        check_logical_operators(node);
    }
    else if (!strcmp(node->node_name, "Ne"))
    {
        check_body(node->fChild);
        check_logical_operators(node);
    }
    else if (!strcmp(node->node_name, "Lt"))
    {
        check_body(node->fChild);
        check_logical_operators(node);
    }
    else if (!strcmp(node->node_name, "Gt"))
    {
        check_body(node->fChild);
        check_logical_operators(node);
    }
    else if (!strcmp(node->node_name, "Le"))
    {
        check_body(node->fChild);
        check_logical_operators(node);
    }
    else if (!strcmp(node->node_name, "Ge"))
    {
        check_body(node->fChild);
        check_logical_operators(node);
    }
    else if (!strcmp(node->node_name, "Add"))
    {
        check_body(node->fChild);
        check_arithmetic_operators(node);
    }
    else if (!strcmp(node->node_name, "Sub"))
    {
        check_body(node->fChild);
        check_arithmetic_operators(node);
    }
    else if (!strcmp(node->node_name, "Mul"))
    {
        check_body(node->fChild);
        check_arithmetic_operators(node);
    }
    else if (!strcmp(node->node_name, "Div"))
    {
        check_body(node->fChild);
        check_arithmetic_operators(node);
    }
    else if (!strcmp(node->node_name, "Mod"))
    {
        check_body(node->fChild);
        check_arithmetic_operators(node);
    }
    else if (!strcmp(node->node_name, "Not")) //1
    {
        check_body(node->fChild);
        check_unary_operator(node);
    }
    else if (!strcmp(node->node_name, "Minus")) //1
    {
        check_body(node->fChild);
        check_unary_operator(node);
    }
    else if (!strcmp(node->node_name, "Plus")) //1
    {

        check_body(node->fChild);
        check_unary_operator(node);
    }
    else if (!strcmp(node->node_name, "Assign"))
    {
        check_body(node->fChild);
        check_assign(node);
    }
    else if (!strcmp(node->node_name, "Call"))
    {
        check_body(node->fChild);

        check_call(node);
    }
    else if (!strcmp(node->node_name, "IntLit"))
    {
        node->type = strdup("Int");
    }
    else if (!strcmp(node->node_name, "RealLit"))
    {
        node->type = strdup("Float32");
    }
    else if (!strcmp(node->node_name, "StrLit"))
    {
        node->type = strdup("String");
    }
    else if (!strcmp(node->node_name, "Id"))
    {
        //check table
        if (search_table(node))
        {
            //!error
        }
    }

    if (node->nSibling)
        check_body(node->nSibling);
}