#include "codegen.h"

int var_counter = 0;
extern table_t *current_table, *global_table;

void print_init()
{
    // print general info present in every file
    printf("declare i32 @putchar(...)\n");
    printf("declare i32 @getchar(...)\n");
    printf(" @.strlit = private unnamed_addr constant [4 x i8] c\"%%s\\0A\\00\", align 1\n");
    printf(" @.intlit = private unnamed_addr constant [4 x i8] c\"%%d\\0A\\00\", align 1\n");
    printf(" @.reallit = private unnamed_addr constant [4 x i8] c\"%%f\\0A\\00\", align 1\n");
    printf(" @.boollit= private unnamed_addr constant [4 x i8] c\"%%d\\0A\\00\", align 1\n");
    printf("declare i32 @printf(i8*, ...)\n\n");
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

void add_llvm_name(char *var_name, char *llvm_name)
{
    for (table_elem_t *elem = current_table->first; elem; elem = elem->next)
    {
        if (!strcmp(elem->name, var_name))
            elem->llvm_name = strdup(llvm_name);
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

void codegen_func(ast_node_t *node)
{
    // funcdecl -> header , body
    // header -> id type? params
    // params -> paramDecl * -> type id
    // body -> declarations | statements

    ast_node_t *header = node->fChild;
    ast_node_t *body = header->nSibling;

    ast_node_t *id_node = header->fChild;
    ast_node_t *type = id_node->nSibling;
    ast_node_t *fParams;

    if (!strcmp(type->node_name, "FuncParams"))
    {
        fParams = type;
        type = NULL;
    }
    else
        fParams = type->nSibling;

    char *func_type = llvm_var_type(type);

    printf("define %s @%s(", func_type, id_node->token.text);
    free(func_type);

    ast_node_t *current_node = fParams->fChild;

    for (current_node; current_node; current_node = current_node->nSibling)
    {
        // criar table_elem
        char *param_type = llvm_var_type(current_node->fChild);
        printf("%s %%%s", param_type, current_node->fChild->nSibling->token.text);
        if (current_node->nSibling)
            printf(", ");
        free(param_type);
    }
    printf(")\n");

    // func body
    current_table = find_table(header);
    printf("{\n");
    var_counter = 1;
    // Todo allocate mem for params and update table elem

    if (body->fChild)
        codegen(body->fChild);
    else
        printf("\tret void\n");
    printf("}\n");
    current_table = global_table;
    // Todo reset llvm_name of parameters
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
            printf("\t%%%s = alloca i8*\n", id_node->token.text);
        }
        else if (!strcmp(type_node->node_name, "Int"))
        {
            printf("\t%%%s = alloca i32\n", id_node->token.text);
        }
        else if (!strcmp(type_node->node_name, "Bool"))
        {
            printf("\t%%%s = alloca i1\n", id_node->token.text);
        }
        else if (!strcmp(type_node->node_name, "Float32"))
        {
            printf("\t%%%s = alloca double\n", id_node->token.text);
        }
        // char num[10];
        // sprintf(num, "%d", var_counter - 1);
        // add_llvm_name(id_node->token.text, num);
    }
    id_node->llvm_name = strdup(id_node->token.text);
    add_llvm_name(id_node->token.text, id_node->token.text);
}

void codegen_for(ast_node_t *node)
{
}

void codegen_if(ast_node_t *node)
{
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
        printf("\tret %s %%%s\n", type, child_node->llvm_name);
    }
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

    for (; params; params = params->nSibling)
    {
        type = llvm_node_type(params);

        if (!strcmp(params->node_name, "Id") && is_global(params->token.text))
        {
            printf("\t%%%d = load %s, %s* @%s\n", var_counter++, type, type, params->llvm_name);
        }

        else if (!strcmp(params->node_name, "Id"))
        {
            printf("\t%%%d = load %s, %s* %%%s\n", var_counter++, type, type, params->llvm_name);
        }
        else
        {
            if (!strcmp(type, "i32") || !strcmp(type, "i1"))
                printf("\t%%%d = add  %s 0, %%%s\n", var_counter++, type, params->llvm_name);
            else if (!strcmp(type, "double"))
                printf("\t%%%d = fadd  %s 0, %%%s\n", var_counter++, type, params->llvm_name);

            // param_name = strdup(params->llvm_name);
        }

        free(type);
    }
    type = llvm_node_type(node);

    if (!strcmp(type, "void"))
    {
        printf("\tcall %s @%s(", type, id_node->llvm_name);
    }
    else
    {
        printf("\t%%%d = call %s @%s(", var_counter++, type, id_node->llvm_name);
    }
    free(type);
    for (params = id_node->nSibling; params; params = params->nSibling)
    {
        type = llvm_node_type(params);

        if (params->nSibling)
            printf("%s %%%d,", type, var_counter_init++);
        else
            printf("%s %%%d", type, var_counter_init++);

        free(type);
    }
    printf(")\n");
}

