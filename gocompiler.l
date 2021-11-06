 /* Andre Figo no. 2019216156 / Joana Simões no. 2019217013*/
%X COMMENT1LINE COMMENTMULTILINE STRLITERR STRLITERROR
letter  [a-zA-Z]
number  [0-9]
newline \r\n|\r|\n

%{
    #include "utils.h"
    #include "y.tab.h"

    #define RETURN_TOKEN(...)  \
    if (l_flag==0) { \
        yylval.token = create_token(yytext, yylineno,yycolno, __VA_ARGS__); \
        return __VA_ARGS__; \
    } 

    extern int l_flag, t_flag;

    int semicolon=0;
    int yycolno=1;
    int begcol=0, begline=0;
%}
%%
 
 /* OPERATORS */
";"     {printf("SEMICOLON\n"); semicolon=0; yycolno+=yyleng; RETURN_TOKEN(SEMICOLON);}
","     {printf("COMMA\n"); semicolon=0; yycolno+=yyleng; RETURN_TOKEN(COMMA);}
"_"     {printf("BLANKID\n"); semicolon=0; yycolno+=yyleng; RETURN_TOKEN(BLANKID);}
"="     {printf("ASSIGN\n"); semicolon=0; yycolno+=yyleng; RETURN_TOKEN(ASSIGN);}
"*"     {printf("STAR\n"); semicolon=0; yycolno+=yyleng; RETURN_TOKEN(STAR);}
"/"     {printf("DIV\n"); semicolon=0; yycolno+=yyleng; RETURN_TOKEN(DIV);}
"-"     {printf("MINUS\n"); semicolon=0; yycolno+=yyleng; RETURN_TOKEN(MINUS);}
"+"     {printf("PLUS\n"); semicolon=0; yycolno+=yyleng; RETURN_TOKEN(PLUS);}
"=="    {printf("EQ\n"); semicolon=0; yycolno+=yyleng; RETURN_TOKEN(EQ);}
">="    {printf("GE\n"); semicolon=0; yycolno+=yyleng; RETURN_TOKEN(GE);}
">"     {printf("GT\n"); semicolon=0; yycolno+=yyleng; RETURN_TOKEN(GT);}
"{"     {printf("LBRACE\n"); semicolon=0; yycolno+=yyleng; RETURN_TOKEN(LBRACE);}
"<="    {printf("LE\n"); semicolon=0; yycolno+=yyleng; RETURN_TOKEN(LE);}
"("     {printf("LPAR\n"); semicolon=0; yycolno+=yyleng; RETURN_TOKEN(LPAR);}
"["     {printf("LSQ\n"); semicolon=0; yycolno+=yyleng; RETURN_TOKEN(LSQ);}
"<"     {printf("LT\n"); semicolon=0; yycolno+=yyleng; RETURN_TOKEN(LT);}
"%"     {printf("MOD\n"); semicolon=0; yycolno+=yyleng; RETURN_TOKEN(MOD);}
"!="    {printf("NE\n"); semicolon=0; yycolno+=yyleng; RETURN_TOKEN(NE);}
"!"     {printf("NOT\n"); semicolon=0; yycolno+=yyleng; RETURN_TOKEN(NOT);}
"&&"    {printf("AND\n"); semicolon=0; yycolno+=yyleng; RETURN_TOKEN(AND);}
"||"    {printf("OR\n"); semicolon=0; yycolno+=yyleng; RETURN_TOKEN(OR);}
"}"     {printf("RBRACE\n"); semicolon=1; yycolno+=yyleng; RETURN_TOKEN(RBRACE);}
")"     {printf("RPAR\n"); semicolon=1; yycolno+=yyleng; RETURN_TOKEN(RPAR);}
"]"     {printf("RSQ\n"); semicolon=1; yycolno+=yyleng; RETURN_TOKEN(RSQ);}

 /* KEYWORDS */
package         {printf("PACKAGE\n"); semicolon=0; yycolno+=yyleng; RETURN_TOKEN(PACKAGE);}
return          {printf("RETURN\n"); semicolon=1; yycolno+=yyleng; RETURN_TOKEN(RETURN);}
else            {printf("ELSE\n"); semicolon=0; yycolno+=yyleng; RETURN_TOKEN(ELSE);}
for             {printf("FOR\n"); semicolon=0; yycolno+=yyleng; RETURN_TOKEN(FOR);}
if              {printf("IF\n"); semicolon=0; yycolno+=yyleng; RETURN_TOKEN(IF);}
var             {printf("VAR\n"); semicolon=0; yycolno+=yyleng; RETURN_TOKEN(VAR);}
int             {printf("INT\n"); semicolon=0; yycolno+=yyleng; RETURN_TOKEN(INT);}
float32         {printf("FLOAT32\n"); semicolon=0; yycolno+=yyleng; RETURN_TOKEN(FLOAT32);}
bool            {printf("BOOL\n"); semicolon=0; yycolno+=yyleng; RETURN_TOKEN(BOOL);}
string          {printf("STRING\n"); semicolon=0; yycolno+=yyleng; RETURN_TOKEN(STRING);}
fmt.Println     {printf("PRINT\n"); semicolon=0; yycolno+=yyleng; RETURN_TOKEN(PRINT);}
strconv.Atoi    {printf("PARSEINT\n"); semicolon=0; yycolno+=yyleng; RETURN_TOKEN(PARSEINT);}
func            {printf("FUNC\n"); semicolon=0; yycolno+=yyleng; RETURN_TOKEN(FUNC);}
os.Args         {printf("CMDARGS\n"); semicolon=0; yycolno+=yyleng; RETURN_TOKEN(CMDARGS);}

 /* RESERVED */
