/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    SEMICOLON = 258,
    COMMA = 259,
    BLANKID = 260,
    ASSIGN = 261,
    STAR = 262,
    DIV = 263,
    MINUS = 264,
    PLUS = 265,
    MOD = 266,
    EQ = 267,
    GT = 268,
    GE = 269,
    LE = 270,
    LT = 271,
    NE = 272,
    LBRACE = 273,
    LPAR = 274,
    LSQ = 275,
    RBRACE = 276,
    RPAR = 277,
    RSQ = 278,
    NOT = 279,
    AND = 280,
    OR = 281,
    ELSE = 282,
    IF = 283,
    RETURN = 284,
    FOR = 285,
    FLOAT32 = 286,
    INT = 287,
    VAR = 288,
    BOOL = 289,
    STRING = 290,
    PARSEINT = 291,
    PRINT = 292,
    PACKAGE = 293,
    FUNC = 294,
    CMDARGS = 295,
    RESERVED = 296,
    ID = 297,
    STRLIT = 298,
    INTLIT = 299,
    REALLIT = 300,
    UNARY = 301
  };
#endif
/* Tokens.  */
#define SEMICOLON 258
#define COMMA 259
#define BLANKID 260
#define ASSIGN 261
#define STAR 262
#define DIV 263
#define MINUS 264
#define PLUS 265
#define MOD 266
#define EQ 267
#define GT 268
#define GE 269
#define LE 270
#define LT 271
#define NE 272
#define LBRACE 273
#define LPAR 274
#define LSQ 275
#define RBRACE 276
#define RPAR 277
#define RSQ 278
#define NOT 279
#define AND 280
#define OR 281
#define ELSE 282
#define IF 283
#define RETURN 284
#define FOR 285
#define FLOAT32 286
#define INT 287
#define VAR 288
#define BOOL 289
#define STRING 290
#define PARSEINT 291
#define PRINT 292
#define PACKAGE 293
#define FUNC 294
#define CMDARGS 295
#define RESERVED 296
#define ID 297
#define STRLIT 298
#define INTLIT 299
#define REALLIT 300
#define UNARY 301

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 22 "gocompiler.y"

    token_t token;
    ast_node_t *ast_node;

#line 154 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
