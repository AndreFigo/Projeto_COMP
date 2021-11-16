/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "gocompiler.y"

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

#line 91 "y.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
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

#line 240 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */



#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))

/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   362

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  47
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  18
/* YYNRULES -- Number of rules.  */
#define YYNRULES  73
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  164

#define YYUNDEFTOK  2
#define YYMAXUTOK   301


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    54,    54,    57,    61,    62,    63,    64,    67,    68,
      71,    76,    79,    82,    83,    84,    85,    88,    93,    99,
     103,   106,   109,   112,   117,   118,   121,   122,   123,   126,
     130,   137,   144,   150,   155,   161,   164,   166,   167,   169,
     172,   175,   184,   185,   187,   190,   193,   196,   199,   202,
     205,   206,   209,   212,   216,   219,   222,   225,   228,   231,
     235,   238,   241,   244,   247,   251,   254,   257,   261,   262,
     263,   264,   265,   266
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "SEMICOLON", "COMMA", "BLANKID",
  "ASSIGN", "STAR", "DIV", "MINUS", "PLUS", "MOD", "EQ", "GT", "GE", "LE",
  "LT", "NE", "LBRACE", "LPAR", "LSQ", "RBRACE", "RPAR", "RSQ", "NOT",
  "AND", "OR", "ELSE", "IF", "RETURN", "FOR", "FLOAT32", "INT", "VAR",
  "BOOL", "STRING", "PARSEINT", "PRINT", "PACKAGE", "FUNC", "CMDARGS",
  "RESERVED", "ID", "STRLIT", "INTLIT", "REALLIT", "UNARY", "$accept",
  "Program", "Declarations", "VarDeclaration", "VarSpec", "CommaId",
  "Type", "FuncDeclaration", "Parameters", "CommaIdType", "FuncBody",
  "VarsAndStatements", "Statement", "StatementSemicolon", "ParseArgs",
  "FuncInvocation", "CommaExpr", "Expr", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301
};
# endif

