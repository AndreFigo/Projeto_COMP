#  Utilização
#  Adicionar gocompiler (compilado) ao PATH
#  (uma boa opção é adicionar a directoria da meta1 ao PATH)
#  Após compilar executar este script
#
#  Funcionalidade
#  Compara todos os casos de teste na pasta meta1
#  Cria o ficheiro *casoteste*.out_temp com resultado de correr cada caso de teste
#
#  Flags
#  -c apagar os ficheiros *casotest*.out_temp após correr cada caso de teste

./compile.sh


dgos=`ls ./Comp2021.git/meta3/*.dgo`
suffix=".dgo"
for ef in $dgos
do
   echo "$ef"
   A="${ef%$suffix}.out_me"
   B="${ef%$suffix}.out"
   ./deigo -s < $ef > $A 
    
   diff $A $B
   if test ! -z $1 && test $1 = "-c"; then
      rm -Rf $A
   fi
done