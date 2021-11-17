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
    ast_node_t *aux_node = NULL, *aux_node2 = NULL;
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
%nonassoc UNARY

%%

Program:            PACKAGE ID SEMICOLON Declarations                                           {$$=program=create_node("Program", null_token);
                                                                                                    add_children($$,1,$4);
                                                                                                }
            |       PACKAGE ID SEMICOLON                                                        {$$=program=create_node("Program", null_token);}
            
            ;
            
Declarations:       VarDeclaration SEMICOLON                                                    {$$=$1;}
            |       FuncDeclaration SEMICOLON                                                   {$$=$1;}
            |       Declarations VarDeclaration SEMICOLON                                       {$$=add_siblings($1,1,$2);}
            |       Declarations FuncDeclaration SEMICOLON                                      {$$=add_siblings($1,1,$2);}
            ;
            
VarDeclaration:     VAR VarSpec                                                                 {$$=split_vardecl($2, null_token); }
            |       VAR LPAR VarSpec SEMICOLON RPAR                                             {$$=split_vardecl($3, null_token);}
            ;
            
VarSpec:            ID CommaId Type                                                             {$$ = create_node("Id", $1);
                                                                                                    $$=add_siblings($3,2, $$, $2);
                                                                                                }
            ;

CommaId:            COMMA ID CommaId                                                            {$$= create_node("Id", $2);
                                                                                                    $$=add_siblings($$,1,$3);
                                                                                                }
            |       /*lambda*/                                                                  {$$=NULL;}
            ;

Type:               INT                                                                         {$$= create_node("Int", $1); }
            |       FLOAT32                                                                     {$$= create_node("Float32", $1);}
            |       BOOL                                                                        {$$= create_node("Bool", $1);}
            |       STRING                                                                      {$$= create_node("String", $1);}
            ;
  
FuncDeclaration:    FUNC ID LPAR Parameters RPAR Type FuncBody                                  {$$= create_node("FuncDecl", null_token);
                                                                                                    aux_node= create_node("FuncHeader", null_token); 
                                                                                                    
                                                                                                    add_children(aux_node, 3, create_node("Id", $2),$6,$4);
                                                                                                    add_children($$,2,aux_node, $7); }
            |       FUNC ID LPAR Parameters RPAR  FuncBody                                      {$$= create_node("FuncDecl", null_token);
                                                                                                    aux_node= create_node("FuncHeader", null_token); 
                                                                                                    add_children(aux_node, 2,  create_node("Id", $2),$4);
                                                                                                    add_children($$,2,aux_node, $6); }
            ;
  
Parameters:         ID Type CommaIdType                                                         {$$=create_node("FuncParams", null_token);
                                                                                                    aux_node = create_node("ParamDecl", null_token);
                                                                                                    add_children(aux_node,2,$2, create_node("Id", $1));
                                                                                                    add_children($$,2, aux_node, $3);}
            |       /*lambda*/                                                                  {$$=create_node("FuncParams", null_token);}
            ;

CommaIdType:        COMMA ID Type CommaIdType                                                   {$$ = create_node("ParamDecl", null_token);
                                                                                                    add_children($$,2, $3, create_node("Id", $2));
                                                                                                    $$=add_siblings($$, 1, $4);}
            |       /*lambda*/                                                                  {$$=NULL;}
            ;

FuncBody:           LBRACE VarsAndStatements RBRACE                                             {$$ = create_node("FuncBody", null_token);
                                                                                                    add_children($$, 1, $2);
                                                                                                }
            ;
  
VarsAndStatements:  Statement SEMICOLON  VarsAndStatements                                      {$$=add_siblings($1, 1, $3);}
            |       error SEMICOLON  VarsAndStatements                                          {syntax_error = 1;   /*printf("stat1\n");*/  $$=create_node("Error",null_token); 
                                                                                                    $$=add_siblings($$, 1, $3); }
            |       VarDeclaration SEMICOLON VarsAndStatements                                  {$$=add_siblings($1, 1, $3);}
            |       SEMICOLON VarsAndStatements                                                 {$$=$2;/*!!!!!!!!!!!! ATENÇAO AQUI*/}
            |       /*lambda*/                                                                  {$$=NULL;}
            ;

