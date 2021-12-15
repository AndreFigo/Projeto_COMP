#include "codegen.h"

int var_counter = 0, returned = 0, string_counter = 0, in_flow = 0;
extern table_t *current_table, *global_table;

void print_global_strings(ast_node_t *node)
{

    if (!strcmp(node->node_name, "Print"))
    {
        if (!strcmp(node->fChild->type, "String"))
        {
            char *no_quotes = remove_double_quotes(node->fChild->token.text);
            printf("@.str%d= private unnamed_addr constant [%d x i8] c\"%s\\0A\\00\"\n", string_counter++, (int)strlen(no_quotes) + 2, no_quotes);
            free(no_quotes);
            char str[30];
            sprintf(str, ".str%d", string_counter - 1);
            node->fChild->llvm_name = string_counter - 1;
        }
    }

    if (node->fChild)
        print_global_strings(node->fChild);
    if (node->nSibling)
        print_global_strings(node->nSibling);
}

void print_init(ast_node_t *node)
{
    // print general info present in every file
    printf("declare i32 @putchar(...)\n");
    printf("declare i32 @getchar(...)\n");
    printf("@.strlit = private unnamed_addr constant [4 x i8] c\"%%s\\0A\\00\", align 1\n");
    printf("@.intlit = private unnamed_addr constant [4 x i8] c\"%%d\\0A\\00\", align 1\n");
    printf("@.reallit = private unnamed_addr constant [4 x i8] c\"%%.08f\\0A\\00\", align 1\n");
    printf("@.boollit= private unnamed_addr constant [4 x i8] c\"%%d\\0A\\00\", align 1\n");
    printf("declare i32 @atoi(...)\n");
    printf("declare i32 @printf(i8*, ...)\n\n");
    printf("@.strtrue = private unnamed_addr constant [6 x i8] c\"true\\0A\\00\"\n");
    printf("@.strfalse = private unnamed_addr constant [7 x i8] c\"false\\0A\\00\"\n");
    printf("define dso_local void @print_bool(i1) #0 {\n");
    printf("\t%%2 = alloca i1\n");
    printf("\tstore i1 %%0, i1* %%2\n");
    printf("\t%%3 = load i1, i1* %%2\n");
    printf("\t%%4 = icmp ne i1 %%3, 0\n");
    printf("\tbr i1 %%4, label %%true, label %%false\n");
    printf("true:\n");
    printf("\t%%5 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.strtrue, i32 0, i32 0))\n");
    printf("\tbr label %%end\n\n");
    printf("false:\n");
    printf("\t%%6 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.strfalse, i32 0, i32 0))\n");
    printf("\tbr label %%end\n\n");
    printf("end:\n");
    printf("\tret void\n");
    printf("}\n");

    print_global_strings(node);
}

int is_global(char *name)
{
    // 1 = global , 0 = local
    table_elem_t *elem = current_table->first;
    if (current_table != global_table)
    {
        for (; elem; elem = elem->next)
            if (!strcmp(elem->name, name))
                return 0;
    }

    elem = global_table->first;
    for (; elem; elem = elem->next)
        if (!strcmp(elem->name, name))
            return 1;

    return 0;
}

void add_llvm_name(char *var_name, int n_var)
{
    for (table_elem_t *elem = current_table->first; elem; elem = elem->next)
    {
        if (!strcmp(elem->name, var_name))
            elem->llvm_name = n_var;
    }
}

table_elem_t *search_table_llvm(char *name)
{
    for (table_elem_t *elem = current_table->first; elem; elem = elem->next)
    {
        if (!strcmp(elem->name, name))
            return elem;
    }
    for (table_elem_t *elem = global_table->first; elem; elem = elem->next)
    {
        if (!strcmp(elem->name, name))
            return elem;
    }
    return NULL;
}

char *llvm_var_type(ast_node_t *node)
{
    char *return_type;
    if (node == NULL)
    {
        return_type = strdup("void");
    }
    else if (!strcmp(node->node_name, "Int"))
    {
        return_type = strdup("i32");
    }
    else if (!strcmp(node->node_name, "Float32"))
    {
        return_type = strdup("double");
    }
    else if (!strcmp(node->node_name, "Bool"))
    {
        return_type = strdup("i1");
    }
    else if (!strcmp(node->node_name, "String"))
    {
        return_type = strdup("i8*");
    }
    return return_type;
}

