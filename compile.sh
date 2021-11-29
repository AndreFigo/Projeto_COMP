#!/bin/sh


lex gocompiler.l && yacc -d -v gocompiler.y && cc -o deigo *.c



