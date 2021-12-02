#ifndef CHECKS_H
#define CHECKS_H

#include "AST.h"
#include "structures.h"

int check_header(ast_node_t *header);
void check_body(ast_node_t *node);
int check_call(ast_node_t *node);
#endif