char *llvm_node_type(ast_node_t *node)
{
    char *return_type;
    if (node == NULL)
    {
        return_type = strdup("void");
    }
    else if (!strcmp(node->type, "none"))
    {
        return_type = strdup("void");
    }
    else if (!strcmp(node->type, "Int"))
    {
        return_type = strdup("i32");
    }
    else if (!strcmp(node->type, "Float32"))
    {
        return_type = strdup("double");
    }
    else if (!strcmp(node->type, "Bool"))
    {
        return_type = strdup("i1");
    }
    else if (!strcmp(node->type, "String"))
    {
        return_type = strdup("i8*");
    }
    return return_type;
}

//!! to kill
void reset_params_llvm_name()
{
    table_elem_t *elem = current_table->first;
    for (; elem; elem = elem->next)
    {
        if (elem->is_param)
        {
            free(elem->llvm_name);
            elem->llvm_name = strdup(elem->name);
        }
    }
}

//! come back later
void update_params_llvm_name(int n_params)
{
    table_elem_t *elem = current_table->first;
    int aux = n_params + 1;
    for (; elem; elem = elem->next)
    {

        if (elem->is_param)
        {
            elem->llvm_name = aux++; ///! atençao
        }
    }
}

void codegen_func(ast_node_t *node)
{
    // funcdecl -> header , body
    // header -> id type? params
    // params -> paramDecl * -> type id
    // body -> declarations | statements

    ast_node_t *header = node->fChild;
    ast_node_t *body = header->nSibling;

    ast_node_t *id_node = header->fChild;
    ast_node_t *type_node = id_node->nSibling;
    ast_node_t *fParams;

    var_counter = 0;

    if (!strcmp(id_node->token.text, "main"))
    {
        printf("define i32 @main(i32 %%argc, i8** %%argv) {\n");

        current_table = find_table(header);
        var_counter++;
    }
    else
    {

        if (!strcmp(type_node->node_name, "FuncParams"))
        {
            fParams = type_node;
            type_node = NULL;
        }
        else
            fParams = type_node->nSibling;

        char *func_type = llvm_var_type(type_node);

        printf("define %s @%s(", func_type, id_node->token.text);
        free(func_type);

        ast_node_t *current_node = fParams->fChild;

        for (; current_node; current_node = current_node->nSibling)
        {
            // criar table_elem
            char *param_type = llvm_var_type(current_node->fChild);
            printf("%s ", param_type);
            if (current_node->nSibling)
                printf(", ");
            free(param_type);
            var_counter++; // increment params vouter
        }
        printf(")\n");

        // func body
        current_table = find_table(header);
        printf("{\n");
        var_counter++; // invisible label

        // TODO: allocate mem for params and update table elem
        current_node = fParams->fChild;
        char *type;
        int n_params = 0;
        for (; current_node; current_node = current_node->nSibling)
        {
            type = llvm_var_type(current_node->fChild);
            printf("\t%%%d = alloca %s\n", var_counter++, type);
            printf("\tstore %s %%%d, %s* %%%d\n", type, n_params, type, var_counter - 1);
            free(type);
            n_params++;
        }

        update_params_llvm_name(n_params);
    }

    if (body->fChild)
        codegen(body->fChild);

    if (!returned)
    {
        printf("ret void");
    }
    printf("}\n");
    returned = 0;

    // reset_params_llvm_name();  //no need
    current_table = global_table;
}

void codegen_var(ast_node_t *node)
{
    // vardecl -> type , id
    ast_node_t *type_node = node->fChild;
    ast_node_t *id_node = type_node->nSibling;

    // printf("a\n");

    if (current_table == global_table && type_node)
    {
        // printf("%s\n", type_node->node_name);
        if (!strcmp(type_node->node_name, "String"))
        {
            printf("@%s = global i8* null\n", id_node->token.text);
        }
        else if (!strcmp(type_node->node_name, "Int"))
        {
            printf("@%s = global i32 0\n", id_node->token.text);
        }
        else if (!strcmp(type_node->node_name, "Bool"))
        {
            printf("@%s = global i1 0\n", id_node->token.text);
        }
        else if (!strcmp(type_node->node_name, "Float32"))
        {
            printf("@%s = global double 0.000000e+00\n", id_node->token.text);
        }
    }
    else
    {
        if (!strcmp(type_node->node_name, "String"))
        {
            printf("\t%%%d = alloca i8*\n", var_counter++);
        }
        else if (!strcmp(type_node->node_name, "Int"))
        {
            printf("\t%%%d = alloca i32\n", var_counter++);
        }
        else if (!strcmp(type_node->node_name, "Bool"))
        {
            printf("\t%%%d = alloca i1\n", var_counter++);
        }
        else if (!strcmp(type_node->node_name, "Float32"))
        {
            printf("\t%%%d = alloca double\n", var_counter++);
        }
        // char num[10];
        // sprintf(num, "%d", var_counter - 1);
        // add_llvm_name(id_node->token.text, num);
        id_node->llvm_name = var_counter - 1;
        add_llvm_name(id_node->token.text, var_counter - 1);
    }
}