void codegen_print(ast_node_t *node)
{
    ast_node_t *child_node = node->fChild;
    char *type = llvm_node_type(child_node);

    codegen(child_node);

    if (!strcmp(child_node->node_name, "Id") && is_global(child_node->token.text))
    {
        printf("\t%%%d = load %s, %s* @%s\n", var_counter++, type, type, child_node->llvm_name);
    }

    else if (!strcmp(child_node->node_name, "Id"))
    {
        printf("\t%%%d = load %s, %s* %%%s\n", var_counter++, type, type, child_node->llvm_name);
    }
    else
    {
        // no need
    }

    // call i32(i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i32 0, i32 0), i32 %aux2)
    if (!strcmp(type, "i32"))
    {
        printf("\tcall i32(i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.intlit, i32 0, i32 0), i32 %%%d)\n", var_counter++ - 1);
    }
    else if (!strcmp(type, "double"))
    {
        printf("\tcall i32(i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.reallit, i32 0, i32 0), double %%%d)\n", var_counter++ - 1);
    }
    else if (!strcmp(type, "i1"))
    {
        printf("\tcall i32(i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.boollit, i32 0, i32 0), i1 %%%d)\n", var_counter++ - 1);
    }
    else if (!strcmp(type, "i8*"))
    {
        printf("\tcall i32(i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.strlit, i32 0, i32 0), i8* %%%d)\n", var_counter++ - 1);
    }
}

void codegen_arithmetic(ast_node_t *node)
{
    ast_node_t *left_child = node->fChild;
    ast_node_t *right_child = left_child->nSibling;
    char *op1, *op2;
    char num[10];

    codegen(left_child);

    char *type = llvm_node_type(left_child);

    if (!strcmp(left_child->node_name, "Id") && is_global(left_child->token.text))
    {
        printf("\t%%%d = load %s, %s* @%s\n", var_counter++, type, type, left_child->llvm_name);
        sprintf(num, "%d", var_counter - 1);
        op1 = strdup(num);
    }
    else if (!strcmp(left_child->node_name, "Id"))
    {
        printf("\t%%%d = load %s, %s* %%%s\n", var_counter++, type, type, left_child->llvm_name);
        sprintf(num, "%d", var_counter - 1);
        op1 = strdup(num);
    }
    else
    {
        op1 = strdup(left_child->llvm_name);
    }

    if (!strcmp(right_child->node_name, "Id") && is_global(right_child->token.text))
    {
        printf("\t%%%d = load %s, %s* @%s\n", var_counter++, type, type, right_child->llvm_name);
        sprintf(num, "%d", var_counter - 1);
        op2 = strdup(num);
    }
    else if (!strcmp(right_child->node_name, "Id"))
    {
        printf("\t%%%d = load %s, %s* %%%s\n", var_counter++, type, type, right_child->llvm_name);
        sprintf(num, "%d", var_counter - 1);
        op2 = strdup(num);
    }
    else
    {
        op2 = strdup(right_child->llvm_name);
    }

    if (!strcmp(node->node_name, "Add"))
    {
        if (!strcmp(type, "i32"))
        {
            printf("\t%%%d = add i32 %%%s, %%%s\n", var_counter++, op1, op2);
        }
        else if (!strcmp(type, "double"))
        {
            printf("\t%%%d = fadd double %%%s, %%%s\n", var_counter++, op1, op2);
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
            printf("\t%%%d = sub i32 %%%s, %%%s\n", var_counter++, op1, op2);
        }
        else if (!strcmp(type, "double"))
        {
            printf("\t%%%d = fsub double %%%s, %%%s\n", var_counter++, op1, op2);
        }
    }
    else if (!strcmp(node->node_name, "Mul"))
    {
        if (!strcmp(type, "i32"))
        {
            printf("\t%%%d = mul i32 %%%s, %%%s\n", var_counter++, op1, op2);
        }
        else if (!strcmp(type, "double"))
        {
            printf("\t%%%d = fmul double %%%s, %%%s\n", var_counter++, op1, op2);
        }
    }
    else if (!strcmp(node->node_name, "Div"))
    {
        if (!strcmp(type, "i32"))
        {
            printf("\t%%%d = sdiv i32 %%%s, %%%s\n", var_counter++, op1, op2);
        }
        else if (!strcmp(type, "double"))
        {
            printf("\t%%%d = fdiv double %%%s, %%%s\n", var_counter++, op1, op2);
        }
    }
    else if (!strcmp(node->node_name, "Mod"))
    {
        printf("\t%%%d = urem i32 %%%s, %%%s\n", var_counter++, op1, op2);
    }

    sprintf(num, "%d", var_counter - 1);
    free(op1);
    free(op2);
    node->llvm_name = strdup(num);
}

