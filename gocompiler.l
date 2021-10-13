%X COMMENT1LINE COMMENTMULTILINE STRLIT STRLITERROR
letter  [a-zA-Z]
number  [0-9]
newline \r\n|\r|\n

%{
    int semicolon=0;
    int yycolno=1;
    int begcol=0, begline=0;
%}
%%
 
 /* OPERATORS */
";"  {printf("SEMICOLON\n");semicolon=0;yycolno+=yyleng;}
","  {printf("COMMA\n");semicolon=0;yycolno+=yyleng;}
"_"  {printf("BLANKID\n");semicolon=0;yycolno+=yyleng;}
"="  {printf("ASSIGN\n");semicolon=0;yycolno+=yyleng;}
"*"  {printf("STAR\n");semicolon=0;yycolno+=yyleng;}
"/"  {printf("DIV\n");semicolon=0;yycolno+=yyleng;}
"-"  {printf("MINUS\n");semicolon=0;yycolno+=yyleng;}
"+"  {printf("PLUS\n");semicolon=0;yycolno+=yyleng;}
"=="  {printf("EQ\n");semicolon=0;yycolno+=yyleng;}
">="  {printf("GE\n");semicolon=0;yycolno+=yyleng;}
">"  {printf("GT\n");semicolon=0;yycolno+=yyleng;}
"{"  {printf("LBRACE\n");semicolon=0;yycolno+=yyleng;}
"<="  {printf("LE\n");semicolon=0;yycolno+=yyleng;}
"("  {printf("LPAR\n");semicolon=0;yycolno+=yyleng;}
"["  {printf("LSQ\n");semicolon=0;yycolno+=yyleng;}
"<"  {printf("LT\n");semicolon=0;yycolno+=yyleng;}
"%"  {printf("MOD\n");semicolon=0;yycolno+=yyleng;}
"!="  {printf("NE\n");semicolon=0;yycolno+=yyleng;}
"!"  {printf("NOT\n");semicolon=0;yycolno+=yyleng;}
"&&"  {printf("AND\n");semicolon=0;yycolno+=yyleng;}
"||"  {printf("OR\n");semicolon=0;yycolno+=yyleng;}
"}"  {printf("RBRACE\n");semicolon=1;yycolno+=yyleng;}
")"  {printf("RPAR\n");semicolon=1;yycolno+=yyleng;}
"]"  {printf("RSQ\n");semicolon=1;yycolno+=yyleng;}

 /* KEYWORDS */
package  {printf("PACKAGE\n");semicolon=0;yycolno+=yyleng;}
return  {printf("RETURN\n");semicolon=1;yycolno+=yyleng;}
else    {printf("ELSE\n");semicolon=0;yycolno+=yyleng;}
for     {printf("FOR\n");semicolon=0;yycolno+=yyleng;}
if  {printf("IF\n");semicolon=0;yycolno+=yyleng;}
var  {printf("VAR\n");semicolon=0;yycolno+=yyleng;}
int  {printf("INT\n");semicolon=0;yycolno+=yyleng;}
float32  {printf("FLOAT32\n");semicolon=0;yycolno+=yyleng;}
bool  {printf("BOOL\n");semicolon=0;yycolno+=yyleng;}
string  {printf("STRING\n");semicolon=0;yycolno+=yyleng;}
fmt.Println  {printf("PRINT\n");semicolon=0;yycolno+=yyleng;}
strconv.Atoi  {printf("PARSEINT\n");semicolon=0;yycolno+=yyleng;}
func    {printf("FUNC\n");semicolon=0;yycolno+=yyleng;}
os.Args  {printf("CMDARGS\n");semicolon=0;yycolno+=yyleng;}

 /* RESERVED */
"++"    {printf("RESERVED(++)\n");semicolon=0;yycolno+=yyleng;}
"--"    {printf("RESERVED(--)\n");semicolon=0;yycolno+=yyleng;}
break    {printf("RESERVED(break)\n");semicolon=0;yycolno+=yyleng;}
case   {printf("RESERVED(case)\n");semicolon=0;yycolno+=yyleng;}
chan    {printf("RESERVED(chan)\n");semicolon=0;yycolno+=yyleng;}
const    {printf("RESERVED(const)\n");semicolon=0;yycolno+=yyleng;}
continue   {printf("RESERVED(continue)\n");semicolon=0;yycolno+=yyleng;}
default    {printf("RESERVED(default)\n");semicolon=0;yycolno+=yyleng;}
defer   {printf("RESERVED(defer)\n");semicolon=0;yycolno+=yyleng;}
fallthrough    {printf("RESERVED(fallthrough)\n");semicolon=0;yycolno+=yyleng;}
go    {printf("RESERVED(go)\n");semicolon=0;yycolno+=yyleng;}
goto    {printf("RESERVED(goto)\n");semicolon=0;yycolno+=yyleng;}
import    {printf("RESERVED(import)\n");semicolon=0;yycolno+=yyleng;}
interface    {printf("RESERVED(interface)\n");semicolon=0;yycolno+=yyleng;}
map   {printf("RESERVED(map)\n");semicolon=0;yycolno+=yyleng;}
range    {printf("RESERVED(range)\n");semicolon=0;yycolno+=yyleng;}
select   {printf("RESERVED(select)\n");semicolon=0;yycolno+=yyleng;}
struct   {printf("RESERVED(struct)\n");semicolon=0;yycolno+=yyleng;}
switch   {printf("RESERVED(switch)\n");semicolon=0;yycolno+=yyleng;}
type    {printf("RESERVED(type)\n");semicolon=0;yycolno+=yyleng;}


 /* INTLIT */