void codegen_for(ast_node_t *node)
{
}

void codegen_if(ast_node_t *node)
{
    // if
    ast_node_t *cond = node->fChild;
    ast_node_t *block_if = cond->nSibling;
    ast_node_t *block_else = block_if->nSibling;
    in_flow = 1;
    codegen(cond);

    // br
    codegen(block_if->fChild);

    codegen(block_else->fChild);
    // cond
    // block
    // block

    in_flow = 0;
}

void codegen_parseargs(ast_node_t *node)
{
    ast_node_t *left_child = node->fChild;
    ast_node_t *right_child = left_child->nSibling;
    codegen(left_child);

    char *type = llvm_node_type(left_child);

    // if (!strcmp(right_child->node_name, "Id") && is_global(right_child->token.text))
    // {
    //     printf("\t%%%d = load %s, %s* @%s\n", var_counter++, type, type, right_child->llvm_name);
    //     sprintf(num, "%d", var_counter - 1);
    //     op2 = strdup(num);
    // }
    // else if (!strcmp(right_child->node_name, "Id"))
    // {
    //     printf("\t%%%d = load %s, %s* %%%s\n", var_counter++, type, type, right_child->llvm_name);
    //     sprintf(num, "%d", var_counter - 1);
    //     op2 = strdup(num);
    // }
    // else
    // {
    //     op2 = strdup(right_child->llvm_name);
    // }

    // todo main args and parseagrs

    //%1 = getelementptr i8*, i8** %argv, i64 1
    //%2 = load i8*, i8** %1
    //%3 = call i32 (i8*, ...) bitcast (i32 (...)* @atoi to i32 (i8*, ...)*)(i8* %2)
    printf("\t%%%d = getelementptr i8*, i8** %%argv, i32 %%%d \n", var_counter++, right_child->llvm_name);
    printf("\t%%%d = load i8*, i8** %%%d\n", var_counter, var_counter - 1);
    var_counter++;
    printf("\t%%%d = call i32 (i8*, ...) bitcast (i32 (...)* @atoi to i32 (i8*, ...)*)(i8* %%%d)\n", var_counter, var_counter - 1);
    var_counter++;
    if (is_global(left_child->token.text))
        printf("\tstore i32 %%%d, i32* @%s\n", var_counter - 1, left_child->token.text);

    else
        printf("\tstore i32 %%%d, i32* %%%d\n", var_counter - 1, left_child->llvm_name);

    node->llvm_name = var_counter - 1; // maybe no need
}

void codegen_return(ast_node_t *node)
{
    ast_node_t *child_node = node->fChild;
    char *type = llvm_node_type(child_node);

    codegen(child_node);

    if (!strcmp(type, "void"))
    {
        printf("\tret void\n");
    }
    else
    {
        printf("\tret %s %%%d\n", type, child_node->llvm_name);
    }
    returned = 1;
}

