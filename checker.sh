./compile.sh

./deigo -s < Comp2021.git/meta3/$1.dgo  > out.txt
diff out.txt Comp2021.git/meta3/$1.out