void codegen_unary(ast_node_t *node)
{
    ast_node_t *child_node = node->fChild;
    char *child_name;
    char num[10];

    codegen(child_node);

    char *type = llvm_node_type(child_node);

    if (!strcmp(child_node->node_name, "Id") && is_global(child_node->token.text))
    {
        printf("\t%%%d = load %s, %s* @%s\n", var_counter++, type, type, child_node->llvm_name);
        sprintf(num, "%d", var_counter - 1);
        child_name = strdup(num);
    }
    else if (!strcmp(child_node->node_name, "Id"))
    {
        printf("\t%%%d = load %s, %s* %%%s\n", var_counter++, type, type, child_node->llvm_name);
        sprintf(num, "%d", var_counter - 1);
        child_name = strdup(num);
    }
    else
    {
        child_name = strdup(child_node->llvm_name);
    }

    if (!strcmp(node->node_name, "Not"))
    {
        printf("\t%%%d = xor i1 %%%s, 1\n", var_counter++, child_name);
    }
    else if (!strcmp(node->node_name, "Minus"))
    {
        if (!strcmp(type, "i32"))
            printf("\t%%%d = sub i32  0, %%%s", var_counter++, child_name);
        else
            printf("\t%%%d = fsub double 0.0, %%%s", var_counter++, child_name);
    }
    else if (!strcmp(node->node_name, "Plus"))
    {
        // nothing to do
    }

    sprintf(num, "%d", var_counter - 1);

    node->llvm_name = strdup(num);
    free(child_name);
}