[1-9]{number}*    {printf("INTLIT(%s)\n", yytext);semicolon=1;yycolno+=yyleng;}

0   {printf("INTLIT(%s)\n", yytext);semicolon=1;yycolno+=yyleng;}

(0x|0X)[0-9a-fA-F]+    {printf("INTLIT(%s)\n", yytext);semicolon=1;yycolno+=yyleng;}

0[0-7]+  {printf("INTLIT(%s)\n", yytext);semicolon=1;yycolno+=yyleng;}

0{number}+   {printf("Line %d, column %d: invalid octal constant (%s)\n",yylineno, yycolno, yytext);semicolon=0;yycolno+=yyleng;}




 /* REALLIT */
 /*parte inteira seguida de ponto, opcional parte fraccionaria e/ou expoente*/
{number}+"."(({number}+)|(e|E)("+"|"-")?{number}+|({number}+)(e|E)("+"|"-")?{number}+)?  {printf("REALLIT(%s)\n", yytext);semicolon=1;yycolno+=yyleng;}

 /*ponto com parte fraccionaria, opcional seguida de expoente*/
"."{number}+((e|E)("+"|"-")?{number}+)?    {printf("REALLIT(%s)\n", yytext);semicolon=1;yycolno+=yyleng;}


 /*parte inteira seguida de expoente*/
{number}+(e|E)("+"|"-")?{number}+   {printf("REALLIT(%s)\n", yytext);semicolon=1;yycolno+=yyleng;}

 /* STRLIT */
\"     {BEGIN STRLIT; begcol=yycolno;yycolno++;}
 /*string completa sem erros*/
<STRLIT>([^\r\n"\\]*|(\\(t|n|r|\\|\"|f)))*\"   {printf("STRLIT(\"%s)\n", yytext); semicolon=1;yycolno+=yyleng; BEGIN 0;}


 /* Erros */
<STRLIT>\\{newline}   {BEGIN 0; printf("Line %d, column %d: invalid escape sequence (\\)\n", yylineno, yycolno);
                            printf("Line %d, column %d: unterminated string literal\n", yylineno, begcol);
                            yycolno=1;yylineno++;semicolon=0;}
<STRLIT>\\(t|n|r|\\|\"|f)   {BEGIN STRLITERROR;yycolno+=yyleng;}
<STRLIT>\\[^nrft"\\]   {BEGIN STRLITERROR; printf("Line %d, column %d: invalid escape sequence (%s)\n", yylineno, yycolno, yytext); yycolno+=yyleng;semicolon=0;}
<STRLIT>{newline}   {BEGIN 0; printf("Line %d, column %d: unterminated string literal\n", yylineno, begcol); yycolno=1;yylineno++;semicolon=0;}
<STRLIT>.   {BEGIN STRLITERROR;yycolno+=yyleng; }
<STRLIT><<EOF>> {printf("Line %d, column %d: unterminated string literal\n", yylineno, begcol);BEGIN 0;}


<STRLITERROR>\\{newline}   { BEGIN 0; printf("Line %d, column %d: invalid escape sequence (\\)\n", yylineno, yycolno);
                                printf("Line %d, column %d: unterminated string literal\n", yylineno, begcol);
                                yycolno=1;yylineno++;semicolon=0;}
<STRLITERROR>\\[^nrft"\\]   { printf("Line %d, column %d: invalid escape sequence (%s)\n", yylineno, yycolno, yytext); yycolno+=yyleng;semicolon=0;}
<STRLITERROR>{newline}   {BEGIN 0; printf("Line %d, column %d: unterminated string literal\n", yylineno, begcol); yycolno=1;yylineno++;semicolon=0;}
<STRLITERROR>\\(t|n|r|\\|\"|f)   {;yycolno+=yyleng;}
<STRLITERROR>\"   {yycolno+=yyleng;BEGIN 0;}
<STRLITERROR>\\   {printf("Line %d, column %d: invalid escape sequence (\\)\n", yylineno, yycolno); yycolno+=yyleng;}
<STRLITERROR><<EOF>>   {printf("Line %d, column %d: unterminated string literal\n", yylineno, begcol); BEGIN 0;}
<STRLITERROR>.   {yycolno+=yyleng;}


 /* IDs */
({letter}|"_")({letter}|{number}|"_")*   {printf("ID(%s)\n", yytext);semicolon=1; yycolno+=yyleng;}

 /*COMMENTS*/
"//"    {BEGIN COMMENT1LINE;yycolno+=yyleng;}

<COMMENT1LINE>{newline}   {BEGIN 0;yylineno++;yycolno=1;}
<COMMENT1LINE>.   {yycolno+=yyleng;}


"/*"    {BEGIN COMMENTMULTILINE;begcol=yycolno;begline=yylineno;yycolno+=yyleng;}
<COMMENTMULTILINE><<EOF>>   {printf("Line %d, column %d: unterminated comment\n",begline, begcol); BEGIN 0; }
<COMMENTMULTILINE>"*/"   {BEGIN 0;yycolno+=yyleng;}
<COMMENTMULTILINE>{newline}   {yycolno=1;yylineno++;}
<COMMENTMULTILINE>.   {yycolno+=yyleng;}




{newline} {
            if (semicolon){
                printf("SEMICOLON\n");
                semicolon=0;
            };
            yylineno++;
            yycolno=1;
            } 

<<EOF>>  {if (semicolon){ printf("SEMICOLON\n");}; yyterminate();} 

\t  {yycolno+=yyleng;}
" "   {yycolno+=yyleng;}

 /* Caraters ilegais*/
.  {printf("Line %d, column %d: illegal character (%s)\n",yylineno, yycolno, yytext); yycolno+=yyleng;}


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
