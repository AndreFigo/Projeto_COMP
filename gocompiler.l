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
    extern int lexical_error;

    int semicolon=0;
    int yycolno=1;
    int begcol=0, begline=0;

    
%}
%%
 
 /* OPERATORS */
";"     {if (l_flag) printf("SEMICOLON\n"); semicolon=0;RETURN_TOKEN(SEMICOLON); yycolno+=yyleng;}
","     {if (l_flag) printf("COMMA\n"); semicolon=0; RETURN_TOKEN(COMMA); yycolno+=yyleng;}
"_"     {if (l_flag) printf("BLANKID\n"); semicolon=0; RETURN_TOKEN(BLANKID); yycolno+=yyleng;}
"="     {if (l_flag) printf("ASSIGN\n"); semicolon=0; RETURN_TOKEN(ASSIGN); yycolno+=yyleng;}
"*"     {if (l_flag) printf("STAR\n"); semicolon=0; RETURN_TOKEN(STAR); yycolno+=yyleng;}
"/"     {if (l_flag) printf("DIV\n"); semicolon=0; RETURN_TOKEN(DIV); yycolno+=yyleng;}
"-"     {if (l_flag) printf("MINUS\n"); semicolon=0;RETURN_TOKEN(MINUS); yycolno+=yyleng;}
"+"     {if (l_flag) printf("PLUS\n"); semicolon=0; RETURN_TOKEN(PLUS); yycolno+=yyleng;}
"=="    {if (l_flag) printf("EQ\n"); semicolon=0; RETURN_TOKEN(EQ); yycolno+=yyleng;}
">="    {if (l_flag) printf("GE\n"); semicolon=0; RETURN_TOKEN(GE); yycolno+=yyleng;}
">"     {if (l_flag) printf("GT\n"); semicolon=0; RETURN_TOKEN(GT); yycolno+=yyleng;}
"{"     {if (l_flag) printf("LBRACE\n"); semicolon=0; RETURN_TOKEN(LBRACE); yycolno+=yyleng;}
"<="    {if (l_flag) printf("LE\n"); semicolon=0; RETURN_TOKEN(LE); yycolno+=yyleng;}
"("     {if (l_flag) printf("LPAR\n"); semicolon=0; RETURN_TOKEN(LPAR); yycolno+=yyleng;}
"["     {if (l_flag) printf("LSQ\n"); semicolon=0; RETURN_TOKEN(LSQ); yycolno+=yyleng;}
"<"     {if (l_flag) printf("LT\n"); semicolon=0; RETURN_TOKEN(LT); yycolno+=yyleng;}
"%"     {if (l_flag) printf("MOD\n"); semicolon=0; RETURN_TOKEN(MOD); yycolno+=yyleng; }
"!="    {if (l_flag) printf("NE\n"); semicolon=0; RETURN_TOKEN(NE); yycolno+=yyleng;}
"!"     {if (l_flag) printf("NOT\n"); semicolon=0; RETURN_TOKEN(NOT); yycolno+=yyleng;}
"&&"    {if (l_flag) printf("AND\n"); semicolon=0; RETURN_TOKEN(AND); yycolno+=yyleng;}
"||"    {if (l_flag) printf("OR\n"); semicolon=0; RETURN_TOKEN(OR); yycolno+=yyleng;}
"}"     {if (l_flag) printf("RBRACE\n"); semicolon=1; RETURN_TOKEN(RBRACE); yycolno+=yyleng;}
")"     {if (l_flag) printf("RPAR\n"); semicolon=1; RETURN_TOKEN(RPAR); yycolno+=yyleng;}
"]"     {if (l_flag) printf("RSQ\n"); semicolon=1; RETURN_TOKEN(RSQ); yycolno+=yyleng;}

 /* KEYWORDS */
