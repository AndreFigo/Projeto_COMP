%X COMMENT1LINE COMMENTMULTILINE STRLIT
letter  [a-zA-Z]
number  [0-9]
newline \r\n|\r|\n

%{
    int semicolon=0;
    int yycolno=1;
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
 /*parte inteira seguida de ponto, op parte fraccionaria e/ou expoente*/
{number}+"."(({number}+)|(e|E)("+"|"-")?{number}+|({number}+)(e|E)("+"|"-")?{number}+)?  {printf("REALLIT(%s)\n", yytext);semicolon=1;yycolno+=yyleng;}

 /*ponto com parte fraccionaria, op seguida de expoente*/
"."{number}+((e|E)("+"|"-")?{number}+)?    {printf("REALLIT(%s)\n", yytext);semicolon=1;yycolno+=yyleng;}


 /*parte inteira seguida de expoente*/
{number}+(e|E)("+"|"-")?{number}+   {printf("REALLIT(%s)\n", yytext);semicolon=1;yycolno+=yyleng;}

 /* STRLIT */


  /*\"([^\r\n\"]*\\\"[^\r\n\"]*)*\"   */     

 /* Invalid escape sequence*/
\"([^\n\r\"]*\\[^trnf\\\"][^\n\r\"]*)*\"   { for(int i =2; i< yyleng-1;i++){
                                                if (yytext[i-1]=='\\' && !(yytext[i]=='n' || yytext[i]=='t'|| yytext[i]=='r'|| yytext[i]=='f'|| yytext[i]=='\\'|| yytext[i]=='\"')){
                                                    printf("Line %d, column %d: invalid escape sequence (%c%c)\n", yylineno, yycolno+i-1, yytext[i-1], yytext[i]);
                                                }
                                            };  semicolon=1; 
                                                yycolno+=yyleng;}
 /* Invalid escape sequence + unterminated string (newline) */
\"([^\n\r\"]*\\[^trnf\\\"][^\n\r\"]*)*{newline}   { for(int i =2; i< yyleng;i++){
                                                        if (yytext[i-1]=='\\' && !(yytext[i]=='n' || yytext[i]=='t'|| yytext[i]=='r'|| yytext[i]=='f'|| yytext[i]=='\\'|| yytext[i]=='\"')){
                                                            printf("Line %d, column %d: invalid escape sequence (%c%c)\n", yylineno, yycolno+i-1, yytext[i-1], yytext[i]);
                                                        }
                                                    }; 
                                                    {printf("Line %d, column %d: unterminated string literal\n",yylineno, yycolno);}
                                                    semicolon=0;
                                                    yylineno++;
                                                    yycolno=1;}
 /* Invalid escape sequence + unterminated string (EOF) */
\"([^\n\r\"]*\\[^trnf\\\"][^\n\r\"]*)*   { for(int i =2; i< yyleng;i++){
                                                        if (yytext[i-1]=='\\' && !(yytext[i]=='n' || yytext[i]=='t'|| yytext[i]=='r'|| yytext[i]=='f'|| yytext[i]=='\\'|| yytext[i]=='\"')){
                                                            printf("Line %d, column %d: invalid escape sequence (%c%c)\n", yylineno, yycolno+i-1, yytext[i-1], yytext[i]);
                                                        }
                                                    }; 
                                                    {printf("Line %d, column %d: unterminated string literal\n",yylineno, yycolno);}
                                                    semicolon=0;
                                                    yylineno++;
                                                    yycolno=1;}
 /* Unterminated string (newline) */
\"[^\n\r\"]*{newline}   {printf("Line %d, column %d: unterminated string literal\n",yylineno, yycolno);
                            semicolon=0;
                            yylineno++;
                            yycolno=1;}
 /* Unterminated string (EOF) */
\"[^\n\r\"]*  {printf("Line %d, column %d: unterminated string literal\n",yylineno, yycolno);
                            semicolon=0;
                            yylineno++;
                            yycolno=1;}
 /* STRLIT */                          
\"[^\n\r\"]*\"  {printf("STRLIT(%s)\n", yytext);}
 
({letter}|"_")({letter}|{number}|"_")*   {printf("ID(%s)\n", yytext);semicolon=1;}

 /*COMMENTS*/
"//"    {BEGIN COMMENT1LINE;}

<COMMENT1LINE>{newline}   {BEGIN 0;yylineno++;yycolno=1;}
<COMMENT1LINE>.   {;}


"/*"    {BEGIN COMMENTMULTILINE;}
<COMMENTMULTILINE><<EOF>>   {printf("Line %d, column %d: unterminated comment\n",yylineno, yycolno); BEGIN 0;}
<COMMENTMULTILINE>"*/"   {BEGIN 0;}
<COMMENTMULTILINE>{newline}   {;}
<COMMENTMULTILINE>.   {;}




{newline} {
            if (semicolon){
                printf("SEMICOLON\n");
                semicolon=0;
            };
            yylineno++;
            yycolno=1;
            } 
.  {yycolno+=yyleng;}

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