"++"            {printf("RESERVED(++)\n"); semicolon=0; yycolno+=yyleng; RETURN_TOKEN(RESERVED);}
"--"            {printf("RESERVED(--)\n"); semicolon=0; yycolno+=yyleng; RETURN_TOKEN(RESERVED);}
break           {printf("RESERVED(break)\n"); semicolon=0; yycolno+=yyleng; RETURN_TOKEN(RESERVED);}
case            {printf("RESERVED(case)\n"); semicolon=0; yycolno+=yyleng; RETURN_TOKEN(RESERVED);}
chan            {printf("RESERVED(chan)\n"); semicolon=0; yycolno+=yyleng; RETURN_TOKEN(RESERVED);}
const           {printf("RESERVED(const)\n"); semicolon=0; yycolno+=yyleng; RETURN_TOKEN(RESERVED);}
continue        {printf("RESERVED(continue)\n"); semicolon=0; yycolno+=yyleng; RETURN_TOKEN(RESERVED);}
default         {printf("RESERVED(default)\n"); semicolon=0; yycolno+=yyleng; RETURN_TOKEN(RESERVED);}
defer           {printf("RESERVED(defer)\n"); semicolon=0; yycolno+=yyleng; RETURN_TOKEN(RESERVED);}
fallthrough     {printf("RESERVED(fallthrough)\n"); semicolon=0; yycolno+=yyleng; RETURN_TOKEN(RESERVED);}
go              {printf("RESERVED(go)\n"); semicolon=0; yycolno+=yyleng; RETURN_TOKEN(RESERVED);}
goto            {printf("RESERVED(goto)\n"); semicolon=0; yycolno+=yyleng; RETURN_TOKEN(RESERVED);}
import          {printf("RESERVED(import)\n"); semicolon=0; yycolno+=yyleng; RETURN_TOKEN(RESERVED);}
interface       {printf("RESERVED(interface)\n"); semicolon=0; yycolno+=yyleng; RETURN_TOKEN(RESERVED);}
map             {printf("RESERVED(map)\n"); semicolon=0; yycolno+=yyleng; RETURN_TOKEN(RESERVED);}
range           {printf("RESERVED(range)\n"); semicolon=0; yycolno+=yyleng; RETURN_TOKEN(RESERVED);}
select          {printf("RESERVED(select)\n"); semicolon=0; yycolno+=yyleng; RETURN_TOKEN(RESERVED);}
struct          {printf("RESERVED(struct)\n"); semicolon=0; yycolno+=yyleng; RETURN_TOKEN(RESERVED);}
switch          {printf("RESERVED(switch)\n"); semicolon=0; yycolno+=yyleng; RETURN_TOKEN(RESERVED);}
type            {printf("RESERVED(type)\n"); semicolon=0; yycolno+=yyleng; RETURN_TOKEN(RESERVED);}


 /* INTLIT */
[1-9]{number}*              {printf("INTLIT(%s)\n", yytext); semicolon=1; yycolno+=yyleng;  RETURN_TOKEN(INTLIT);}

0                           {printf("INTLIT(%s)\n", yytext); semicolon=1; yycolno+=yyleng;  RETURN_TOKEN(INTLIT);}

(0x|0X)[0-9a-fA-F]+         {printf("INTLIT(%s)\n", yytext); semicolon=1; yycolno+=yyleng;  RETURN_TOKEN(INTLIT);}

0[0-7]+                     {printf("INTLIT(%s)\n", yytext); semicolon=1; yycolno+=yyleng;  RETURN_TOKEN(INTLIT);}

0{number}+                  {printf("Line %d, column %d: invalid octal constant (%s)\n",yylineno, yycolno, yytext); semicolon=0; yycolno+=yyleng;}




 /* REALLIT */
 /*parte inteira seguida de ponto, opcional parte fraccionaria e/ou expoente*/
{number}+"."(({number}+)|(e|E)("+"|"-")?{number}+|({number}+)(e|E)("+"|"-")?{number}+)?     {printf("REALLIT(%s)\n", yytext); semicolon=1; yycolno+=yyleng;   RETURN_TOKEN(REALLIT);}

 /*ponto com parte fraccionaria, opcional seguida de expoente*/