Statement:          ID ASSIGN Expr                                                              {$$=create_node("Assign", null_token);
                                                                                                    add_children($$, 2, create_node("Id",$1), $3);
                                                                                                }

            |       LBRACE StatementSemicolon RBRACE                                            {   if ($2==NULL){ $$=$2;}
                                                                                                    else if ($2->nSibling == NULL) {$$=$2;}
                                                                                                    else{
                                                                                                        $$ = create_node("Block", null_token);
                                                                                                        add_children($$, 1, $2);
                                                                                                    }
                                                                                                }

            |       IF Expr LBRACE StatementSemicolon RBRACE ELSE LBRACE StatementSemicolon RBRACE              {$$=create_node("If", null_token);
                                                                                                                    aux_node = create_node("Block", null_token);
                                                                                                                    add_children(aux_node, 1, $4);
                                                                                                                    aux_node2 = create_node("Block", null_token);
                                                                                                                    add_children(aux_node2, 1, $8);
                                                                                                                    add_children($$, 3, $2, aux_node, aux_node2);
                                                                                                                }
            |       IF Expr LBRACE StatementSemicolon RBRACE                                    {$$=create_node("If", null_token);
                                                                                                    aux_node = create_node("Block", null_token);
                                                                                                    add_children(aux_node, 1, $4);
                                                                                                    aux_node2 = create_node("Block", null_token);
                                                                                                    add_children($$, 3, $2, aux_node, aux_node2);}

            |       FOR Expr LBRACE StatementSemicolon RBRACE                                   {$$=create_node("For", null_token);
                                                                                                    aux_node = create_node("Block", null_token);
                                                                                                    add_children(aux_node, 1, $4);
                                                                                                    add_children($$, 2, $2, aux_node);
                                                                                                }
            |       FOR LBRACE StatementSemicolon RBRACE                                        {$$=create_node("For", null_token);
                                                                                                    aux_node = create_node("Block", null_token);
                                                                                                    add_children(aux_node, 1, $3);
                                                                                                    add_children($$, 1, aux_node);
                                                                                                }

            |       RETURN Expr                                                                 {$$ = create_node("Return", null_token);
                                                                                                    add_children($$, 1, $2);
                                                                                                }
            |       RETURN                                                                      {$$ =  create_node("Return", null_token);}

            |       FuncInvocation                                                              {$$=$1;}
            |       ParseArgs                                                                   {$$=$1;}

            |       PRINT LPAR Expr RPAR                                                        {$$ = create_node("Print", null_token);
                                                                                                    add_children($$, 1, $3);
                                                                                                }
            |       PRINT LPAR STRLIT RPAR                                                      {$$ = create_node("Print", null_token);
                                                                                                    add_children($$, 1, create_node("StrLit", $3));
                                                                                                }
            |       PRINT LPAR error RPAR                                                      {$$ = create_node("Print", null_token);
                                                                                                    add_children($$, 1, create_node("Error", null_token));
                                                                                                    syntax_error = 1;
                                                                                                   /* printf("print\n");*/
                                                                                                }


            ;
  
StatementSemicolon: Statement SEMICOLON StatementSemicolon                                      {$$=add_siblings($1, 1, $3); }
            |       error SEMICOLON StatementSemicolon                                          {syntax_error = 1;   /*printf("stat2\n");*/  $$=create_node("Error",null_token); 
                                                                                                    $$=add_siblings($$, 1, $3); }
            |       /*lambda*/                                                                  {$$=NULL;}
            ;
            
ParseArgs:          ID COMMA BLANKID ASSIGN PARSEINT LPAR CMDARGS LSQ Expr RSQ RPAR             {$$=create_node("ParseArgs", null_token);
                                                                                                    add_children($$, 2, create_node("Id", $1),$9);
                                                                                                }
            |       ID COMMA BLANKID ASSIGN PARSEINT LPAR error RPAR                            {syntax_error = 1;  $$ = create_node("Error",null_token);}
            ;