package         {if (l_flag) printf("PACKAGE\n"); semicolon=0; RETURN_TOKEN(PACKAGE); yycolno+=yyleng;}
return          {if (l_flag) printf("RETURN\n"); semicolon=1; RETURN_TOKEN(RETURN); yycolno+=yyleng;}
else            {if (l_flag) printf("ELSE\n"); semicolon=0; RETURN_TOKEN(ELSE); yycolno+=yyleng;}
for             {if (l_flag) printf("FOR\n"); semicolon=0; RETURN_TOKEN(FOR); yycolno+=yyleng;}
if              {if (l_flag) printf("IF\n"); semicolon=0; RETURN_TOKEN(IF); yycolno+=yyleng;}
var             {if (l_flag) printf("VAR\n"); semicolon=0; RETURN_TOKEN(VAR); yycolno+=yyleng;}
int             {if (l_flag) printf("INT\n"); semicolon=0; RETURN_TOKEN(INT); yycolno+=yyleng;}
float32         {if (l_flag) printf("FLOAT32\n"); semicolon=0; RETURN_TOKEN(FLOAT32); yycolno+=yyleng;}
bool            {if (l_flag) printf("BOOL\n"); semicolon=0; RETURN_TOKEN(BOOL); yycolno+=yyleng;}
string          {if (l_flag) printf("STRING\n"); semicolon=0; RETURN_TOKEN(STRING); yycolno+=yyleng;}
fmt.Println     {if (l_flag) printf("PRINT\n"); semicolon=0; RETURN_TOKEN(PRINT); yycolno+=yyleng; }
strconv.Atoi    {if (l_flag) printf("PARSEINT\n"); semicolon=0; RETURN_TOKEN(PARSEINT); yycolno+=yyleng;}
func            {if (l_flag) printf("FUNC\n"); semicolon=0; RETURN_TOKEN(FUNC); yycolno+=yyleng;}
os.Args         {if (l_flag) printf("CMDARGS\n"); semicolon=0; RETURN_TOKEN(CMDARGS); yycolno+=yyleng;}

 /* RESERVED */
"++"            {if (l_flag) printf("RESERVED(++)\n"); semicolon=0; RETURN_TOKEN(RESERVED); yycolno+=yyleng;}
"--"            {if (l_flag) printf("RESERVED(--)\n"); semicolon=0; RETURN_TOKEN(RESERVED); yycolno+=yyleng;}
break           {if (l_flag) printf("RESERVED(break)\n"); semicolon=0; RETURN_TOKEN(RESERVED); yycolno+=yyleng;}
case            {if (l_flag) printf("RESERVED(case)\n"); semicolon=0; RETURN_TOKEN(RESERVED); yycolno+=yyleng;}
chan            {if (l_flag) printf("RESERVED(chan)\n"); semicolon=0; RETURN_TOKEN(RESERVED); yycolno+=yyleng;}
const           {if (l_flag) printf("RESERVED(const)\n"); semicolon=0; RETURN_TOKEN(RESERVED); yycolno+=yyleng;}
continue        {if (l_flag) printf("RESERVED(continue)\n"); semicolon=0; RETURN_TOKEN(RESERVED); yycolno+=yyleng;}
default         {if (l_flag) printf("RESERVED(default)\n"); semicolon=0; RETURN_TOKEN(RESERVED); yycolno+=yyleng;}
defer           {if (l_flag) printf("RESERVED(defer)\n"); semicolon=0; RETURN_TOKEN(RESERVED); yycolno+=yyleng;}
fallthrough     {if (l_flag) printf("RESERVED(fallthrough)\n"); semicolon=0; RETURN_TOKEN(RESERVED); yycolno+=yyleng;}
go              {if (l_flag) printf("RESERVED(go)\n"); semicolon=0; RETURN_TOKEN(RESERVED); yycolno+=yyleng;}
goto            {if (l_flag) printf("RESERVED(goto)\n"); semicolon=0; RETURN_TOKEN(RESERVED); yycolno+=yyleng;}
import          {if (l_flag) printf("RESERVED(import)\n"); semicolon=0; RETURN_TOKEN(RESERVED); yycolno+=yyleng;}
interface       {if (l_flag) printf("RESERVED(interface)\n"); semicolon=0; RETURN_TOKEN(RESERVED); yycolno+=yyleng;}
map             {if (l_flag) printf("RESERVED(map)\n"); semicolon=0; RETURN_TOKEN(RESERVED); yycolno+=yyleng;}
range           {if (l_flag) printf("RESERVED(range)\n"); semicolon=0; RETURN_TOKEN(RESERVED); yycolno+=yyleng;}
select          {if (l_flag) printf("RESERVED(select)\n"); semicolon=0; RETURN_TOKEN(RESERVED); yycolno+=yyleng;}
struct          {if (l_flag) printf("RESERVED(struct)\n"); semicolon=0; RETURN_TOKEN(RESERVED); yycolno+=yyleng;}
switch          {if (l_flag) printf("RESERVED(switch)\n"); semicolon=0; RETURN_TOKEN(RESERVED); yycolno+=yyleng;}
type            {if (l_flag) printf("RESERVED(type)\n"); semicolon=0; RETURN_TOKEN(RESERVED); yycolno+=yyleng;}


 /* INTLIT */
