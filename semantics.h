#ifndef SEMANTICS_H
#define SEMANTICS_H

#include "AST.h"
#include "structures.h"

void print_tables();
int create_symtab(ast_node_t *node);
int insert_elem_func();
int search_table();
int add_table(table_t *table);
table_t *create_table(int global);
void print_table(table_t *table);
table_elem_t *create_return_elem();
int insert_elem_var(int param, ast_node_t *node);
#endif