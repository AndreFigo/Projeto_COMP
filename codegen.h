#ifndef CODEGEN_H
#define CODEGEN_H

#include "AST.h"
#include "structures.h"
#include "semantics.h"
#include "utils.h"

void codegen(ast_node_t *node);
char *llvm_var_type(ast_node_t *node);
char *llvm_node_type(ast_node_t *node);

#endif