void codegen_call(ast_node_t *node)
{
    // type da funcao
    // type dos filhos

    char *param_name;
    char num[10];
    char *type;
    ast_node_t *id_node = node->fChild;
    ast_node_t *params = id_node->nSibling;

    codegen(id_node);
    int var_counter_init = var_counter;

    // for (; params; params = params->nSibling)
    // {
    //     type = llvm_node_type(params);

    //     if (!strcmp(params->node_name, "Id") && is_global(params->token.text))
    //     {
    //         printf("\t%%%d = load %s, %s* @%s\n", var_counter++, type, type, params->token.text);
    //     }

    //     else if (!strcmp(params->node_name, "Id"))
    //     {
    //         printf("\t%%%d = load %s, %s* %%%d\n", var_counter++, type, type, params->llvm_name);
    //     }
    //     else
    //     {
    //         if (!strcmp(type, "i32") || !strcmp(type, "i1"))
    //             printf("\t%%%d = add  %s 0, %%%s\n", var_counter++, type, params->llvm_name);
    //         else if (!strcmp(type, "double"))
    //             printf("\t%%%d = fadd  %s 0, %%%s\n", var_counter++, type, params->llvm_name);

    //         // param_name = strdup(params->llvm_name);
    //     }

    //     free(type);
    // }
    type = llvm_node_type(node);

    if (!strcmp(type, "void"))
    {
        printf("\tcall %s @%s(", type, id_node->token.text);
    }
    else
    {
        printf("\t%%%d = call %s @%s(", var_counter++, type, id_node->token.text);
    }
    free(type);
    for (params = id_node->nSibling; params; params = params->nSibling)
    {
        type = llvm_node_type(params);

        if (params->nSibling)
            printf("%s %%%d,", type, params->llvm_name);
        else
            printf("%s %%%d", type, params->llvm_name);

        free(type);
    }
    printf(")\n");

    node->llvm_name = var_counter - 1;
}

void codegen_print(ast_node_t *node)
{
    ast_node_t *child_node = node->fChild;
    char *type = llvm_node_type(child_node);

    codegen(child_node);

    // if (!strcmp(child_node->node_name, "Id") && is_global(child_node->token.text))
    // {
    //     printf("\t%%%d = load %s, %s* @%s\n", var_counter++, type, type, child_node->llvm_name);
    // }

    // else if (!strcmp(child_node->node_name, "Id"))
    // {
    //     printf("\t%%%d = load %s, %s* %%%s\n", var_counter++, type, type, child_node->llvm_name);
    // }
    // else
    // {
    //     // no need
    // }

    // call i32(i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i32 0, i32 0), i32 %aux2)
    if (!strcmp(type, "i32"))
    {
        printf("\tcall i32(i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.intlit, i32 0, i32 0), i32 %%%d)\n", child_node->llvm_name);
        var_counter++
    }
    else if (!strcmp(type, "double"))
    {
        printf("\tcall i32(i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.reallit, i32 0, i32 0), double %%%d)\n", child_node->llvm_name);
        var_counter++
    }
    else if (!strcmp(type, "i1"))
    {
        // call void @print_bool(i1 %boo)
        printf("\tcall void @print_bool(i1 %%%d)\n", child_node->llvm_name);
    }
    else if (!strcmp(type, "i8*"))
    {

        printf("\tcall i32(i8*, ...) @printf(i8* getelementptr inbounds ([%d x i8], [%d x i8]* @.str%d, i32 0, i32 0))\n", (int)strlen(child_node->token.text), (int)strlen(child_node->token.text), child_node->llvm_name);
        var_counter++;
    }
}

