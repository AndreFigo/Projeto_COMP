%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "utils.h"
    #include "AST.h"
    #include "structures.h"
    #include "y.tab.h"


    int yylex(void);
    void yyerror (char *s);

    int l_flag = 0, t_flag = 0;
    int lexical_error = 0, syntax_error = 0;

    ast_node_t *program = NULL; // root
    ast_node_t *aux_node = NULL;
    token_t null_token = {.text= NULL, .n_col=-1, .n_line=-1};
%}

%union{
    token_t token;
    ast_node_t *ast_node;
}

%token <token> SEMICOLON COMMA
%token <token> BLANKID
%token <token> ASSIGN
%token <token> STAR DIV MINUS PLUS MOD
%token <token> EQ GT GE LE LT NE
%token <token> LBRACE LPAR LSQ RBRACE RPAR RSQ
%token <token> NOT AND OR
%token <token> ELSE IF RETURN FOR
%token <token> FLOAT32 INT VAR BOOL STRING
%token <token> PARSEINT PRINT PACKAGE FUNC CMDARGS RESERVED
%token <token> ID STRLIT INTLIT REALLIT 

%type <ast_node> Program Declarations VarDeclaration VarSpec CommaId Type FuncDeclaration
%type <ast_node> Parameters CommaIdType FuncBody VarsAndStatements Statement StatementSemicolon
%type <ast_node> ParseArgs FuncInvocation CommaExpr Expr

%right ASSIGN 
%left OR
%left AND
%left EQ GT GE LE LT NE
%left MINUS PLUS 
%left STAR DIV MOD
%right NOT

%%

Program:            PACKAGE ID SEMICOLON Declarations                                           {$$=program=create_node("Program", null_token);  add_children($$,1,$4);}
            |       PACKAGE ID SEMICOLON                                                        {$$=program=create_node("Program", null_token);}
            
            ;
            
Declarations:       VarDeclaration SEMICOLON                                                    {$$=$1;}
            |       FuncDeclaration SEMICOLON                                                   {$$=$1;}
            |       Declarations VarDeclaration SEMICOLON                                       {add_siblings($1,1,$2);}
            |       Declarations FuncDeclaration SEMICOLON                                      {add_siblings($1,1,$2);}
            ;
            
VarDeclaration:     VAR VarSpec                                                                 {$$=split_vardecl($2, null_token); }
            |       VAR LPAR VarSpec SEMICOLON RPAR                                             {$$=split_vardecl($3, null_token);}
            ;
            
VarSpec:            ID CommaId Type                                                             {$$ = create_node("Id", $1);  add_siblings($3,2, $$, $2); $$=$3;}
            ;

CommaId:            COMMA ID CommaId                                                            {$$= create_node("Id", $2);  add_siblings($$,1,$3);}
            |       /*lambda*/                                                                  {$$=NULL;}
            ;

Type:               INT                                                                         {$$= create_node("Int", $1); }
            |       FLOAT32                                                                     {$$= create_node("Float32", $1);}
            |       BOOL                                                                        {$$= create_node("Bool", $1);}
            |       STRING                                                                      {$$= create_node("String", $1);}
            ;
  
FuncDeclaration:    FUNC ID LPAR Parameters RPAR Type FuncBody                                  {;}
            |       FUNC ID LPAR Parameters RPAR  FuncBody                                      {;}
            |       FUNC ID LPAR  RPAR Type FuncBody                                            {;}
            |       FUNC ID LPAR  RPAR  FuncBody                                                {;}

            ;
  
Parameters:         ID Type CommaIdType                                                         {;}
            ;

CommaIdType:        COMMA ID Type CommaIdType                                                  {;}
            |       /*lambda*/                                                                  {;}
            ;

FuncBody:           LBRACE VarsAndStatements RBRACE                                             {;}
            ;
  
VarsAndStatements:  VarsAndStatements  Statement SEMICOLON                                      {;}
            |       VarsAndStatements VarDeclaration SEMICOLON                                  {;}
            |       VarsAndStatements  SEMICOLON                                                {;}
            |       /*lambda*/                                                                  {;}
            ;

Statement:          ID ASSIGN Expr                                                              {;}

            |       LBRACE StatementSemicolon RBRACE                                            {;}

            |       IF Expr LBRACE StatementSemicolon RBRACE ELSE LBRACE StatementSemicolon RBRACE               {;}
            |       IF Expr LBRACE StatementSemicolon RBRACE                                    {;}

            |       FOR Expr LBRACE StatementSemicolon RBRACE                                   {;}
            |       FOR LBRACE StatementSemicolon RBRACE                                        {;}

            |       RETURN Expr                                                                 {;}
            |       RETURN                                                                      {;}

            |       FuncInvocation                                                              {;}
            |       ParseArgs                                                                   {;}

            |       PRINT LPAR Expr RPAR                                                        {;}
            |       PRINT LPAR STRLIT RPAR                                                      {;}

            |       error SEMICOLON                                                             {syntax_error = 1;}

            ;
  
StatementSemicolon: Statement SEMICOLON StatementSemicolon                                      {;}
            |       /*lambda*/                                                                  {;}
            ;
            
ParseArgs:          ID COMMA BLANKID ASSIGN PARSEINT LPAR CMDARGS LSQ Expr RSQ RPAR             {;}
            |       ID COMMA BLANKID ASSIGN PARSEINT LPAR error RPAR                            {syntax_error = 1;}
            ;

FuncInvocation:     ID LPAR Expr CommaExpr RPAR                                                 {;}
            |       ID LPAR  RPAR                                                               {;}
            |       ID LPAR  error RPAR                                                         {syntax_error = 1;}

            ;
CommaExpr:          COMMA Expr  CommaExpr                                                       {;}
            |       /*lambda*/                                                                  {;}
            ;

Expr:               Expr OR  Expr                                                               {;}
            |       Expr AND Expr                                                               {;}
            
            |       Expr LT Expr                                                                {;}
            |       Expr GT Expr                                                                {;}
            |       Expr EQ Expr                                                                {;}
            |       Expr NE Expr                                                                {;}
            |       Expr LE Expr                                                                {;}
            |       Expr GE Expr                                                                {;}

            |       Expr PLUS Expr                                                              {;}
            |       Expr MINUS Expr                                                             {;}
            |       Expr STAR Expr                                                              {;}
            |       Expr DIV Expr                                                               {;}
            |       Expr MOD Expr                                                               {;}
    
            |       NOT Expr                                                                    {;}
            |       MINUS Expr                                                                  {;}
            |       PLUS Expr                                                                   {;}
            
            |       INTLIT                                                                      {;}
            |       REALLIT                                                                     {;}
            |       ID                                                                          {;}
            |       FuncInvocation                                                              {;}
            |       LPAR Expr RPAR                                                              {;}
            |       LPAR error RPAR                                                             {syntax_error = 1;}
            ;

%%

void verify_flags(int argc, char * argv[]) {
    int has_flag=0;
    for(int i = 0; i < argc; i++){
        if (strcmp(argv[i], "-l")==0) {
            l_flag=1;
            t_flag=0;
            has_flag=1;
        }
        else if (strcmp(argv[i], "-t")==0) {
            l_flag=0;
            t_flag=1;
            has_flag=1;
        }
    }
    if (!has_flag)
        t_flag=1;
}

int main(int argc, char *argv[]) {

    verify_flags(argc, argv);

    if (l_flag){
        yylex();
    }else if(t_flag){
        if (yyparse()){         //error
            syntax_error=1;
        }
        
        print_program(program);
    }

    return 0;
}