[1-9]{number}*              {if (l_flag) printf("INTLIT(%s)\n", yytext); semicolon=1; RETURN_TOKEN(INTLIT); yycolno+=yyleng; }

0                           {if (l_flag) printf("INTLIT(%s)\n", yytext); semicolon=1; RETURN_TOKEN(INTLIT); yycolno+=yyleng; }

(0x|0X)[0-9a-fA-F]+         {if (l_flag) printf("INTLIT(%s)\n", yytext); semicolon=1; RETURN_TOKEN(INTLIT); yycolno+=yyleng; }

0[0-7]+                     {if (l_flag) printf("INTLIT(%s)\n", yytext); semicolon=1; RETURN_TOKEN(INTLIT); yycolno+=yyleng; }

0{number}+                  {printf("Line %d, column %d: invalid octal constant (%s)\n",yylineno, yycolno, yytext);lexical_error = 1; semicolon=0; yycolno+=yyleng;}




 /* REALLIT */
 /*parte inteira seguida de ponto, opcional parte fraccionaria e/ou expoente*/
{number}+"."(({number}+)|(e|E)("+"|"-")?{number}+|({number}+)(e|E)("+"|"-")?{number}+)?     {if (l_flag) printf("REALLIT(%s)\n", yytext); semicolon=1; RETURN_TOKEN(REALLIT); yycolno+=yyleng;  }

 /*ponto com parte fraccionaria, opcional seguida de expoente*/
"."{number}+((e|E)("+"|"-")?{number}+)?                                                     {if (l_flag) printf("REALLIT(%s)\n", yytext); semicolon=1; RETURN_TOKEN(REALLIT); yycolno+=yyleng; }

 /*parte inteira seguida de expoente*/
{number}+(e|E)("+"|"-")?{number}+                                                           {if (l_flag) printf("REALLIT(%s)\n", yytext); semicolon=1;  RETURN_TOKEN(REALLIT); yycolno+=yyleng;}


 /* STRLIT */
\"                                                      {BEGIN STRLITERR; begcol=yycolno;yycolno++;}
 /*string completa sem erros*/