void codegen_arithmetic(ast_node_t *node)
{
    ast_node_t *left_child = node->fChild;
    ast_node_t *right_child = left_child->nSibling;

    codegen(left_child);

    char *type = llvm_node_type(left_child);

    // if (!strcmp(left_child->node_name, "Id") && is_global(left_child->token.text))
    // {
    //     printf("\t%%%d = load %s, %s* @%s\n", var_counter++, type, type, left_child->llvm_name);
    //     sprintf(num, "%d", var_counter - 1);
    //     op1 = strdup(num);
    // }
    // else if (!strcmp(left_child->node_name, "Id"))
    // {
    //     printf("\t%%%d = load %s, %s* %%%s\n", var_counter++, type, type, left_child->llvm_name);
    //     sprintf(num, "%d", var_counter - 1);
    //     op1 = strdup(num);
    // }
    // else
    // {
    //     op1 = strdup(left_child->llvm_name);
    // }

    // if (!strcmp(right_child->node_name, "Id") && is_global(right_child->token.text))
    // {
    //     printf("\t%%%d = load %s, %s* @%s\n", var_counter++, type, type, right_child->llvm_name);
    //     sprintf(num, "%d", var_counter - 1);
    //     op2 = strdup(num);
    // }
    // else if (!strcmp(right_child->node_name, "Id"))
    // {
    //     printf("\t%%%d = load %s, %s* %%%s\n", var_counter++, type, type, right_child->llvm_name);
    //     sprintf(num, "%d", var_counter - 1);
    //     op2 = strdup(num);
    // }
    // else
    // {
    //     op2 = strdup(right_child->llvm_name);
    // }

    if (!strcmp(node->node_name, "Add"))
    {
        if (!strcmp(type, "i32"))
        {
            printf("\t%%%d = add i32 %%%d, %%%d\n", var_counter++, left_child->llvm_name, right_child->llvm_name);
        }
        else if (!strcmp(type, "double"))
        {
            printf("\t%%%d = fadd double %%%d, %%%d\n", var_counter++, left_child->llvm_name, right_child->llvm_name);
        }
        else
        {
            // TODO: add strings
        }
    }
    else if (!strcmp(node->node_name, "Sub"))
    {
        if (!strcmp(type, "i32"))
        {
            printf("\t%%%d = sub i32 %%%d, %%%d\n", var_counter++, left_child->llvm_name, right_child->llvm_name);
        }
        else if (!strcmp(type, "double"))
        {
            printf("\t%%%d = fsub double %%%d, %%%d\n", var_counter++, left_child->llvm_name, right_child->llvm_name);
        }
    }
    else if (!strcmp(node->node_name, "Mul"))
    {
        if (!strcmp(type, "i32"))
        {
            printf("\t%%%d = mul i32 %%%d, %%%d\n", var_counter++, left_child->llvm_name, right_child->llvm_name);
        }
        else if (!strcmp(type, "double"))
        {
            printf("\t%%%d = fmul double %%%d, %%%d\n", var_counter++, left_child->llvm_name, right_child->llvm_name);
        }
    }
    else if (!strcmp(node->node_name, "Div"))
    {
        if (!strcmp(type, "i32"))
        {
            printf("\t%%%d = sdiv i32 %%%d, %%%d\n", var_counter++, left_child->llvm_name, right_child->llvm_name);
        }
        else if (!strcmp(type, "double"))
        {
            printf("\t%%%d = fdiv double %%%d, %%%d\n", var_counter++, left_child->llvm_name, right_child->llvm_name);
        }
    }
    else if (!strcmp(node->node_name, "Mod"))
    {
        printf("\t%%%d = srem i32 %%%d, %%%d\n", var_counter++, left_child->llvm_name, right_child->llvm_name);
    }

    node->llvm_name = var_counter - 1;
}

void codegen_unary(ast_node_t *node)
{
    ast_node_t *child_node = node->fChild;

    codegen(child_node);

    char *type = llvm_node_type(child_node);

    // if (!strcmp(child_node->node_name, "Id") && is_global(child_node->token.text))
    // {
    //     printf("\t%%%d = load %s, %s* @%s\n", var_counter++, type, type, child_node->llvm_name);
    //     sprintf(num, "%d", var_counter - 1);
    //     child_name = strdup(num);
    // }
    // else if (!strcmp(child_node->node_name, "Id"))
    // {
    //     printf("\t%%%d = load %s, %s* %%%s\n", var_counter++, type, type, child_node->llvm_name);
    //     sprintf(num, "%d", var_counter - 1);
    //     child_name = strdup(num);
    // }
    // else
    // {
    //     child_name = strdup(child_node->llvm_name);
    // }

    if (!strcmp(node->node_name, "Not"))
    {
        printf("\t%%%d = xor i1 %%%d, 1\n", var_counter++, child_node->llvm_name);
    }
    else if (!strcmp(node->node_name, "Minus"))
    {
        if (!strcmp(type, "i32"))
            printf("\t%%%d = sub i32  0, %%%d", var_counter++, child_node->llvm_name);
        else
            printf("\t%%%d = fsub double 0.0, %%%d", var_counter++, child_node->llvm_name);
    }
    else if (!strcmp(node->node_name, "Plus"))
    {
        // nothing to do
        //! check if doesnt break
    }

    node->llvm_name = var_counter - 1;
}

