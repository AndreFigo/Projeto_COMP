#ifndef SEMANTICS_H
#define SEMANTICS_H

#include "AST.h"
#include "structures.h"

void print_tables();
void create_symtab(ast_node_t *node);
void check_symtab(ast_node_t *node);
int insert_elem_func();
int search_table();
void find_unused(table_t *table);
void add_table(table_t *table, ast_node_t *node);
table_t *create_table(int global);
void print_table(table_t *table);
table_elem_t *create_return_elem();
int insert_elem_var(int param, ast_node_t *node);
void free_tables(table_t *table);
void print_symbol_already_defined(token_t token);
void print_cannot_find_symbol(token_t token);
void print_cannot_find_symbol_func(ast_node_t *node, ast_node_t *params_nodes);
void print_cannot_be_applied_to_type(token_t token, char *type);
void print_cannot_be_applied_to_types(token_t token, char *typeA, char *typeB);
void print_incompatible_type(token_t token, token_t child_token, char *type);
void print_symbol_declared_but_never_used(int line, int col, char *var);

#endif
