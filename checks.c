#include "checks.h"
#include "semantics.h"

extern table_t *current_table, *global_table;
extern int semantic_error;

int check_header(ast_node_t *header)
{

    ast_node_t *current_node = header->fChild;

    current_table->name = strdup(current_node->token.text);

    // add table to list
    //?????????? TO REVIEW ??????????????
    table_t *aux = global_table;
    for (; aux->next; aux = aux->next)
    {
        if (aux->name && current_table->name && strcmp(current_table->name, aux->name) == 0)
        {
            // !print error
            print_symbol_already_defined(header->fChild->token);
            return 1;
        }
    }
    if (aux->name && current_table->name && strcmp(current_table->name, aux->name) == 0)
    {
        // !print error
        print_symbol_already_defined(header->fChild->token);
        return 1;
    }

    current_node = current_node->nSibling;
    if (strcmp(current_node->node_name, "FuncParams"))
    {
        current_table->return_type = strdup(current_node->node_name);
        current_node = current_node->nSibling;
    }
    current_table->first = create_return_elem();

    // FuncParams node

    for (current_node = current_node->fChild; current_node; current_node = current_node->nSibling)
    {
        // criar table_elem
        if (insert_elem_var(1, current_node))
        {
            //! deu erro  done
        }

        // add param
    }
    return 0;
}

int check_call(ast_node_t *node)
{
    // check id return type
    // check number of params and children
    ast_node_t *id_node = node->fChild;     // function name
    ast_node_t *params = id_node->nSibling; // params to search on table
    int params_given = 0, params_needed = 0;

    printf("id node %s %s\n", id_node->token.text, id_node->type);
    if (!strcmp(id_node->type, "undef"))
    {
        print_cannot_find_symbol_func(id_node, id_node->nSibling); // diferente numero
        node->type = strdup("undef");
        return 1;
    }

    if (!id_node->is_func)
        return 1;

    // check params (childs) in the AST
    for (; params; params = params->nSibling)
        params_given++;

    // search the params on the table
    for (param_t *aux = id_node->elem->params; aux; aux = aux->next)
        params_needed++;

    if (params_given != params_needed)
    {
        //! erro
        print_cannot_find_symbol_func(id_node, id_node->nSibling); // diferente numero
        id_node->type = strdup("undef");
        node->type = strdup("undef");

        return 1;
    }
    else
    {
        // if the params number are equal, checks if they have the same type
        param_t *aux = id_node->elem->params;
        params = id_node->nSibling;
        while (params)
        {
            if (strcmp(params->type, aux->type)) // or one is undef?
            {
                //! erro
                print_cannot_find_symbol_func(id_node, id_node->nSibling); // diferentes tipos de dados
                id_node->type = strdup("undef");
                node->type = strdup("undef");
                return 1;
            }
            params = params->nSibling;
            aux = aux->next;
        }
    }
    if (strcmp(id_node->type, "none")) // ???? REVIEW
        node->type = strdup(id_node->type);
    return 0;
}

int check_logical_operators(ast_node_t *node)
{
    ast_node_t *left_node = node->fChild;         // id name
    ast_node_t *right_node = left_node->nSibling; // expression

    if ((!strcmp(node->node_name, "And") || !strcmp(node->node_name, "Or")) && (strcmp(left_node->type, right_node->type) || strcmp(left_node->type, "Bool")))
    {
        //! erro invalid type
        print_cannot_be_applied_to_types(node->token, left_node->type, right_node->type);
        node->type = strdup("undef");
        return 1;
    }
    else if ((!strcmp(node->node_name, "Eq") || !strcmp(node->node_name, "Ne")) && ((strcmp(left_node->type, right_node->type)) || !strcmp(left_node->type, "undef") || !strcmp(left_node->type, "none")))
    {
        //! erro invalid type
        print_cannot_be_applied_to_types(node->token, left_node->type, right_node->type);
        node->type = strdup("undef");
        return 1;
    }
    else if (
        (!strcmp(node->node_name, "Lt") || !strcmp(node->node_name, "Le") || !strcmp(node->node_name, "Gt") || !strcmp(node->node_name, "Ge")) && (strcmp(left_node->type, right_node->type) ||
                                                                                                                                                   (strcmp(left_node->type, "Int") && strcmp(left_node->type, "Float32"))))
    {
        //! erro invalid type
        print_cannot_be_applied_to_types(node->token, left_node->type, right_node->type);
        node->type = strdup("undef");
        return 1;
    }
    node->type = strdup("Bool");
    return 0;
}