FuncInvocation:     ID LPAR Expr CommaExpr RPAR                                                 {$$ = create_node("Call", null_token);
                                                                                                    add_children($$, 3, create_node("Id", $1), $3, $4);
                                                                                                }
            |       ID LPAR  RPAR                                                               {$$ = create_node("Call", null_token);
                                                                                                    add_children($$, 1, create_node("Id", $1));
                                                                                                }
            |       ID LPAR  error RPAR                                                         {syntax_error = 1;    $$ = create_node("Error",null_token);}

            ;
CommaExpr:          COMMA Expr CommaExpr                                                        {$$=add_siblings($2,1,$3); }
            |       /*lambda*/                                                                  {$$=NULL;}
            ;

Expr:               Expr OR  Expr                                                               {$$ = create_node("Or", null_token);
                                                                                                    add_children($$, 2, $1, $3);
                                                                                                }
            |       Expr AND Expr                                                               {$$ = create_node("And", null_token);
                                                                                                    add_children($$, 2, $1, $3);
                                                                                                }
            
            |       Expr LT Expr                                                                {$$ = create_node("Lt", null_token);
                                                                                                    add_children($$, 2, $1, $3);
                                                                                                }
            |       Expr GT Expr                                                                {$$ = create_node("Gt", null_token);
                                                                                                    add_children($$, 2, $1, $3);
                                                                                                }
            |       Expr EQ Expr                                                                {$$ = create_node("Eq", null_token);
                                                                                                    add_children($$, 2, $1, $3);
                                                                                                }
            |       Expr NE Expr                                                                {$$ = create_node("Ne", null_token);
                                                                                                    add_children($$, 2, $1, $3);
                                                                                                }
            |       Expr LE Expr                                                                {$$ = create_node("Le", null_token);
                                                                                                    add_children($$, 2, $1, $3);
                                                                                                }
            |       Expr GE Expr                                                                {$$ = create_node("Ge", null_token);
                                                                                                    add_children($$, 2, $1, $3);
                                                                                                }

            |       Expr PLUS Expr                                                              {$$ = create_node("Add", null_token);
                                                                                                    add_children($$, 2, $1, $3);
                                                                                                }
            |       Expr MINUS Expr                                                             {$$ = create_node("Sub", null_token);
                                                                                                    add_children($$, 2, $1, $3);
                                                                                                }
            |       Expr STAR Expr                                                              {$$ = create_node("Mul", null_token);
                                                                                                    add_children($$, 2, $1, $3);
                                                                                                }
            |       Expr DIV Expr                                                               {$$ = create_node("Div", null_token);
                                                                                                    add_children($$, 2, $1, $3);
                                                                                                }
            |       Expr MOD Expr                                                               {$$ = create_node("Mod", null_token);
                                                                                                    add_children($$, 2, $1, $3);
                                                                                                }

            |       NOT Expr                                                                    {$$ = create_node("Not", null_token);
                                                                                                    add_children($$, 1, $2);
                                                                                                }
            |       MINUS Expr             %prec UNARY                                          {$$ = create_node("Minus", null_token);
                                                                                                    add_children($$, 1, $2);
                                                                                                }
            |       PLUS Expr            %prec UNARY                                            {$$ = create_node("Plus", null_token);
                                                                                                    add_children($$, 1, $2);
                                                                                                }
            
            |       INTLIT                                                                      {$$ = create_node("IntLit", $1);}
            |       REALLIT                                                                     {$$= create_node("RealLit", $1);}
            |       ID                                                                          {$$ = create_node("Id", $1);}
            |       FuncInvocation                                                              {$$=$1;}
            |       LPAR Expr RPAR                                                              {$$=$2;}
            |       LPAR error RPAR                                                             {syntax_error = 1;  $$ = create_node("Error",null_token);}
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