void codegen_logical(ast_node_t *node)
{
    ast_node_t *left_child = node->fChild;
    ast_node_t *right_child = left_child->nSibling;
    char *op1, *op2;
    char num[10];

    codegen(left_child);

    char *type = llvm_node_type(left_child);

    if (!strcmp(left_child->node_name, "Id") && is_global(left_child->token.text))
    {
        printf("\t%%%d = load %s, %s* @%s\n", var_counter++, type, type, left_child->llvm_name);
        sprintf(num, "%d", var_counter - 1);
        op1 = strdup(num);
    }
    else if (!strcmp(left_child->node_name, "Id"))
    {
        printf("\t%%%d = load %s, %s* %%%s\n", var_counter++, type, type, left_child->llvm_name);
        sprintf(num, "%d", var_counter - 1);
        op1 = strdup(num);
    }
    else
    {
        op1 = strdup(left_child->llvm_name);
    }

    if (!strcmp(right_child->node_name, "Id") && is_global(right_child->token.text))
    {
        printf("\t%%%d = load %s, %s* @%s\n", var_counter++, type, type, right_child->llvm_name);
        sprintf(num, "%d", var_counter - 1);
        op2 = strdup(num);
    }
    else if (!strcmp(right_child->node_name, "Id"))
    {
        printf("\t%%%d = load %s, %s* %%%s\n", var_counter++, type, type, right_child->llvm_name);
        sprintf(num, "%d", var_counter - 1);
        op2 = strdup(num);
    }
    else
    {
        op2 = strdup(right_child->llvm_name);
    }

    if (!strcmp(node->node_name, "Or"))
    {
        printf("\t%%%d = or i1 %%%s, %%%s\n", var_counter++, op1, op2);
    }
    else if (!strcmp(node->node_name, "And"))
    {
        printf("\t%%%d = and i1 %%%s, %%%s\n", var_counter++, op1, op2);
    }
    else if (!strcmp(node->node_name, "Eq"))
    {
        printf("\t%%%d = icmp eq %s %%%s, %%%s\n", var_counter++, type, op1, op2);
    }
    else if (!strcmp(node->node_name, "Ne"))
    {
        printf("\t%%%d = icmp ne %s %%%s, %%%s\n", var_counter++, type, op1, op2);
    }
    else if (!strcmp(node->node_name, "Le"))
    {
        printf("\t%%%d = icmp sle %s %%%s, %%%s\n", var_counter++, type, op1, op2);
    }
    else if (!strcmp(node->node_name, "Ge"))
    {
        printf("\t%%%d = icmp sge %s %%%s, %%%s\n", var_counter++, type, op1, op2);
    }
    else if (!strcmp(node->node_name, "Lt"))
    {
        printf("\t%%%d = icmp slt %s %%%s, %%%s\n", var_counter++, type, op1, op2);
    }
    else if (!strcmp(node->node_name, "Gt"))
    {
        printf("\t%%%d = icmp sgt %s %%%s, %%%s\n", var_counter++, type, op1, op2);
    }
    sprintf(num, "%d", var_counter - 1);
    free(op1);
    free(op2);
    node->llvm_name = strdup(num);
}

void codegen_assign(ast_node_t *node)
{
    ast_node_t *left_child = node->fChild;
    ast_node_t *right_child = left_child->nSibling;

    codegen(left_child);
    // codegen(right_child);

    char *type = llvm_node_type(left_child);

    // printf("name %s\n", left_child->llvm_name);

    if (is_global(left_child->token.text))
    {
        if (!strcmp(right_child->node_name, "Id") && is_global(right_child->token.text))
        {
            printf("\t%%%d = load %s, %s* @%s\n", var_counter++, type, type, right_child->llvm_name);
            printf("\tstore %s %%%d, %s* @%s\n", type, var_counter - 1, type, left_child->llvm_name);
        }
        else
        {
            printf("\tstore %s %%%s, %s* @%s\n", type, right_child->llvm_name, type, left_child->llvm_name);
        }
    }
    else
    {
        if (!strcmp(right_child->node_name, "Id") && is_global(right_child->token.text))
        {
            //%2 = load i32, i32* @glo, align 4
            printf("\t%%%d = load %s, %s* @%s\n", var_counter++, type, type, right_child->llvm_name);
            printf("\tstore %s %%%d, %s* %%%s\n", type, var_counter - 1, type, left_child->llvm_name);
        }
        else
        {
            printf("\tstore %s %%%s, %s* %%%s\n", type, right_child->llvm_name, type, left_child->llvm_name);
        }
    }
}

void codegen(ast_node_t *node)
{
    if (!node)
        return;

    // printf("%s\n", node->node_name);
    if (!strcmp(node->node_name, "Program"))
    {
        print_init();
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
        // search table
        // printf("id name %s\n", node->token.text);

        table_elem_t *elem = search_table_llvm(node->token.text);
        char *type = llvm_node_type(node);

        // printf("\t%%%d = load %s, %s* @%s\n", var_counter++, type, type, elem->llvm_name);

        // TODO: dividir em dois !!!!!!!!!!!!!!!!!!!!!!!!!!!!
        // printf("llvm name %s\n", elem->llvm_name);

        node->llvm_name = strdup(elem->llvm_name);
    }

    if (node->nSibling)
    {
        codegen(node->nSibling);
    }
}