<STRLITERR>([^\r\n"\\]*|(\\(t|n|r|\\|\"|f)))*\"            {if (l_flag) printf("STRLIT(\"%s)\n", yytext); semicolon=1;  RETURN_TOKEN(STRLIT); yycolno+=yyleng; BEGIN 0; }


 /* Erros */
<STRLITERR>\\{newline}             {BEGIN 0; printf("Line %d, column %d: invalid escape sequence (\\)\n", yylineno, yycolno);
                                    printf("Line %d, column %d: unterminated string literal\n", yylineno, begcol); lexical_error = 1;
                                    yycolno=1;yylineno++;semicolon=0;}
<STRLITERR>\\(t|n|r|\\|\"|f)       {BEGIN STRLITERROR;yycolno+=yyleng;}
<STRLITERR>\\[^nrft"\\]            {BEGIN STRLITERROR; printf("Line %d, column %d: invalid escape sequence (%s)\n", yylineno, yycolno, yytext); lexical_error = 1; yycolno+=yyleng;semicolon=0;}
<STRLITERR>{newline}               {BEGIN 0; printf("Line %d, column %d: unterminated string literal\n", yylineno, begcol);lexical_error = 1; yycolno=1;yylineno++;semicolon=0;}
<STRLITERR>.                       {BEGIN STRLITERROR;yycolno+=yyleng; }
<STRLITERR><<EOF>>                 {printf("Line %d, column %d: unterminated string literal\n", yylineno, begcol);lexical_error = 1;BEGIN 0;}


<STRLITERROR>\\{newline}        {BEGIN 0; printf("Line %d, column %d: invalid escape sequence (\\)\n", yylineno, yycolno);
                                    printf("Line %d, column %d: unterminated string literal\n", yylineno, begcol); lexical_error = 1;
                                    yycolno=1;yylineno++;semicolon=0;}
<STRLITERROR>\\[^nrft"\\]       {printf("Line %d, column %d: invalid escape sequence (%s)\n", yylineno, yycolno, yytext); yycolno+=yyleng;semicolon=0; lexical_error = 1;}
<STRLITERROR>{newline}          {BEGIN 0; printf("Line %d, column %d: unterminated string literal\n", yylineno, begcol);lexical_error = 1; yycolno=1;yylineno++;semicolon=0;}
<STRLITERROR>\\(t|n|r|\\|\"|f)  {;yycolno+=yyleng;}
<STRLITERROR>\"                 {yycolno+=yyleng;BEGIN 0;}
<STRLITERROR>\\                 {printf("Line %d, column %d: invalid escape sequence (\\)\n", yylineno, yycolno); lexical_error = 1; yycolno+=yyleng;}
<STRLITERROR><<EOF>>            {printf("Line %d, column %d: unterminated string literal\n", yylineno, begcol); lexical_error = 1; BEGIN 0;}
<STRLITERROR>.                  {yycolno+=yyleng;}


 /* IDs */
({letter}|"_")({letter}|{number}|"_")*      {if (l_flag) printf("ID(%s)\n", yytext);semicolon=1; RETURN_TOKEN(ID); yycolno+=yyleng;  }

 /*COMMENTS*/
"//"    {BEGIN COMMENT1LINE;yycolno+=yyleng;}

<COMMENT1LINE>{newline}     {BEGIN 0;yylineno++;yycolno=1;}
<COMMENT1LINE>.             {yycolno+=yyleng;}


"/*"                            {BEGIN COMMENTMULTILINE;begcol=yycolno;begline=yylineno;yycolno+=yyleng;}
<COMMENTMULTILINE><<EOF>>       {printf("Line %d, column %d: unterminated comment\n",begline, begcol); lexical_error = 1; BEGIN 0; }
<COMMENTMULTILINE>"*/"          {BEGIN 0;yycolno+=yyleng;}
<COMMENTMULTILINE>{newline}     {yycolno=1;yylineno++;}
<COMMENTMULTILINE>.             {yycolno+=yyleng;}




{newline} {
            if (semicolon){
                if (l_flag) printf("SEMICOLON\n");
                semicolon=0;
                RETURN_TOKEN(SEMICOLON);
            };
            yylineno++;
            yycolno=1;
            } 

<<EOF>>  {if (semicolon){ if (l_flag) printf("SEMICOLON\n"); RETURN_TOKEN(SEMICOLON);}; yyterminate();} 

\t  {yycolno+=yyleng;}
" "   {yycolno+=yyleng;}

 /* Caraters ilegais*/
.  {printf("Line %d, column %d: illegal character (%s)\n",yylineno, yycolno, yytext); lexical_error = 1; yycolno+=yyleng;}


%%

int yywrap()
{
    return 1;
}

void yyerror ( char *s) {
    printf (" Line  %d,  column  %d: %s: %s\n", yylineno, yycolno, s, yytext );
}