#define YYPACT_NINF (-51)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-45)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -37,   -30,    15,    20,   -51,   -25,   -16,   -15,   -25,    22,
      26,    -5,    39,   -51,    25,    52,    60,   -51,   -51,    62,
      29,    35,    30,   -51,   -51,    68,    39,   -51,   -51,   -51,
     -51,   -51,    35,    69,   -51,   -51,    70,   -14,    50,   -51,
     118,    75,   -51,    35,    94,   118,   144,   147,   147,   140,
      79,     3,    96,    80,   103,   -51,   -51,   -51,    70,   118,
     -51,   104,   108,    92,   147,   147,    99,   147,    97,   -51,
     -51,   -51,   206,   306,   144,   226,    86,   115,   147,    93,
     118,   -51,   118,   -51,   -51,   144,   144,   -51,   -51,   -51,
     100,   246,   -51,   147,   147,   147,   147,   147,   147,   147,
     147,   147,   147,   147,   144,   147,   147,   105,   144,   102,
     110,   266,   119,   306,   111,   -51,   186,   -51,   -51,   -51,
     -51,   -51,   -51,   -51,   -51,    49,    49,   -51,   168,   168,
     168,   168,   168,   168,   113,   345,   326,   -51,   131,   -51,
     -51,   -51,   117,   -51,   147,   132,   134,   -51,   121,   186,
     -51,   145,     1,   -51,   144,   146,   149,   159,   -51,   147,
     -51,   286,   148,   -51
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     1,     3,     0,     0,     2,     0,
       0,     0,    12,     8,     0,     0,     0,     4,     5,     0,
       0,     0,    20,     6,     7,     0,    12,    14,    13,    15,
      16,    10,     0,     0,     9,    11,    22,     0,     0,    19,
       0,     0,    18,     0,     0,     0,     0,     0,    36,     0,
       0,     0,     0,     0,     0,    38,    37,    17,    22,     0,
      27,     0,     0,     0,     0,     0,     0,     0,    70,    68,
      69,    71,     0,    35,     0,     0,     0,     0,     0,     0,
       0,    23,     0,    21,    25,     0,     0,    30,    66,    67,
       0,     0,    65,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    29,     0,    48,    51,    26,    24,    43,
      42,    73,    72,    62,    63,    61,    60,    64,    56,    55,
      59,    58,    54,    57,     0,    53,    52,    34,     0,    41,
      40,    39,     0,    49,     0,     0,    32,    33,     0,    51,
      47,     0,     0,    50,     0,     0,     0,     0,    46,     0,
      31,     0,     0,    45
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -51,   -51,   -51,     5,   156,   157,    -4,   179,   -51,   130,
     163,    -7,   -29,   -50,   -51,   -40,    56,   -17
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     8,    52,    13,    21,    31,    10,    33,    39,
      42,    53,    62,    63,    55,    71,   145,    72
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      56,     1,   155,    11,    40,    56,    56,    77,     6,    78,
       9,    54,     3,    15,     7,     4,    54,    27,    28,    56,
      29,    30,    79,     5,   107,    17,    12,    14,    36,    18,
      54,    73,    75,    41,    56,   119,   120,    12,    60,    58,
      56,   156,    56,    20,    22,    56,    56,    88,    89,    91,
      92,    54,    84,    54,   134,    23,    93,    94,   138,   111,
      97,   113,   116,    24,    56,    25,    27,    28,    56,    29,
      30,    26,    32,   117,    38,   118,   123,   124,   125,   126,
     127,   128,   129,   130,   131,   132,   133,   109,   135,   136,
      34,    37,    43,    40,   114,    64,    65,    59,    76,    80,
      90,    81,    64,    65,   157,    66,    82,    85,    64,    65,
      67,    86,    66,    87,    56,   115,    79,    67,    66,    44,
     112,    45,   121,    67,   139,   142,   137,   149,    68,   110,
      69,    70,   140,   143,   146,    68,    46,    69,    70,   -28,
     152,    68,   161,    69,    70,    61,    47,    48,    49,    64,
      65,     6,   147,   148,   150,    50,    64,    65,    74,    66,
      51,   151,    46,   154,    67,   -44,    66,    19,   158,   159,
     163,    67,    47,    48,    49,    93,    94,    95,    96,    97,
     160,    50,    68,    35,    69,    70,    51,    16,    83,    68,
     144,    69,    70,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,    57,   153,     0,     0,     0,     0,
       0,   105,   106,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,     0,     0,     0,     0,     0,
       0,   105,   106,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   108,     0,     0,     0,     0,     0,
       0,   105,   106,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,     0,     0,     0,     0,   122,     0,
       0,   105,   106,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,     0,     0,     0,     0,   141,     0,
       0,   105,   106,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,     0,     0,     0,     0,     0,   162,
       0,   105,   106,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,     0,     0,     0,     0,     0,     0,
       0,   105,   106,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,     0,     0,     0,     0,     0,     0,
       0,   105,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103
};

