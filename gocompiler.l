%X COMMENT1LINE COMMENTMULTILINE STRLIT
letter  [a-zA-Z]
number  [0-9]
newline \r\n|\r|\n

%{
    int semicolon=0;
%}
%%

";"  {printf("SEMICOLON\n");semicolon=0;}
","  {printf("COMMA\n");semicolon=0;}
"_"  {printf("BLANKID\n");semicolon=0;}
"="  {printf("ASSIGN\n");semicolon=0;}
"*"  {printf("STAR\n");semicolon=0;}
"/"  {printf("DIV\n");semicolon=0;}
"-"  {printf("MINUS\n");semicolon=0;}
"+"  {printf("PLUS\n");semicolon=0;}
"=="  {printf("EQ\n");semicolon=0;}
">="  {printf("GE\n");semicolon=0;}
">"  {printf("GT\n");semicolon=0;}
"{"  {printf("LBRACE\n");semicolon=0;}
"<="  {printf("LE\n");semicolon=0;}
"("  {printf("LPAR\n");semicolon=0;}
"["  {printf("LSQ\n");semicolon=0;}
"<"  {printf("LT\n");semicolon=0;}
"%"  {printf("MOD\n");semicolon=0;}
"!="  {printf("NE\n");semicolon=0;}
"!"  {printf("NOT\n");semicolon=0;}
"&&"  {printf("AND\n");semicolon=0;}
"||"  {printf("OR\n");semicolon=0;}
"}"  {printf("RBRACE\n");semicolon=1;}
")"  {printf("RPAR\n");semicolon=1;}
"]"  {printf("RSQ\n");semicolon=1;}


package  {printf("PACKAGE\n");semicolon=0;}
return  {printf("RETURN\n");semicolon=1;}
else    {printf("ELSE\n");semicolon=0;}
for     {printf("FOR\n");semicolon=0;}
if  {printf("IF\n");semicolon=0;}
var  {printf("VAR\n");semicolon=0;}
int  {printf("INT\n");semicolon=0;}
float32  {printf("FLOAT32\n");semicolon=0;}
bool  {printf("BOOL\n");semicolon=0;}
string  {printf("STRING\n");semicolon=0;}
fmt.Println  {printf("PRINT\n");semicolon=0;}
strconv.Atoi  {printf("PARSEINT\n");semicolon=0;}
func    {printf("FUNC\n");semicolon=0;}
os.Args  {printf("CMDARGS\n");semicolon=0;}

"++"    {printf("RESERVED(++)\n");semicolon=0;}
"--"    {printf("RESERVED(--)\n");semicolon=0;}
break    {printf("RESERVED(break)\n");semicolon=0;}
case   {printf("RESERVED(case)\n");semicolon=0;}
chan    {printf("RESERVED(chan)\n");semicolon=0;}
const    {printf("RESERVED(const)\n");semicolon=0;}
continue   {printf("RESERVED(continue)\n");semicolon=0;}
default    {printf("RESERVED(default)\n");semicolon=0;}
defer   {printf("RESERVED(defer)\n");semicolon=0;}
fallthrough    {printf("RESERVED(fallthrough)\n");semicolon=0;}
go    {printf("RESERVED(go)\n");semicolon=0;}
goto    {printf("RESERVED(goto)\n");semicolon=0;}
import    {printf("RESERVED(import)\n");semicolon=0;}
interface    {printf("RESERVED(interface)\n");semicolon=0;}
map   {printf("RESERVED(map)\n");semicolon=0;}
range    {printf("RESERVED(range)\n");semicolon=0;}
select   {printf("RESERVED(select)\n");semicolon=0;}
struct   {printf("RESERVED(struct)\n");semicolon=0;}
switch   {printf("RESERVED(switch)\n");semicolon=0;}
type    {printf("RESERVED(type)\n");semicolon=0;}


[1-9]{number}*    {printf("INTLIT(%s)\n", yytext);semicolon=1;}

0   {printf("INTLIT(%s)\n", yytext);semicolon=1;}

(0x|0X)[0-9a-fA-F]+    {printf("INTLIT(%s)\n", yytext);semicolon=1;}

0[0-7]+  {printf("INTLIT(%s)\n", yytext);semicolon=1;}

0{number}+   {printf("Line %d, column %d: invalid octal constant (%s)\n",yylineno, 1, yytext);semicolon=0;}





 /*parte inteira seguida de ponto, op parte fraccionaria e/ou expoente*/
{number}+"."(({number}+)|(e|E)("+"|"-")?{number}+|({number}+)(e|E)("+"|"-")?{number}+)  {printf("REALLIT(%s)\n", yytext);semicolon=1;}


 /*ponto com parte fraccionaria, op seguida de expoente*/
"."{number}+((e|E)("+"|"-")?{number}+)?    {printf("REALLIT(%s)\n", yytext);semicolon=1;}


 /*parte inteira seguida de expoente*/
{number}+(e|E)("+"|"-")?{number}+   {printf("REALLIT(%s)\n", yytext);semicolon=1;}



 /*\"  {BEGIN STRLIT;}*/

   
\"([^\n\r\"]*\\[^trnf\\\"][^\n\r\"]*)*\"   {printf("erro\n");}

\"([^\n\r\"]*\\[^trnf\\\"][^\n\r\"]*)*{newline}   {printf("erro4x\n");}
\"([^\n\r\"]*\\[^trnf\\\"][^\n\r\"]*)*<EOF>   {printf("erro5x\n");}
\"[^\n\r\"]*{newline}   {printf("erro2x\n");}
\"[^\n\r\"]*<EOF>  {printf("erro3x\n");}
\"[^\n\r\"]*\"  {printf("good\n");}
<<EOF>> {printf("ohey the\n");}

<STRLIT>\\[^trnf\\\"]      {printf("teste\n");}
 /*<STRLIT>[^\n\r\"]*{newline}   {printf("Line %d, column %d: unterminated string literal\n",yylineno, 1); semicolon=0; BEGIN 0;}  */
 /*<STRLIT>[^\n\r\"]*\"    {printf("STRLIT(\"%s)\n", yytext); semicolon=1; BEGIN 0;} */

"//"    {BEGIN COMMENT1LINE;}


<COMMENT1LINE>{newline}   {BEGIN 0;}
<COMMENT1LINE>.   {;}


"/*"    {BEGIN COMMENTMULTILINE;}
<COMMENTMULTILINE><<EOF>>   {printf("Line %d, column %d: unterminated comment\n",yylineno, 1); BEGIN 0;}
<COMMENTMULTILINE>"*/"   {BEGIN 0;}

<COMMENTMULTILINE>.   {;}



({letter}|"_")({letter}|{number}|"_")*   {printf("ID(%s)\n", yytext);semicolon=1;}

{newline} {if (semicolon){
                printf("SEMICOLON\n");
                semicolon=0;
            }} 
.  {;}

%%
int main()
{
yylex();
return 0;
}

int yywrap()
{
return 1;
}
