%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "utils.h"
    #include "y.tab.h"


    int yylex(void);
    void yyerror (const char *s);

    int l_flag = 0, t_flag = 0;
%}

%union{
    token_t token;
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

%right ASSIGN 
%left OR
%left AND
%left EQ GT GE LE LT NE
%left MINUS PLUS 
%left STAR DIV MOD
%right NOT

%%

Program:            PACKAGE ID SEMICOLON Declarations                                           {;}
            |       PACKAGE ID SEMICOLON                                                        {;}
            
            ;
            
Declarations:       VarDeclaration SEMICOLON                                                    {;}
            |       FuncDeclaration SEMICOLON                                                   {;}
            |       Declarations VarDeclaration SEMICOLON                                       {;}
            |       Declarations FuncDeclaration SEMICOLON                                      {;}
            ;
            
VarDeclaration:     VAR VarSpec                                                                 {;}
            |       VAR LPAR VarSpec SEMICOLON RPAR                                             {;}
            ;
            
VarSpec:            ID CommaId Type                                                             {;}
            ;

CommaId:            CommaId COMMA ID                                                            {;}
            |       /*lambda*/                                                                  {;}
            ;

Type:               INT                                                                         {;}
            |       FLOAT32                                                                     {;}
            |       BOOL                                                                        {;}
            |       STRING                                                                      {;}
            ;
  
FuncDeclaration:    FUNC ID LPAR Parameters RPAR Type FuncBody                                  {;}
            |       FUNC ID LPAR Parameters RPAR  FuncBody                                      {;}
            |       FUNC ID LPAR  RPAR Type FuncBody                                            {;}
            |       FUNC ID LPAR  RPAR  FuncBody                                                {;}

            ;
  
Parameters:         ID Type CommaIdType                                                         {;}
            ;

CommaIdType:        CommaIdType COMMA ID Type                                                   {;}
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

            ;
  
StatementSemicolon: StatementSemicolon Statement SEMICOLON                                      {;}
            |       /*lambda*/                                                                  {;}
            ;
            
ParseArgs:          ID COMMA BLANKID ASSIGN PARSEINT LPAR CMDARGS LSQ Expr RSQ RPAR             {;}
            ;

FuncInvocation:     ID LPAR Expr CommaExpr RPAR                                                 {;}
            |       ID LPAR  RPAR                                                               {;}

            ;
CommaExpr:          CommaExpr COMMA Expr                                                        {;}
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
            |       LPAR Expr RPAR
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
        yyparse();
    }
    return 0;
}