void codegen_logical(ast_node_t *node)
{
    ast_node_t *left_child = node->fChild;
    ast_node_t *right_child = left_child->nSibling;

    codegen(left_child);

    char *type = llvm_node_type(left_child);

    // if (!strcmp(left_child->node_name, "Id") && is_global(left_child->token.text))
    // {
    //     printf("\t%%%d = load %s, %s* @%s\n", var_counter++, type, type, left_child->llvm_name);
    //     sprintf(num, "%d", var_counter - 1);
    //     op1 = strdup(num);
    // }
    // else if (!strcmp(left_child->node_name, "Id"))
    // {
    //     printf("\t%%%d = load %s, %s* %%%s\n", var_counter++, type, type, left_child->llvm_name);
    //     sprintf(num, "%d", var_counter - 1);
    //     op1 = strdup(num);
    // }
    // else
    // {
    //     op1 = strdup(left_child->llvm_name);
    // }

    // if (!strcmp(right_child->node_name, "Id") && is_global(right_child->token.text))
    // {
    //     printf("\t%%%d = load %s, %s* @%s\n", var_counter++, type, type, right_child->llvm_name);
    //     sprintf(num, "%d", var_counter - 1);
    //     op2 = strdup(num);
    // }
    // else if (!strcmp(right_child->node_name, "Id"))
    // {
    //     printf("\t%%%d = load %s, %s* %%%s\n", var_counter++, type, type, right_child->llvm_name);
    //     sprintf(num, "%d", var_counter - 1);
    //     op2 = strdup(num);
    // }
    // else
    // {
    //     op2 = strdup(right_child->llvm_name);
    // }

    if (!strcmp(node->node_name, "Or"))
    {
        printf("\t%%%d = or i1 %%%d, %%%d\n", var_counter++, left_child->llvm_name, right_child->llvm_name);
    }
    else if (!strcmp(node->node_name, "And"))
    {
        printf("\t%%%d = and i1 %%%d, %%%d\n", var_counter++, left_child->llvm_name, right_child->llvm_name);
    }
    else if (!strcmp(node->node_name, "Eq"))
    {
        printf("\t%%%d = icmp eq %s %%%d, %%%d\n", var_counter++, type, left_child->llvm_name, right_child->llvm_name);
    }
    else if (!strcmp(node->node_name, "Ne"))
    {
        printf("\t%%%d = icmp ne %s %%%d, %%%d\n", var_counter++, type, left_child->llvm_name, right_child->llvm_name);
    }
    else if (!strcmp(node->node_name, "Le"))
    {
        printf("\t%%%d = icmp sle %s %%%d, %%%d\n", var_counter++, type, left_child->llvm_name, right_child->llvm_name);
    }
    else if (!strcmp(node->node_name, "Ge"))
    {
        printf("\t%%%d = icmp sge %s %%%d, %%%d\n", var_counter++, type, left_child->llvm_name, right_child->llvm_name);
    }
    else if (!strcmp(node->node_name, "Lt"))
    {
        printf("\t%%%d = icmp slt %s %%%d, %%%d\n", var_counter++, type, left_child->llvm_name, right_child->llvm_name);
    }
    else if (!strcmp(node->node_name, "Gt"))
    {
        printf("\t%%%d = icmp sgt %s %%%d, %%%d\n", var_counter++, type, left_child->llvm_name, right_child->llvm_name);
    }
    node->llvm_name = var_counter - 1;
}

void codegen_assign(ast_node_t *node)
{
    ast_node_t *left_child = node->fChild;
    ast_node_t *right_child = left_child->nSibling;

    codegen(left_child);
    // codegen(right_child);

    char *type = llvm_node_type(left_child);

    // printf("name %s\n", left_child->llvm_name);

    // if (is_global(left_child->token.text))
    // {
    //     if (!strcmp(right_child->node_name, "Id") && is_global(right_child->token.text))
    //     {
    //         printf("\t%%%d = load %s, %s* @%s\n", var_counter++, type, type, right_child->llvm_name);
    //         printf("\tstore %s %%%d, %s* @%s\n", type, var_counter - 1, type, left_child->llvm_name);
    //     }
    //     else
    //     {
    //         printf("\tstore %s %%%s, %s* @%s\n", type, right_child->llvm_name, type, left_child->llvm_name);
    //     }
    // }
    // else
    // {
    //     if (!strcmp(right_child->node_name, "Id") && is_global(right_child->token.text))
    //     {
    //         //%2 = load i32, i32* @glo, align 4
    //         printf("\t%%%d = load %s, %s* @%s\n", var_counter++, type, type, right_child->llvm_name);
    //         printf("\tstore %s %%%d, %s* %%%s\n", type, var_counter - 1, type, left_child->llvm_name);
    //     }
    //     else
    //     {
    //         printf("\tstore %s %%%s, %s* %%%s\n", type, right_child->llvm_name, type, left_child->llvm_name);
    //     }
    // }
    if (is_global(left_child->token.text))
    {
        printf("\tstore %s %%%d, %s* @%s\n", type, right_child->llvm_name, type, left_child->token.text);
    }
    else
    {
        printf("\tstore %s %%%d, %s* %%%d\n", type, right_child->llvm_name, type, left_child->llvm_name);
    }
}

