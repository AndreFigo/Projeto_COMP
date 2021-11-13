
#ifndef AST_H
#define AST_H

#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "structures.h"

ast_node_t *create_node(char *type, token_t token);

void add_children(ast_node_t *parent, int n_childs, ...);

void add_siblings(ast_node_t *first, int n_siblings, ...);

void free_ast(ast_node_t *node);

void print_node(char *type, token_t tok, int depth);

void print_ast(ast_node_t *node, int depth);

void print_program(ast_node_t *program);

#endif