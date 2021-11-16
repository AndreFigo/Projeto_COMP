#!/bin/bash
echo "{$1}"
#./jucompiler -s < $1.java | diff $1.out -
../3158 -s < $1.java | diff $1.out -
