lex gocompiler.l
clang-7 -o comp lex.yy.c

./comp < Comp2021.git/meta1/$1.dgo > out.txt
diff out.txt Comp2021.git/meta1/$1.out