static const yytype_int16 yycheck[] =
{
      40,    38,     1,    19,    18,    45,    46,     4,    33,     6,
       5,    40,    42,     8,    39,     0,    45,    31,    32,    59,
      34,    35,    19,     3,    74,     3,    42,    42,    32,     3,
      59,    48,    49,    37,    74,    85,    86,    42,    45,    43,
      80,    40,    82,     4,    19,    85,    86,    64,    65,    66,
      67,    80,    59,    82,   104,     3,     7,     8,   108,    76,
      11,    78,    79,     3,   104,     3,    31,    32,   108,    34,
      35,    42,    42,    80,     4,    82,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,     1,   105,   106,
      22,    22,    42,    18,     1,     9,    10,     3,    19,     3,
       1,    21,     9,    10,   154,    19,     3,     3,     9,    10,
      24,     3,    19,    21,   154,    22,    19,    24,    19,     1,
       5,     3,    22,    24,    22,     6,    21,   144,    42,    43,
      44,    45,    22,    22,    21,    42,    18,    44,    45,    21,
      19,    42,   159,    44,    45,     1,    28,    29,    30,     9,
      10,    33,    21,    36,    22,    37,     9,    10,    18,    19,
      42,    27,    18,    18,    24,    21,    19,    11,    22,    20,
      22,    24,    28,    29,    30,     7,     8,     9,    10,    11,
      21,    37,    42,    26,    44,    45,    42,     8,    58,    42,
       4,    44,    45,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    41,   149,    -1,    -1,    -1,    -1,
      -1,    25,    26,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    -1,    -1,    -1,    -1,    -1,
      -1,    25,    26,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    -1,    -1,    -1,    -1,    -1,
      -1,    25,    26,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    -1,    -1,    -1,    -1,    22,    -1,
      -1,    25,    26,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    -1,    -1,    -1,    -1,    22,    -1,
      -1,    25,    26,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    -1,    -1,    -1,    -1,    -1,    23,
      -1,    25,    26,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    25,    26,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    25,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    38,    48,    42,     0,     3,    33,    39,    49,    50,
      54,    19,    42,    51,    42,    50,    54,     3,     3,    51,
       4,    52,    19,     3,     3,     3,    42,    31,    32,    34,
      35,    53,    42,    55,    22,    52,    53,    22,     4,    56,
      18,    53,    57,    42,     1,     3,    18,    28,    29,    30,
      37,    42,    50,    58,    59,    61,    62,    57,    53,     3,
      58,     1,    59,    60,     9,    10,    19,    24,    42,    44,
      45,    62,    64,    64,    18,    64,    19,     4,     6,    19,
       3,    21,     3,    56,    58,     3,     3,    21,    64,    64,
       1,    64,    64,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    25,    26,    60,    18,     1,
      43,    64,     5,    64,     1,    22,    64,    58,    58,    60,
      60,    22,    22,    64,    64,    64,    64,    64,    64,    64,
      64,    64,    64,    64,    60,    64,    64,    21,    60,    22,
      22,    22,     6,    22,     4,    63,    21,    21,    36,    64,
      22,    27,    19,    63,    18,     1,    40,    60,    22,    20,
      21,    64,    23,    22
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    47,    48,    48,    49,    49,    49,    49,    50,    50,
      51,    52,    52,    53,    53,    53,    53,    54,    54,    55,
      55,    56,    56,    57,    58,    58,    58,    58,    58,    59,
      59,    59,    59,    59,    59,    59,    59,    59,    59,    59,
      59,    59,    60,    60,    60,    61,    61,    62,    62,    62,
      63,    63,    64,    64,    64,    64,    64,    64,    64,    64,
      64,    64,    64,    64,    64,    64,    64,    64,    64,    64,
      64,    64,    64,    64
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     4,     3,     2,     2,     3,     3,     2,     5,
       3,     3,     0,     1,     1,     1,     1,     7,     6,     3,
       0,     4,     0,     3,     3,     3,     3,     2,     0,     3,
       3,     9,     5,     5,     4,     2,     1,     1,     1,     4,
       4,     4,     3,     3,     0,    11,     8,     5,     3,     4,
       3,     0,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     2,     2,     2,     1,     1,
       1,     1,     3,     3
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2:
#line 54 "gocompiler.y"
                                                                                                {(yyval.ast_node)=program=create_node("Program", null_token);
                                                                                                    add_children((yyval.ast_node),1,(yyvsp[0].ast_node));
                                                                                                }
#line 1564 "y.tab.c"
    break;

  case 3:
#line 57 "gocompiler.y"
                                                                                                {(yyval.ast_node)=program=create_node("Program", null_token);}
#line 1570 "y.tab.c"
    break;

  case 4:
#line 61 "gocompiler.y"
                                                                                                {(yyval.ast_node)=(yyvsp[-1].ast_node);}
#line 1576 "y.tab.c"
    break;

  case 5:
#line 62 "gocompiler.y"
                                                                                                {(yyval.ast_node)=(yyvsp[-1].ast_node);}
#line 1582 "y.tab.c"
    break;

  case 6:
#line 63 "gocompiler.y"
                                                                                                {add_siblings((yyvsp[-2].ast_node),1,(yyvsp[-1].ast_node));}
#line 1588 "y.tab.c"
    break;

  case 7:
#line 64 "gocompiler.y"
                                                                                                {add_siblings((yyvsp[-2].ast_node),1,(yyvsp[-1].ast_node));}
#line 1594 "y.tab.c"
    break;

  case 8:
#line 67 "gocompiler.y"
                                                                                                {(yyval.ast_node)=split_vardecl((yyvsp[0].ast_node), null_token); }
#line 1600 "y.tab.c"
    break;

  case 9:
#line 68 "gocompiler.y"
                                                                                                {(yyval.ast_node)=split_vardecl((yyvsp[-2].ast_node), null_token);}
#line 1606 "y.tab.c"
    break;

  case 10:
#line 71 "gocompiler.y"
                                                                                                {(yyval.ast_node) = create_node("Id", (yyvsp[-2].token));
                                                                                                    add_siblings((yyvsp[0].ast_node),2, (yyval.ast_node), (yyvsp[-1].ast_node)); (yyval.ast_node)=(yyvsp[0].ast_node);
                                                                                                }
#line 1614 "y.tab.c"
    break;

  case 11:
#line 76 "gocompiler.y"
                                                                                                {(yyval.ast_node)= create_node("Id", (yyvsp[-1].token));
                                                                                                    add_siblings((yyval.ast_node),1,(yyvsp[0].ast_node));
                                                                                                }
#line 1622 "y.tab.c"
    break;

  case 12:
#line 79 "gocompiler.y"
                                                                                                {(yyval.ast_node)=NULL;}
#line 1628 "y.tab.c"
    break;

  case 13:
#line 82 "gocompiler.y"
                                                                                                {(yyval.ast_node)= create_node("Int", (yyvsp[0].token)); }
#line 1634 "y.tab.c"
    break;

  case 14:
#line 83 "gocompiler.y"
                                                                                                {(yyval.ast_node)= create_node("Float32", (yyvsp[0].token));}
#line 1640 "y.tab.c"
    break;

  case 15:
#line 84 "gocompiler.y"
                                                                                                {(yyval.ast_node)= create_node("Bool", (yyvsp[0].token));}
#line 1646 "y.tab.c"
    break;

  case 16:
#line 85 "gocompiler.y"
                                                                                                {(yyval.ast_node)= create_node("String", (yyvsp[0].token));}
#line 1652 "y.tab.c"
    break;

  case 17:
#line 88 "gocompiler.y"
                                                                                                {(yyval.ast_node)= create_node("FuncDecl", null_token);
                                                                                                    aux_node= create_node("FuncHeader", null_token); 
                                                                                                    
                                                                                                    add_children(aux_node, 3, create_node("Id", (yyvsp[-5].token)),(yyvsp[-1].ast_node),(yyvsp[-3].ast_node));
                                                                                                    add_children((yyval.ast_node),2,aux_node, (yyvsp[0].ast_node)); }
#line 1662 "y.tab.c"
    break;

  case 18:
#line 93 "gocompiler.y"
                                                                                                {(yyval.ast_node)= create_node("FuncDecl", null_token);
                                                                                                    aux_node= create_node("FuncHeader", null_token); 
                                                                                                    add_children(aux_node, 2,  create_node("Id", (yyvsp[-4].token)),(yyvsp[-2].ast_node));
                                                                                                    add_children((yyval.ast_node),2,aux_node, (yyvsp[0].ast_node)); }
#line 1671 "y.tab.c"
    break;

  case 19:
#line 99 "gocompiler.y"
                                                                                                {(yyval.ast_node)=create_node("FuncParams", null_token);
                                                                                                    aux_node = create_node("ParamDecl", null_token);
                                                                                                    add_children(aux_node,2,(yyvsp[-1].ast_node), create_node("Id", (yyvsp[-2].token)));
                                                                                                    add_children((yyval.ast_node),2, aux_node, (yyvsp[0].ast_node));}
#line 1680 "y.tab.c"
    break;

  case 20:
#line 103 "gocompiler.y"
                                                                                                {(yyval.ast_node)=create_node("FuncParams", null_token);}
#line 1686 "y.tab.c"
    break;

  case 21:
#line 106 "gocompiler.y"
                                                                                                {(yyval.ast_node) = create_node("ParamDecl", null_token);
                                                                                                    add_children((yyval.ast_node),2, (yyvsp[-1].ast_node), create_node("Id", (yyvsp[-2].token)));
                                                                                                    add_siblings((yyval.ast_node), 1, (yyvsp[0].ast_node));}
#line 1694 "y.tab.c"
    break;

  case 22:
#line 109 "gocompiler.y"
                                                                                                {(yyval.ast_node)=NULL;}
#line 1700 "y.tab.c"
    break;

  case 23:
#line 112 "gocompiler.y"
                                                                                                {(yyval.ast_node) = create_node("FuncBody", null_token);
                                                                                                    add_children((yyval.ast_node), 1, (yyvsp[-1].ast_node));
                                                                                                }
#line 1708 "y.tab.c"
    break;

  case 24:
#line 117 "gocompiler.y"
                                                                                                {add_siblings((yyvsp[-2].ast_node), 1, (yyvsp[0].ast_node));(yyval.ast_node)=(yyvsp[-2].ast_node);}
#line 1714 "y.tab.c"
    break;

  case 25:
#line 118 "gocompiler.y"
                                                                                                {syntax_error = 1;   printf("stat1\n");  (yyval.ast_node)=create_node("Error",null_token); 
                                                                                                    add_siblings((yyval.ast_node), 1, (yyvsp[0].ast_node)); }
#line 1721 "y.tab.c"
    break;

  case 26:
#line 121 "gocompiler.y"
                                                                                                {add_siblings((yyvsp[-2].ast_node), 1, (yyvsp[0].ast_node)); (yyval.ast_node)=(yyvsp[-2].ast_node);}
#line 1727 "y.tab.c"
    break;

  case 27:
#line 122 "gocompiler.y"
                                                                                                {(yyval.ast_node)=(yyvsp[0].ast_node);/*!!!!!!!!!!!! ATENÇAO AQUI*/}
#line 1733 "y.tab.c"
    break;

  case 28:
#line 123 "gocompiler.y"
                                                                                                {(yyval.ast_node)=NULL;}
#line 1739 "y.tab.c"
    break;

  case 29:
#line 126 "gocompiler.y"
                                                                                                {(yyval.ast_node)=create_node("Assign", null_token);
                                                                                                    add_children((yyval.ast_node), 2, create_node("Id",(yyvsp[-2].token)), (yyvsp[0].ast_node));
                                                                                                }
#line 1747 "y.tab.c"
    break;

  case 30:
#line 130 "gocompiler.y"
                                                                                                {   if ((yyvsp[-1].ast_node)->nSibling == NULL) (yyval.ast_node)=(yyvsp[-1].ast_node);
                                                                                                    else{
                                                                                                        (yyval.ast_node) = create_node("Block", null_token);
                                                                                                        add_children((yyval.ast_node), 1, (yyvsp[-1].ast_node));
                                                                                                    }
                                                                                                }
#line 1758 "y.tab.c"
    break;

  case 31:
#line 137 "gocompiler.y"
                                                                                                                {(yyval.ast_node)=create_node("If", null_token);
                                                                                                                    aux_node = create_node("Block", null_token);
                                                                                                                    add_children(aux_node, 1, (yyvsp[-5].ast_node));
                                                                                                                    aux_node2 = create_node("Block", null_token);
                                                                                                                    add_children(aux_node2, 1, (yyvsp[-1].ast_node));
                                                                                                                    add_children((yyval.ast_node), 3, (yyvsp[-7].ast_node), aux_node, aux_node2);
                                                                                                                }
#line 1770 "y.tab.c"
    break;

  case 32:
#line 144 "gocompiler.y"
                                                                                                {(yyval.ast_node)=create_node("If", null_token);
                                                                                                    aux_node = create_node("Block", null_token);
                                                                                                    add_children(aux_node, 1, (yyvsp[-1].ast_node));
                                                                                                    aux_node2 = create_node("Block", null_token);
                                                                                                    add_children((yyval.ast_node), 3, (yyvsp[-3].ast_node), aux_node, aux_node2);}
#line 1780 "y.tab.c"
    break;

  case 33:
#line 150 "gocompiler.y"
                                                                                                {(yyval.ast_node)=create_node("For", null_token);
                                                                                                    aux_node = create_node("Block", null_token);
                                                                                                    add_children(aux_node, 1, (yyvsp[-1].ast_node));
                                                                                                    add_children((yyval.ast_node), 2, (yyvsp[-3].ast_node), aux_node);
                                                                                                }
#line 1790 "y.tab.c"
    break;

  case 34:
#line 155 "gocompiler.y"
                                                                                                {(yyval.ast_node)=create_node("For", null_token);
                                                                                                    aux_node = create_node("Block", null_token);
                                                                                                    add_children(aux_node, 1, (yyvsp[-1].ast_node));
                                                                                                    add_children((yyval.ast_node), 1, aux_node);
                                                                                                }
#line 1800 "y.tab.c"
    break;

  case 35:
#line 161 "gocompiler.y"
                                                                                                {(yyval.ast_node) = create_node("Return", null_token);
                                                                                                    add_children((yyval.ast_node), 1, (yyvsp[0].ast_node));
                                                                                                }
#line 1808 "y.tab.c"
    break;

  case 36:
#line 164 "gocompiler.y"
                                                                                                {(yyval.ast_node) =  create_node("Return", null_token);}
#line 1814 "y.tab.c"
    break;

  case 37:
#line 166 "gocompiler.y"
                                                                                                {(yyval.ast_node)=(yyvsp[0].ast_node);}
#line 1820 "y.tab.c"
    break;

  case 38:
#line 167 "gocompiler.y"
                                                                                                {(yyval.ast_node)=(yyvsp[0].ast_node);}
#line 1826 "y.tab.c"
    break;

  case 39:
#line 169 "gocompiler.y"
                                                                                                {(yyval.ast_node) = create_node("Print", null_token);
                                                                                                    add_children((yyval.ast_node), 1, (yyvsp[-1].ast_node));
                                                                                                }
#line 1834 "y.tab.c"
    break;

  case 40:
#line 172 "gocompiler.y"
                                                                                                {(yyval.ast_node) = create_node("Print", null_token);
                                                                                                    add_children((yyval.ast_node), 1, create_node("StrLit", (yyvsp[-1].token)));
                                                                                                }
#line 1842 "y.tab.c"
    break;

  case 41:
#line 175 "gocompiler.y"
                                                                                               {(yyval.ast_node) = create_node("Print", null_token);
                                                                                                    add_children((yyval.ast_node), 1, create_node("Error", null_token));
                                                                                                    syntax_error = 1;
                                                                                                    printf("print\n");
                                                                                                }
#line 1852 "y.tab.c"
    break;

  case 42:
#line 184 "gocompiler.y"
                                                                                                {add_siblings((yyvsp[-2].ast_node), 1, (yyvsp[0].ast_node)); (yyval.ast_node)=(yyvsp[-2].ast_node);}
#line 1858 "y.tab.c"
    break;

  case 43:
#line 185 "gocompiler.y"
                                                                                                {syntax_error = 1;   printf("stat2\n");  (yyval.ast_node)=create_node("Error",null_token); 
                                                                                                    add_siblings((yyval.ast_node), 1, (yyvsp[0].ast_node)); }
#line 1865 "y.tab.c"
    break;

  case 44:
#line 187 "gocompiler.y"
                                                                                                {(yyval.ast_node)=NULL;}
#line 1871 "y.tab.c"
    break;

  case 45:
#line 190 "gocompiler.y"
                                                                                                {(yyval.ast_node)=create_node("ParseArgs", null_token);
                                                                                                    add_children((yyval.ast_node), 2, create_node("Id", (yyvsp[-10].token)),(yyvsp[-2].ast_node));
                                                                                                }
#line 1879 "y.tab.c"
    break;

  case 46:
#line 193 "gocompiler.y"
                                                                                                {syntax_error = 1;  printf("ll\n");  (yyval.ast_node) = create_node("Error",null_token);}
#line 1885 "y.tab.c"
    break;

  case 47:
#line 196 "gocompiler.y"
                                                                                                {(yyval.ast_node) = create_node("Call", null_token);
                                                                                                    add_children((yyval.ast_node), 3, create_node("Id", (yyvsp[-4].token)), (yyvsp[-2].ast_node), (yyvsp[-1].ast_node));
                                                                                                }
#line 1893 "y.tab.c"
    break;

  case 48:
#line 199 "gocompiler.y"
                                                                                                {(yyval.ast_node) = create_node("Call", null_token);
                                                                                                    add_children((yyval.ast_node), 1, create_node("Id", (yyvsp[-2].token)));
                                                                                                }
#line 1901 "y.tab.c"
    break;

  case 49:
#line 202 "gocompiler.y"
                                                                                                {syntax_error = 1;   printf("ii\n");  (yyval.ast_node) = create_node("Error",null_token);}
#line 1907 "y.tab.c"
    break;

  case 50:
#line 205 "gocompiler.y"
                                                                                                {add_siblings((yyvsp[-1].ast_node),1,(yyvsp[0].ast_node)); (yyval.ast_node)=(yyvsp[-1].ast_node);}
#line 1913 "y.tab.c"
    break;

  case 51:
#line 206 "gocompiler.y"
                                                                                                {(yyval.ast_node)=NULL;}
#line 1919 "y.tab.c"
    break;

  case 52:
#line 209 "gocompiler.y"
                                                                                                {(yyval.ast_node) = create_node("Or", null_token);
                                                                                                    add_children((yyval.ast_node), 2, (yyvsp[-2].ast_node), (yyvsp[0].ast_node));
                                                                                                }
#line 1927 "y.tab.c"
    break;

  case 53:
#line 212 "gocompiler.y"
                                                                                                {(yyval.ast_node) = create_node("And", null_token);
                                                                                                    add_children((yyval.ast_node), 2, (yyvsp[-2].ast_node), (yyvsp[0].ast_node));
                                                                                                }
#line 1935 "y.tab.c"
    break;

  case 54:
#line 216 "gocompiler.y"
                                                                                                {(yyval.ast_node) = create_node("Lt", null_token);
                                                                                                    add_children((yyval.ast_node), 2, (yyvsp[-2].ast_node), (yyvsp[0].ast_node));
                                                                                                }
#line 1943 "y.tab.c"
    break;

  case 55:
#line 219 "gocompiler.y"
                                                                                                {(yyval.ast_node) = create_node("Gt", null_token);
                                                                                                    add_children((yyval.ast_node), 2, (yyvsp[-2].ast_node), (yyvsp[0].ast_node));
                                                                                                }
#line 1951 "y.tab.c"
    break;

  case 56:
#line 222 "gocompiler.y"
                                                                                                {(yyval.ast_node) = create_node("Eq", null_token);
                                                                                                    add_children((yyval.ast_node), 2, (yyvsp[-2].ast_node), (yyvsp[0].ast_node));
                                                                                                }
#line 1959 "y.tab.c"
    break;

  case 57:
#line 225 "gocompiler.y"
                                                                                                {(yyval.ast_node) = create_node("Ne", null_token);
                                                                                                    add_children((yyval.ast_node), 2, (yyvsp[-2].ast_node), (yyvsp[0].ast_node));
                                                                                                }
#line 1967 "y.tab.c"
    break;

  case 58:
#line 228 "gocompiler.y"
                                                                                                {(yyval.ast_node) = create_node("Le", null_token);
                                                                                                    add_children((yyval.ast_node), 2, (yyvsp[-2].ast_node), (yyvsp[0].ast_node));
                                                                                                }
#line 1975 "y.tab.c"
    break;

  case 59:
#line 231 "gocompiler.y"
                                                                                                {(yyval.ast_node) = create_node("Ge", null_token);
                                                                                                    add_children((yyval.ast_node), 2, (yyvsp[-2].ast_node), (yyvsp[0].ast_node));
                                                                                                }
#line 1983 "y.tab.c"
    break;

  case 60:
#line 235 "gocompiler.y"
                                                                                                {(yyval.ast_node) = create_node("Add", null_token);
                                                                                                    add_children((yyval.ast_node), 2, (yyvsp[-2].ast_node), (yyvsp[0].ast_node));
                                                                                                }
#line 1991 "y.tab.c"
    break;

  case 61:
#line 238 "gocompiler.y"
                                                                                                {(yyval.ast_node) = create_node("Sub", null_token);
                                                                                                    add_children((yyval.ast_node), 2, (yyvsp[-2].ast_node), (yyvsp[0].ast_node));
                                                                                                }
#line 1999 "y.tab.c"
    break;

  case 62:
#line 241 "gocompiler.y"
                                                                                                {(yyval.ast_node) = create_node("Mul", null_token);
                                                                                                    add_children((yyval.ast_node), 2, (yyvsp[-2].ast_node), (yyvsp[0].ast_node));
                                                                                                }
#line 2007 "y.tab.c"
    break;

  case 63:
#line 244 "gocompiler.y"
                                                                                                {(yyval.ast_node) = create_node("Div", null_token);
                                                                                                    add_children((yyval.ast_node), 2, (yyvsp[-2].ast_node), (yyvsp[0].ast_node));
                                                                                                }
#line 2015 "y.tab.c"
    break;

  case 64:
#line 247 "gocompiler.y"
                                                                                                {(yyval.ast_node) = create_node("Mod", null_token);
                                                                                                    add_children((yyval.ast_node), 2, (yyvsp[-2].ast_node), (yyvsp[0].ast_node));
                                                                                                }
#line 2023 "y.tab.c"
    break;

  case 65:
#line 251 "gocompiler.y"
                                                                                                {(yyval.ast_node) = create_node("Not", null_token);
                                                                                                    add_children((yyval.ast_node), 1, (yyvsp[0].ast_node));
                                                                                                }
#line 2031 "y.tab.c"
    break;

  case 66:
#line 254 "gocompiler.y"
                                                                                                {(yyval.ast_node) = create_node("Minus", null_token);
                                                                                                    add_children((yyval.ast_node), 1, (yyvsp[0].ast_node));
                                                                                                }
#line 2039 "y.tab.c"
    break;

  case 67:
#line 257 "gocompiler.y"
                                                                                                {(yyval.ast_node) = create_node("Plus", null_token);
                                                                                                    add_children((yyval.ast_node), 1, (yyvsp[0].ast_node));
                                                                                                }
#line 2047 "y.tab.c"
    break;

  case 68:
#line 261 "gocompiler.y"
                                                                                                {(yyval.ast_node) = create_node("IntLit", (yyvsp[0].token));}
#line 2053 "y.tab.c"
    break;

  case 69:
#line 262 "gocompiler.y"
                                                                                                {(yyval.ast_node)= create_node("RealLit", (yyvsp[0].token));}
#line 2059 "y.tab.c"
    break;

  case 70:
#line 263 "gocompiler.y"
                                                                                                {(yyval.ast_node) = create_node("Id", (yyvsp[0].token));}
#line 2065 "y.tab.c"
    break;

  case 71:
#line 264 "gocompiler.y"
                                                                                                {(yyval.ast_node)=(yyvsp[0].ast_node);}
#line 2071 "y.tab.c"
    break;

  case 72:
#line 265 "gocompiler.y"
                                                                                                {(yyval.ast_node)=(yyvsp[-1].ast_node);}
#line 2077 "y.tab.c"
    break;

  case 73:
#line 266 "gocompiler.y"
                                                                                                {syntax_error = 1; printf("p\n"); (yyval.ast_node) = create_node("Error",null_token);}
#line 2083 "y.tab.c"
    break;


#line 2087 "y.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[+*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 269 "gocompiler.y"


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