void codegen_id(ast_node_t *node)
{
    // search table
    // printf("id name %s\n", node->token.text);

    table_elem_t *elem = search_table_llvm(node->token.text);
    char *type = llvm_node_type(node);

    // printf("\t%%%d = load %s, %s* @%s\n", var_counter++, type, type, elem->llvm_name);

    // TODO: dividir em dois !!!!!!!!!!!!!!!!!!!!!!!!!!!! -> done = yes?
    // printf("llvm name %s\n", elem->llvm_name);
    if (is_global(node->token.text))
    {
        printf("\t%%%d = load %s, %s* @%s\n", var_counter++, type, type, node->token.text);
    }
    else
    {
        printf("\t%%%d = load %s, %s* %%%d\n", var_counter++, type, type, elem->llvm_name);
    }
    node->llvm_name = var_counter - 1;
}
void codegen(ast_node_t *node)
{
    if (!node)
        return;

    // printf("%s\n", node->node_name);
    if (!strcmp(node->node_name, "Program"))
    {
        print_init(node);
        codegen(node->fChild);
        return;
    }

    if (!strcmp(node->node_name, "FuncDecl"))
    {
        codegen_func(node);
        printf("\n");
    }

    if (!strcmp(node->node_name, "VarDecl"))
    {

        codegen_var(node);
    }
    if (!strcmp(node->node_name, "For"))
    {
        codegen_for(node);
    }

    if (!strcmp(node->node_name, "If"))
    {
        codegen_if(node);
    }

    if (!strcmp(node->node_name, "Return"))
    {
        codegen_return(node);
    }
    if (!strcmp(node->node_name, "Call"))
    {
        codegen_call(node);
    }
    if (!strcmp(node->node_name, "ParseArgs"))
    {
        codegen_parseargs(node);
    }
    if (!strcmp(node->node_name, "Print"))
    {
        codegen_print(node);
    }
    if (!strcmp(node->node_name, "Assign"))
    {
        codegen_assign(node); //!!!!!!
    }
    if (!strcmp(node->node_name, "Not") || !strcmp(node->node_name, "Minus") || !strcmp(node->node_name, "Plus"))
    {
        codegen_unary(node);
    }
    if (!strcmp(node->node_name, "Add") || !strcmp(node->node_name, "Sub") || !strcmp(node->node_name, "Mul") || !strcmp(node->node_name, "Div") || !strcmp(node->node_name, "Mod"))
    {
        codegen_arithmetic(node);
    }
    if (!strcmp(node->node_name, "And") || !strcmp(node->node_name, "Or") || !strcmp(node->node_name, "Eq") || !strcmp(node->node_name, "Ne") || !strcmp(node->node_name, "Le") || !strcmp(node->node_name, "Ge") || !strcmp(node->node_name, "Lt") || !strcmp(node->node_name, "Gt"))
    {
        codegen_logical(node);
    }
    if (!strcmp(node->node_name, "IntLit"))
    {
        printf("\t%%%d = add i32 0, %s\n", var_counter++, node->token.text);
        char num[10];
        sprintf(num, "%d", var_counter - 1);

        node->llvm_name = strdup(num);
    }
    if (!strcmp(node->node_name, "RealLit"))
    {
        printf("\t%%%d = fadd double 0.0, %s\n", var_counter++, node->token.text);
        char num[10];
        sprintf(num, "%d", var_counter - 1);
        node->llvm_name = strdup(num);
    }
    if (!strcmp(node->node_name, "StrLit"))
    {
    }
    if (!strcmp(node->node_name, "Id"))
    {
        codegen_id(node);
    }

    if (node->nSibling && !in_flow)
    {
        codegen(node->nSibling);
    }
}
