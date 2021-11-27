#!/bin/sh


lex gocompiler.l && yacc -d -v gocompiler.y && cc -o deigo lex.yy.c y.tab.c utils.c semantics.c AST.c



