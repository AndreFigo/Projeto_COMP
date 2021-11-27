#ifndef SEMANTICS_H
#define SEMANTICS_H

#include "AST.h"
#include "structures.h"

void print_tables();
int create_symtab(ast_node_t *node);
int insert_elem_func();
#endif