
#ifndef AST_H
#define AST_H

#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "structures.h"

ast_node_t *create_node(char *node_name, token_t token);

void add_children(ast_node_t *parent, int n_childs, ...);

ast_node_t *add_siblings(ast_node_t *first, int n_siblings, ...);

void free_ast(ast_node_t *node);

void print_ast_node(char *node_name, token_t tok, int depth);

void print_ast_node_anottated(ast_node_t *node, int depth);

void print_ast(ast_node_t *node, int depth);

void print_program(ast_node_t *program);

ast_node_t *split_vardecl(ast_node_t *node, token_t vardecl_tok);

#endif