"."{number}+((e|E)("+"|"-")?{number}+)?                                                     {printf("REALLIT(%s)\n", yytext); semicolon=1; yycolno+=yyleng;  RETURN_TOKEN(REALLIT);}

 /*parte inteira seguida de expoente*/
{number}+(e|E)("+"|"-")?{number}+                                                           {printf("REALLIT(%s)\n", yytext); semicolon=1; yycolno+=yyleng;  RETURN_TOKEN(REALLIT);}


 /* STRLIT */
\"                                                      {BEGIN STRLITERR; begcol=yycolno;yycolno++;}
 /*string completa sem erros*/
<STRLITERR>([^\r\n"\\]*|(\\(t|n|r|\\|\"|f)))*\"            {printf("STRLIT(\"%s)\n", yytext); semicolon=1;yycolno+=yyleng; BEGIN 0;   RETURN_TOKEN(STRLIT);}


 /* Erros */
<STRLITERR>\\{newline}             {BEGIN 0; printf("Line %d, column %d: invalid escape sequence (\\)\n", yylineno, yycolno);
                                    printf("Line %d, column %d: unterminated string literal\n", yylineno, begcol);
                                    yycolno=1;yylineno++;semicolon=0;}
<STRLITERR>\\(t|n|r|\\|\"|f)       {BEGIN STRLITERROR;yycolno+=yyleng;}
<STRLITERR>\\[^nrft"\\]            {BEGIN STRLITERROR; printf("Line %d, column %d: invalid escape sequence (%s)\n", yylineno, yycolno, yytext); yycolno+=yyleng;semicolon=0;}
<STRLITERR>{newline}               {BEGIN 0; printf("Line %d, column %d: unterminated string literal\n", yylineno, begcol); yycolno=1;yylineno++;semicolon=0;}
<STRLITERR>.                       {BEGIN STRLITERROR;yycolno+=yyleng; }
<STRLITERR><<EOF>>                 {printf("Line %d, column %d: unterminated string literal\n", yylineno, begcol);BEGIN 0;}


<STRLITERROR>\\{newline}        {BEGIN 0; printf("Line %d, column %d: invalid escape sequence (\\)\n", yylineno, yycolno);
                                    printf("Line %d, column %d: unterminated string literal\n", yylineno, begcol);
                                    yycolno=1;yylineno++;semicolon=0;}
<STRLITERROR>\\[^nrft"\\]       {printf("Line %d, column %d: invalid escape sequence (%s)\n", yylineno, yycolno, yytext); yycolno+=yyleng;semicolon=0;}
<STRLITERROR>{newline}          {BEGIN 0; printf("Line %d, column %d: unterminated string literal\n", yylineno, begcol); yycolno=1;yylineno++;semicolon=0;}
<STRLITERROR>\\(t|n|r|\\|\"|f)  {;yycolno+=yyleng;}
<STRLITERROR>\"                 {yycolno+=yyleng;BEGIN 0;}
<STRLITERROR>\\                 {printf("Line %d, column %d: invalid escape sequence (\\)\n", yylineno, yycolno); yycolno+=yyleng;}
<STRLITERROR><<EOF>>            {printf("Line %d, column %d: unterminated string literal\n", yylineno, begcol); BEGIN 0;}
<STRLITERROR>.                  {yycolno+=yyleng;}


 /* IDs */
({letter}|"_")({letter}|{number}|"_")*      {printf("ID(%s)\n", yytext);semicolon=1; yycolno+=yyleng;   RETURN_TOKEN(ID);}

 /*COMMENTS*/
"//"    {BEGIN COMMENT1LINE;yycolno+=yyleng;}

<COMMENT1LINE>{newline}     {BEGIN 0;yylineno++;yycolno=1;}
<COMMENT1LINE>.             {yycolno+=yyleng;}


"/*"                            {BEGIN COMMENTMULTILINE;begcol=yycolno;begline=yylineno;yycolno+=yyleng;}
<COMMENTMULTILINE><<EOF>>       {printf("Line %d, column %d: unterminated comment\n",begline, begcol); BEGIN 0; }
<COMMENTMULTILINE>"*/"          {BEGIN 0;yycolno+=yyleng;}
<COMMENTMULTILINE>{newline}     {yycolno=1;yylineno++;}
<COMMENTMULTILINE>.             {yycolno+=yyleng;}




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

int yywrap()
{
    return 1;
}

void yyerror ( char *s) {
    printf (" Line  %d,  column  %d: %s: %s\n", yylineno, yycolno, s, yytext );
}