int check_arithmetic_operators(ast_node_t *node)
{
    // printf("1\n");
    ast_node_t *left_node = node->fChild;         // id name
    ast_node_t *right_node = left_node->nSibling; // expression
    // add - tudo excepto none e undef
    // mul, div, mod, sub  - tudo excepto none, string, undef
    // printf("%s\n", node->node_name);
    // printf("7\n");
    // printf("%s\n", left_node->type);
    // printf("8\n");
    // printf("%s\n", right_node->type);
    // printf("9\n");
    if (!strcmp(node->node_name, "Add") && (strcmp(left_node->type, right_node->type) || (!strcmp(left_node->type, "none") || !strcmp(left_node->type, "undef") || !strcmp(left_node->type, "Bool"))))
    {
        // printf("2\n");

        print_cannot_be_applied_to_types(node->token, left_node->type, right_node->type);
        node->type = strdup("undef");
        return 1;
    }
    else if ((!strcmp(node->node_name, "Sub") || !strcmp(node->node_name, "Mul") || !strcmp(node->node_name, "Div") || !strcmp(node->node_name, "Mod")) && (strcmp(left_node->type, right_node->type) || !strcmp(left_node->type, "none") || !strcmp(left_node->type, "undef") || !strcmp(left_node->type, "String") || !strcmp(left_node->type, "Bool")))
    {
        // printf("3\n");

        //! erro invalid type
        print_cannot_be_applied_to_types(node->token, left_node->type, right_node->type);
        node->type = strdup("undef");
        return 1;
    }
    // printf("4\n");

    node->type = strdup(left_node->type);
    return 0;
}

int check_unary_operator(ast_node_t *node)
{
    ast_node_t *child_node = node->fChild; // id name
    if (!strcmp(node->node_name, "Not") && strcmp(child_node->type, "Bool"))
    {
        //! erro
        print_cannot_be_applied_to_type(node->token, child_node->type);
        node->type = strdup("undef");
        return 1;
    }
    else if ((!strcmp(node->node_name, "Plus") || !strcmp(node->node_name, "Minus")) && strcmp(child_node->type, "Int") && strcmp(child_node->type, "Float32"))
    {
        print_cannot_be_applied_to_type(node->token, child_node->type);
        node->type = strdup("undef");
        return 1;
    }
    node->type = strdup(child_node->type);
    return 0;
}

int check_parse_args(ast_node_t *node)
{
    ast_node_t *left_node = node->fChild;         // id name
    ast_node_t *right_node = left_node->nSibling; // expression
    if (strcmp(left_node->type, "Int") || strcmp(right_node->type, "Int"))
    {
        //! erro invalid type
        print_cannot_be_applied_to_types(node->token, left_node->type, right_node->type);
        node->type = strdup("undef");
        return 1;
    }
    node->type = strdup("Int");
    return 0;
}

int check_assign(ast_node_t *node)
{
    ast_node_t *id_node = node->fChild;        // id name
    ast_node_t *expr_node = id_node->nSibling; // expression

    if (id_node == NULL || expr_node == NULL)
    {
        return 1;
    }

    if (id_node->is_func)
    {
        //! invalid id
        print_cannot_find_symbol(id_node->token);
        id_node->type = strdup("undef");
    }

    if (strcmp(id_node->type, expr_node->type) || !strcmp(id_node->type, "undef") || !strcmp(id_node->type, "none"))
    {
        // !erro invalid type
        print_cannot_be_applied_to_types(node->token, id_node->type, expr_node->type);
        node->type = strdup("undef");
        return 1;
    }

    node->type = strdup(id_node->type);
    return 0;
}
int check_statements(ast_node_t *node)
{
    ast_node_t *child_node = node->fChild;

    if ((!strcmp(node->node_name, "For") || !strcmp(node->node_name, "If")) && strcmp(child_node->type, "Bool"))
    {
        // !erro
        print_incompatible_type(node->token, child_node->type);
        return 1;
    }
    else if (!strcmp(node->node_name, "Print") && (!strcmp(child_node->type, "undef")))
    {
        // !erro
        print_incompatible_type(node->token, child_node->type);
        return 1;
    }
    else if (!strcmp(node->node_name, "Return"))
    {
        if (child_node == NULL && strcmp(current_table->return_type, "none"))
        {

            print_incompatible_type(node->token, "none");
            return 1;
        }
        else if (child_node != NULL && strcmp(current_table->return_type, child_node->type))
        {
            print_incompatible_type(node->token, child_node->type);
            return 1;
        }
    }
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
            //! deu erro
        }
        // add to current table
    }
    else if (!strcmp(node->node_name, "If"))
    {

        if (node->fChild)
            check_body(node->fChild);
        check_statements(node);
    }
    else if (!strcmp(node->node_name, "For"))
    {
        if (node->fChild)
            check_body(node->fChild);
        check_statements(node);
    }

    else if (!strcmp(node->node_name, "Print"))
    {
        // nothing to do
        check_body(node->fChild);
        check_statements(node);
    }
    else if (!strcmp(node->node_name, "Return"))
    {
        if (node->fChild)
            check_body(node->fChild);
        check_statements(node);
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
    else if (!strcmp(node->node_name, "Not")) // 1
    {
        check_body(node->fChild);
        check_unary_operator(node);
    }
    else if (!strcmp(node->node_name, "Minus")) // 1
    {
        check_body(node->fChild);
        check_unary_operator(node);
    }
    else if (!strcmp(node->node_name, "Plus")) // 1
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
        // check table
        if (search_table(node))
        {
            //! error
        }
    }

    if (node->nSibling)
        check_body(node->nSibling);
}