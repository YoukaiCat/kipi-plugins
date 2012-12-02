/* A Bison parser, made by GNU Bison 2.6.5.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2012 Free Software Foundation, Inc.
   
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

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.6.5"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
/* Line 360 of yacc.c  */
#line 26 "ptoparser/panoParser.y"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "tparserdebug.h"
#include "tparserprivate.h"

int yylex (void);
void yyerror (char const *);
/*  Keeps track of the current type of input line in the file */
int currentLine = -1;

pt_script script;

/* defining it gives better error messages. It might be an overkill */
#define YYERROR_VERBOSE 1 

static pt_script_image *image = NULL;
static pt_script_ctrl_point *ctrlPoint = NULL;
static pt_script_mask *mask = NULL;
static int nbProjParms = 0;
static double* projParms = NULL;
static int nbCommentLine = 0;
static char** commentLines = NULL;

/* copy a string while allocating and checking for memory */
static void ParserStringCopy(char **dest, const char *from)
{
    if (*dest)
        free(*dest);
    *dest = strdup(from);
    if (*dest == NULL)
        yyerror("Not enough memory");
}



/* Line 360 of yacc.c  */
#line 109 "/tmp/digikam-sc/build/extra/kipi-plugins/panorama/panoParser.c"

# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "panoParser.h".  */
#ifndef YY_YY_TMP_DIGIKAM_SC_BUILD_EXTRA_KIPI_PLUGINS_PANORAMA_PANOPARSER_H_INCLUDED
# define YY_YY_TMP_DIGIKAM_SC_BUILD_EXTRA_KIPI_PLUGINS_PANORAMA_PANOPARSER_H_INCLUDED
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     PT_TOKEN_NUMBER_INT = 258,
     PT_TOKEN_NUMBER_FLOAT = 259,
     PT_TOKEN_STRING = 260,
     PT_TOKEN_HUGIN_KEYWORD = 261,
     PT_TOKEN_KEYWORD = 262,
     PT_TOKEN_KEYWORD_MULTICHAR = 263,
     PT_TOKEN_KEYWORD_CROPPING = 264,
     PT_TOKEN_COMMENT = 265,
     PT_TOKEN_EOL = 266,
     PT_TOKEN_SEP = 267,
     PT_TOKEN_INPUT_LINE = 268,
     PT_TOKEN_PANO_LINE = 269,
     PT_TOKEN_CONTROL_PT_LINE = 270,
     PT_TOKEN_OPTIMIZE_OPT_LINE = 271,
     PT_TOKEN_OPTIMIZE_VARS_LINE = 272,
     PT_TOKEN_KEYWORD_MASK = 273,
     PT_TOKEN_KEYWORD_PROJPARAMS = 274,
     PT_TOKEN_COMMA = 275,
     PT_TOKEN_REFERENCE = 276,
     PT_TOKEN_MASK_PT_LINE = 277,
     PT_TOKEN_ERROR = 278,
     PT_TOKEN_EOF = 279
   };
#endif


#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 376 of yacc.c  */
#line 69 "ptoparser/panoParser.y"

    int     iVal;
    double  fVal;
    char    strVal[PT_TOKEN_MAX_LEN + 1];
    char    cVal;


/* Line 376 of yacc.c  */
#line 184 "/tmp/digikam-sc/build/extra/kipi-plugins/panorama/panoParser.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */

#endif /* !YY_YY_TMP_DIGIKAM_SC_BUILD_EXTRA_KIPI_PLUGINS_PANORAMA_PANOPARSER_H_INCLUDED  */

/* Copy the second part of user declarations.  */

/* Line 379 of yacc.c  */
#line 212 "/tmp/digikam-sc/build/extra/kipi-plugins/panorama/panoParser.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(N) (N)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   91

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  25
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  39
/* YYNRULES -- Number of rules.  */
#define YYNRULES  67
/* YYNRULES -- Number of states.  */
#define YYNSTATES  115

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   279

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
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
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     6,     9,    11,    14,    15,    18,    21,
      24,    27,    30,    33,    36,    39,    40,    45,    46,    51,
      52,    57,    58,    63,    65,    66,    71,    72,    77,    79,
      81,    85,    88,    91,    93,    97,    99,   103,   105,   107,
     109,   111,   113,   115,   117,   121,   123,   127,   130,   133,
     135,   139,   143,   152,   156,   160,   163,   166,   169,   172,
     175,   178,   180,   182,   186,   188,   190,   192
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      26,     0,    -1,    27,    29,    -1,    27,    28,    -1,    28,
      -1,    29,    31,    -1,    -1,    29,    30,    -1,    10,    44,
      -1,    32,    44,    -1,    34,    44,    -1,    36,    44,    -1,
      38,    44,    -1,    40,    44,    -1,    42,    44,    -1,    -1,
      13,    12,    33,    47,    -1,    -1,    14,    12,    35,    48,
      -1,    -1,    16,    12,    37,    48,    -1,    -1,    17,    12,
      39,    45,    -1,    17,    -1,    -1,    15,    12,    41,    51,
      -1,    -1,    22,    12,    43,    52,    -1,    11,    -1,    46,
      -1,    45,    12,    46,    -1,     8,    62,    -1,     7,    62,
      -1,    49,    -1,    47,    12,    49,    -1,    50,    -1,    48,
      12,    50,    -1,    56,    -1,    57,    -1,    58,    -1,    56,
      -1,    58,    -1,    59,    -1,    58,    -1,    51,    12,    58,
      -1,    53,    -1,    52,    12,    53,    -1,     7,    62,    -1,
      18,    54,    -1,    55,    -1,    54,    20,    55,    -1,    62,
      20,    62,    -1,     9,    62,    20,    62,    20,    62,    20,
      62,    -1,     8,    21,    62,    -1,     7,    21,    62,    -1,
       7,     5,    -1,    19,    60,    -1,     7,    62,    -1,     7,
      61,    -1,     8,     5,    -1,     8,    63,    -1,     7,    -1,
      63,    -1,    60,    20,    63,    -1,     4,    -1,     3,    -1,
       4,    -1,     3,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   110,   110,   118,   119,   121,   127,   128,   130,   144,
     166,   171,   176,   190,   204,   221,   220,   255,   254,   261,
     260,   269,   268,   272,   275,   274,   288,   287,   317,   329,
     330,   332,   345,   363,   364,   366,   367,   371,   372,   373,
     375,   376,   377,   379,   380,   382,   386,   394,   410,   417,
     418,   420,   435,   463,   548,   593,   640,   648,   782,   877,
     890,   991,  1010,  1017,  1025,  1027,  1029,  1030
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "PT_TOKEN_NUMBER_INT",
  "PT_TOKEN_NUMBER_FLOAT", "PT_TOKEN_STRING", "PT_TOKEN_HUGIN_KEYWORD",
  "PT_TOKEN_KEYWORD", "PT_TOKEN_KEYWORD_MULTICHAR",
  "PT_TOKEN_KEYWORD_CROPPING", "PT_TOKEN_COMMENT", "PT_TOKEN_EOL",
  "PT_TOKEN_SEP", "PT_TOKEN_INPUT_LINE", "PT_TOKEN_PANO_LINE",
  "PT_TOKEN_CONTROL_PT_LINE", "PT_TOKEN_OPTIMIZE_OPT_LINE",
  "PT_TOKEN_OPTIMIZE_VARS_LINE", "PT_TOKEN_KEYWORD_MASK",
  "PT_TOKEN_KEYWORD_PROJPARAMS", "PT_TOKEN_COMMA", "PT_TOKEN_REFERENCE",
  "PT_TOKEN_MASK_PT_LINE", "PT_TOKEN_ERROR", "PT_TOKEN_EOF", "$accept",
  "input", "lines", "line", "commentlines", "commentline", "realline",
  "inputline", "$@1", "panoline", "$@2", "optimizeOptsline", "$@3",
  "optimizeVarsline", "$@4", "ctrlPtsLine", "$@5", "maskPtsLine", "$@6",
  "eoln", "varsOpt", "varOpt", "varsinput", "vars", "varinput", "var",
  "varsparms", "varsparmsmask", "varparmmask", "mask", "maskpoint",
  "varcropping", "varreference", "varparameter", "varonly", "projparams",
  "float", "int", "intorfloat", YY_NULL
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    25,    26,    27,    27,    28,    29,    29,    30,    31,
      31,    31,    31,    31,    31,    33,    32,    35,    34,    37,
      36,    39,    38,    38,    41,    40,    43,    42,    44,    45,
      45,    46,    46,    47,    47,    48,    48,    49,    49,    49,
      50,    50,    50,    51,    51,    52,    52,    53,    53,    54,
      54,    55,    56,    57,    57,    58,    58,    58,    58,    58,
      58,    59,    60,    60,    61,    62,    63,    63
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     2,     1,     2,     0,     2,     2,     2,
       2,     2,     2,     2,     2,     0,     4,     0,     4,     0,
       4,     0,     4,     1,     0,     4,     0,     4,     1,     1,
       3,     2,     2,     1,     3,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     3,     1,     3,     2,     2,     1,
       3,     3,     8,     3,     3,     2,     2,     2,     2,     2,
       2,     1,     1,     3,     1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       6,     0,     6,     4,     0,     1,     3,     2,     0,     0,
       0,     0,     0,    23,     0,     7,     5,     0,     0,     0,
       0,     0,     0,    28,     8,    15,    17,    24,    19,    21,
      26,     9,    10,    11,    12,    13,    14,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    16,    33,    37,
      38,    39,    61,     0,    18,    35,    40,    41,    42,     0,
      25,    43,    20,     0,     0,    22,    29,     0,     0,    27,
      45,    65,    64,    55,     0,    58,    57,    67,    66,    59,
       0,    60,     0,    56,    62,     0,     0,     0,    32,    31,
       0,    47,    48,    49,     0,     0,    54,    53,     0,     0,
      34,    36,    44,    30,     0,     0,    46,     0,    63,    50,
      51,     0,     0,     0,    52
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     1,     2,     3,     4,    15,    16,    17,    37,    18,
      38,    19,    40,    20,    41,    21,    39,    22,    42,    24,
      65,    66,    47,    54,    48,    55,    60,    69,    70,    92,
      93,    56,    50,    57,    58,    83,    75,    76,    81
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -46
static const yytype_int8 yypact[] =
{
     -46,    25,   -46,   -46,    23,   -46,   -46,    23,    -6,    22,
      29,    38,    49,    50,    51,   -46,   -46,    -6,    -6,    -6,
      -6,    -6,    -6,   -46,   -46,   -46,   -46,   -46,   -46,   -46,
     -46,   -46,   -46,   -46,   -46,   -46,   -46,     7,    35,    13,
      35,     5,    10,     3,     6,    61,    27,    55,   -46,   -46,
     -46,   -46,    43,    53,    63,   -46,   -46,   -46,   -46,    43,
      64,   -46,    63,    61,    61,    65,   -46,    61,    61,    66,
     -46,   -46,   -46,   -46,    61,   -46,   -46,   -46,   -46,   -46,
      61,   -46,    45,    59,   -46,     7,    35,    13,   -46,   -46,
       5,   -46,    60,   -46,    62,    10,   -46,   -46,    61,    27,
     -46,   -46,   -46,   -46,    61,    61,   -46,    67,   -46,   -46,
     -46,    61,    68,    61,   -46
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -46,   -46,   -46,    79,    81,   -46,   -46,   -46,   -46,   -46,
     -46,   -46,   -46,   -46,   -46,   -46,   -46,   -46,   -46,    52,
     -46,    -5,   -46,    44,     1,     4,   -46,   -46,    -4,   -46,
     -15,   -33,   -46,   -36,   -46,   -46,   -46,   -45,   -44
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      82,    51,    84,    61,    49,    23,    71,    72,    73,    77,
      78,    79,    63,    64,    43,    44,    45,    67,    88,    89,
      59,    53,    91,    94,    74,     5,    46,    80,    68,    96,
      77,    78,    46,     8,    25,    97,     9,    10,    11,    12,
      13,    26,    52,    53,    45,    14,    71,    72,    73,    51,
      27,   102,    49,   107,    46,   108,    77,    78,    79,    94,
     110,    28,    29,    30,    71,    98,   112,    85,   114,    31,
      32,    33,    34,    35,    36,    86,    87,    90,    95,    99,
     104,     6,   105,     7,    62,   103,   100,   111,   113,   109,
     101,   106
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-46)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_uint8 yycheck[] =
{
      45,    37,    46,    39,    37,    11,     3,     4,     5,     3,
       4,     5,     7,     8,     7,     8,     9,     7,    63,    64,
       7,     8,    67,    68,    21,     0,    19,    21,    18,    74,
       3,     4,    19,    10,    12,    80,    13,    14,    15,    16,
      17,    12,     7,     8,     9,    22,     3,     4,     5,    85,
      12,    87,    85,    98,    19,    99,     3,     4,     5,   104,
     105,    12,    12,    12,     3,    20,   111,    12,   113,    17,
      18,    19,    20,    21,    22,    12,    12,    12,    12,    20,
      20,     2,    20,     2,    40,    90,    85,    20,    20,   104,
      86,    95
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    26,    27,    28,    29,     0,    28,    29,    10,    13,
      14,    15,    16,    17,    22,    30,    31,    32,    34,    36,
      38,    40,    42,    11,    44,    12,    12,    12,    12,    12,
      12,    44,    44,    44,    44,    44,    44,    33,    35,    41,
      37,    39,    43,     7,     8,     9,    19,    47,    49,    56,
      57,    58,     7,     8,    48,    50,    56,    58,    59,     7,
      51,    58,    48,     7,     8,    45,    46,     7,    18,    52,
      53,     3,     4,     5,    21,    61,    62,     3,     4,     5,
      21,    63,    62,    60,    63,    12,    12,    12,    62,    62,
      12,    62,    54,    55,    62,    12,    62,    62,    20,    20,
      49,    50,    58,    46,    20,    20,    53,    62,    63,    55,
      62,    20,    62,    20,    62
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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
      YYERROR;							\
    }								\
while (YYID (0))

/* Error token number */
#define YYTERROR	1
#define YYERRCODE	256


/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */
#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

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
#ifndef	YYINITDEPTH
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
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
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
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
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
	    /* Fall through.  */
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

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
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
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULL, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  YYSIZE_T yysize1;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULL;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
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
      int yyn = yypact[*yyssp];
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
                yysize1 = yysize + yytnamerr (YY_NULL, yytname[yyx]);
                if (! (yysize <= yysize1
                       && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                  return 2;
                yysize = yysize1;
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  yysize1 = yysize + yystrlen (yyformat);
  if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
    return 2;
  yysize = yysize1;

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
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}




/* The lookahead symbol.  */
int yychar;


#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval YY_INITIAL_VALUE(yyval_default);

/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

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
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
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
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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
      yychar = YYLEX;
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

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
/* Line 1778 of yacc.c  */
#line 111 "ptoparser/panoParser.y"
    {
        script.iEndingCommentsCount = nbCommentLine;
        script.endingComments = commentLines;
        nbCommentLine = 0;
        commentLines = NULL;
    }
    break;

  case 5:
/* Line 1778 of yacc.c  */
#line 122 "ptoparser/panoParser.y"
    {
        nbCommentLine = 0;
        commentLines = NULL;
    }
    break;

  case 8:
/* Line 1778 of yacc.c  */
#line 131 "ptoparser/panoParser.y"
    {
        char** curComment = (char**) panoScriptReAlloc((void**) &commentLines,
                                                       sizeof(char*),
                                                       &nbCommentLine);

        if (curComment == NULL) {
            yyerror("Not enough memory");
            return -1;
        }

        *curComment = strdup((yyvsp[(1) - (2)].strVal));
    }
    break;

  case 9:
/* Line 1778 of yacc.c  */
#line 145 "ptoparser/panoParser.y"
    {
        int prevNbImages = script.iInputImagesCount - 1;
        int* curImageCommentsCount = (int*) panoScriptReAlloc((void**) &(script.iImage_prevCommentsCount),
                                                              sizeof(int),
                                                              &prevNbImages);
        if (curImageCommentsCount == NULL) {
            yyerror("Not enough memory");
            return -1;
        }
        *curImageCommentsCount = nbCommentLine;

        prevNbImages--;
        char*** curImageComments = (char***) panoScriptReAlloc((void**) &(script.image_prevComments),
                                                               sizeof(char**),
                                                               &prevNbImages);
        if (curImageComments == NULL) {
            yyerror("Not enough memory");
            return -1;
        }
        *curImageComments = commentLines;
    }
    break;

  case 10:
/* Line 1778 of yacc.c  */
#line 167 "ptoparser/panoParser.y"
    {
        script.iPano_prevCommentsCount = nbCommentLine;
        script.pano_prevComments = commentLines;
    }
    break;

  case 11:
/* Line 1778 of yacc.c  */
#line 172 "ptoparser/panoParser.y"
    {
        script.iOptimize_prevCommentsCount = nbCommentLine;
        script.optimize_prevComments = commentLines;
    }
    break;

  case 12:
/* Line 1778 of yacc.c  */
#line 177 "ptoparser/panoParser.y"
    {
        int prevNbVars = script.iVarsToOptimizeCount - 1;
        int* curVarCommentsCount = (int*) panoScriptReAlloc((void**) &(script.iVarsToOptimize_prevCommentsCount),
                                                            sizeof(int),
                                                            &prevNbVars);
        *curVarCommentsCount = nbCommentLine;

        prevNbVars--;
        char*** curVarComments = (char***) panoScriptReAlloc((void**) &(script.varsToOptimize_prevComments),
                                                             sizeof(char**),
                                                             &prevNbVars);
        *curVarComments = commentLines;
    }
    break;

  case 13:
/* Line 1778 of yacc.c  */
#line 191 "ptoparser/panoParser.y"
    {
        int prevNbCP = script.iCtrlPointsCount - 1;
        int* curCPCommentsCount = (int*) panoScriptReAlloc((void**) &(script.iCtrlPoints_prevCommentsCount),
                                                           sizeof(int),
                                                           &prevNbCP);
        *curCPCommentsCount = nbCommentLine;

        prevNbCP--;
        char*** curCPComments = (char***) panoScriptReAlloc((void**) &(script.ctrlPoints_prevComments),
                                                            sizeof(char**),
                                                            &prevNbCP);
        *curCPComments = commentLines;
    }
    break;

  case 14:
/* Line 1778 of yacc.c  */
#line 205 "ptoparser/panoParser.y"
    {
        int prevNbMasks = script.iCtrlPointsCount - 1;
        int* curMaskCommentsCount = (int*) panoScriptReAlloc((void**) &(script.iMasks_prevCommentsCount),
                                                           sizeof(int),
                                                           &prevNbMasks);
        *curMaskCommentsCount = nbCommentLine;

        prevNbMasks--;
        char*** curMaskComments = (char***) panoScriptReAlloc((void**) &(script.masks_prevComments),
                                                            sizeof(char**),
                                                            &prevNbMasks);
        *curMaskComments = commentLines;
    }
    break;

  case 15:
/* Line 1778 of yacc.c  */
#line 221 "ptoparser/panoParser.y"
    {
        int i;
        currentLine = PT_TOKEN_INPUT_LINE;

        image = (pt_script_image*) panoScriptReAlloc((void**) &(script.inputImageSpec),
                                                     sizeof(pt_script_image),
                                                     &script.iInputImagesCount);

        if (image == NULL) {
            yyerror("Not enough memory");
            return -1;
        }

        image->fHorFOVRef = -1;
        image->yawRef = -1;
        image->pitchRef = -1;
        for (i = 0; i < PANO_PARSER_COEF_COUNT; i++) {
            image->geometryCoefRef[i] = -1;
        }
        image->imageEVRef = -1;
        image->whiteBalanceFactorRedRef = -1;
        image->whiteBalanceFactorBlueRef = -1;
        for (i = 0; i < PANO_PARSER_RESP_CURVE_COEF_COUNT; i++) {
            image->photometricCoefRef[i] = -1;
        }
        image->vignettingCorrectionModeRef = -1;
        for (i = 0; i < PANO_PARSER_VIGN_COEF_COUNT; i++) {
            image->vignettingCorrectionCoefRef[i] = -1;
        }
        image->stackRef = -1;
    }
    break;

  case 17:
/* Line 1778 of yacc.c  */
#line 255 "ptoparser/panoParser.y"
    {
        currentLine = PT_TOKEN_PANO_LINE;
    }
    break;

  case 19:
/* Line 1778 of yacc.c  */
#line 261 "ptoparser/panoParser.y"
    {
        currentLine = PT_TOKEN_OPTIMIZE_OPT_LINE;
    }
    break;

  case 21:
/* Line 1778 of yacc.c  */
#line 269 "ptoparser/panoParser.y"
    {
        currentLine = PT_TOKEN_OPTIMIZE_VARS_LINE;
    }
    break;

  case 24:
/* Line 1778 of yacc.c  */
#line 275 "ptoparser/panoParser.y"
    {
        currentLine = PT_TOKEN_CONTROL_PT_LINE;
        ctrlPoint = (pt_script_ctrl_point*) panoScriptReAlloc((void**) &script.ctrlPointsSpec,
                                                              sizeof(pt_script_ctrl_point),
                                                              &script.iCtrlPointsCount);
        if (ctrlPoint == NULL) {
            yyerror("Not enough memory");
            return -1;
        }
    }
    break;

  case 26:
/* Line 1778 of yacc.c  */
#line 288 "ptoparser/panoParser.y"
    {
        currentLine = PT_TOKEN_MASK_PT_LINE;
        mask = (pt_script_mask*) malloc(sizeof(pt_script_mask));
        if (mask == NULL) {
            yyerror("Not enough memory");
            return -1;
        }
    }
    break;

  case 27:
/* Line 1778 of yacc.c  */
#line 297 "ptoparser/panoParser.y"
    {
        if ((yyvsp[(4) - (4)].iVal) == -1) {
            yyerror("Mask line without an image reference");
            return -1;
        }
        if ((yyvsp[(4) - (4)].iVal) >= script.iInputImagesCount) {
            yyerror("Mask line referencing a missing input image");
            return -1;
        }
        pt_script_mask** maskPtr = (pt_script_mask**) panoScriptReAlloc((void**) &script.masks,
                                                                        sizeof(pt_script_mask*),
                                                                        &script.iMasksCount);

        if (maskPtr == NULL) {
            yyerror("Not enough memory");
            return -1;
        }
        *maskPtr = mask;
    }
    break;

  case 28:
/* Line 1778 of yacc.c  */
#line 318 "ptoparser/panoParser.y"
    {
        DEBUG_1("ENDOFLINE");
        currentLine = -1; /* This says we don't know the type of line being processed */
    }
    break;

  case 31:
/* Line 1778 of yacc.c  */
#line 333 "ptoparser/panoParser.y"
    {
        pt_script_optimize_var* varToOptimize = (pt_script_optimize_var*) panoScriptReAlloc((void**) &script.varsToOptimize,
                                                                                            sizeof(pt_script_optimize_var),
                                                                                            &script.iVarsToOptimizeCount);
        if (varToOptimize == NULL) {
            yyerror("Not enough memory");
            return -1;
        }

        varToOptimize->varName = strdup((yyvsp[(1) - (2)].strVal));
        varToOptimize->varIndex = (yyvsp[(2) - (2)].iVal);
    }
    break;

  case 32:
/* Line 1778 of yacc.c  */
#line 346 "ptoparser/panoParser.y"
    {
        pt_script_optimize_var* varToOptimize = (pt_script_optimize_var*) panoScriptReAlloc((void**) &script.varsToOptimize,
                                                                                            sizeof(pt_script_optimize_var),
                                                                                            &script.iVarsToOptimizeCount);
        if (varToOptimize == NULL) {
            yyerror("Not enough memory");
            return -1;
        }

        char keyword[2];
        keyword[0] = (yyvsp[(1) - (2)].cVal);
        keyword[1] = 0;

        varToOptimize->varName = strdup(keyword);
        varToOptimize->varIndex = (yyvsp[(2) - (2)].iVal);
    }
    break;

  case 45:
/* Line 1778 of yacc.c  */
#line 383 "ptoparser/panoParser.y"
    {
        (yyval.iVal) = (yyvsp[(1) - (1)].iVal);
    }
    break;

  case 46:
/* Line 1778 of yacc.c  */
#line 387 "ptoparser/panoParser.y"
    {
        if ((yyvsp[(1) - (3)].iVal) != -1)
            (yyval.iVal) = (yyvsp[(1) - (3)].iVal);
        else
            (yyval.iVal) = (yyvsp[(3) - (3)].iVal);
    }
    break;

  case 47:
/* Line 1778 of yacc.c  */
#line 395 "ptoparser/panoParser.y"
    {
        (yyval.iVal) = -1;
        switch ((yyvsp[(1) - (2)].cVal)) {
        case 'i':
            mask->iImage = (yyvsp[(2) - (2)].iVal);
            (yyval.iVal) = (yyvsp[(2) - (2)].iVal);
            break;
        case 't':
            mask->type = (yyvsp[(2) - (2)].iVal);
            break;
        default:
            panoScriptParserError("Invalid variable name [%c] in mask line.\n", (yyvsp[(1) - (2)].cVal));
            return -1;
        }
    }
    break;

  case 48:
/* Line 1778 of yacc.c  */
#line 411 "ptoparser/panoParser.y"
    {
        (yyval.iVal) = -1;
        mask->points = NULL;
        mask->iPointsCount = 0;
    }
    break;

  case 51:
/* Line 1778 of yacc.c  */
#line 421 "ptoparser/panoParser.y"
    {
        pt_point* maskPointPtr = (pt_point*) panoScriptReAlloc((void**) &mask->points,
                                                               sizeof(pt_point),
                                                               &mask->iPointsCount);

        if (maskPointPtr == NULL) {
            yyerror("Not enough memory");
            return -1;
        }
        maskPointPtr->x = (yyvsp[(1) - (3)].iVal);
        maskPointPtr->y = (yyvsp[(3) - (3)].iVal);
    }
    break;

  case 52:
/* Line 1778 of yacc.c  */
#line 436 "ptoparser/panoParser.y"
    {
        if (currentLine != PT_TOKEN_PANO_LINE && currentLine != PT_TOKEN_INPUT_LINE) {
            panoScriptParserError("Error: There shouldn't be any cropping parameter here!\n");
            return -1;
        }

        int* cropArea = NULL;
        if (currentLine == PT_TOKEN_PANO_LINE) {
            cropArea = script.pano.cropArea;
        } else {
            cropArea = image->cropArea;
        }
        switch ((yyvsp[(1) - (8)].cVal)) {
        case 'C':
        case 'S':
            cropArea[0] = (yyvsp[(2) - (8)].iVal);
            cropArea[1] = (yyvsp[(4) - (8)].iVal);
            cropArea[2] = (yyvsp[(6) - (8)].iVal);
            cropArea[3] = (yyvsp[(8) - (8)].iVal);
            break;
        default:
            panoScriptParserError("Invalid variable name- [%c] in image line\n", (yyvsp[(1) - (8)].cVal));
            return -1;
        }
    }
    break;

  case 53:
/* Line 1778 of yacc.c  */
#line 464 "ptoparser/panoParser.y"
    {
        if (currentLine != PT_TOKEN_INPUT_LINE) {
            panoScriptParserError("Error: References should only be present on i lines!\n");
            return -1;
        }
        int imageRef = (yyvsp[(3) - (3)].iVal);
        char *keyword = (yyvsp[(1) - (3)].strVal);

        switch (*keyword) {
        case 'R':
        {
            switch (*(keyword + 1)) {
            case 'a':
            case 'b':
            case 'c':
            case 'd':
            case 'e':
                if (*(keyword + 2) == '\0') {
                    image->photometricCoefRef[*(keyword + 1) - 'a'] = imageRef;
                    break;
                }
            default:
                panoScriptParserError("Invalid variable name [%s]\n", keyword);
                return -1;
            }
            break;
        }
        case 'V':
        {
            if (*(keyword + 2) != '\0') {
                panoScriptParserError("Invalid variable name [%s]\n", keyword);
                return -1;
            }
            switch (*(keyword + 1)) {
            case 'a':
            case 'b':
            case 'c':
            case 'd':
            case 'e':
                image->vignettingCorrectionCoefRef[*(keyword + 1) - 'a'] = imageRef;
                break;
            case 'm':
                image->vignettingCorrectionModeRef = imageRef;
                break;
            case 'x':
            case 'y':
                image->vignettingCorrectionCoefRef[*(keyword + 1) - 'x' + 4] = imageRef;
                break;
            default:
                panoScriptParserError("Invalid variable name [%s]\n", keyword);
                return -1;
            }
            break;
        }
        case 'E':
        {
            if (strcmp(keyword, "Eev") == 0) {
                image->imageEVRef = imageRef;
                break;
            }


            if (*(keyword + 2) != '\0') {
                panoScriptParserError("Invalid variable name [%s]\n", keyword);
                return -1;
            }
            switch (*(keyword + 1)) {
            case 'r':
                image->whiteBalanceFactorRedRef = imageRef;
                break;
            case 'b':
                image->whiteBalanceFactorBlueRef = imageRef;
                break;
            default:
                panoScriptParserError("Invalid variable name [%s]\n", keyword);
                return -1;
            }
            break;
        }
        default:
            panoScriptParserError("Invalid variable name [%s]\n", keyword);
            return -1;
        }
    }
    break;

  case 54:
/* Line 1778 of yacc.c  */
#line 549 "ptoparser/panoParser.y"
    {
        int imageRef = (yyvsp[(3) - (3)].iVal);

        if (currentLine != PT_TOKEN_INPUT_LINE) {
            panoScriptParserError("Error: References should only be present on i lines!\n");
            return -1;
        }
        switch ((yyvsp[(1) - (3)].cVal)) {
        case 'v':
            image->fHorFOVRef = imageRef;
            break;
        case 'y':
            image->yawRef = imageRef;
            break;
        case 'p':
            image->pitchRef = imageRef;
            break;
        case 'r':
            image->rollRef = imageRef;
            break;
        case 'a':
        case 'b':
        case 'c':
        case 'd':
        case 'e':
            image->geometryCoefRef[(yyvsp[(1) - (3)].cVal) - 'a'] = imageRef;
            break;
        case 'g':
            image->geometryCoefRef[5] = imageRef;
            break;
        case 't':
            image->geometryCoefRef[6] = imageRef;
            break;
        case 'j':
            image->stackRef = imageRef;
            break;
        default:
            panoScriptParserError("Invalid variable name [%c=] in input line.\n", (yyvsp[(1) - (3)].cVal));
            return -1;
        }
    }
    break;

  case 55:
/* Line 1778 of yacc.c  */
#line 594 "ptoparser/panoParser.y"
    {
        /* For the case where the keyword is one char, followed by a string */

        DEBUG_2("Token %s", (yyvsp[(2) - (2)].strVal));

        /* Processing of string variables */
        switch (currentLine) {
        case PT_TOKEN_PANO_LINE:
            switch ((yyvsp[(1) - (2)].cVal)) {
            case 'n':
                ParserStringCopy(&script.pano.outputFormat, (yyvsp[(2) - (2)].strVal));
                break;
            case 'T':
                if (strncmp((yyvsp[(2) - (2)].strVal), "UINT", 4) == 0) {
                    if (strcmp((yyvsp[(2) - (2)].strVal) + 4, "8") == 0) {
                        script.pano.bitDepthOutput = UINT8;
                    } else if (strcmp((yyvsp[(2) - (2)].strVal) + 4, "16") == 0) {
                        script.pano.bitDepthOutput = UINT16;
                    } else {
                        panoScriptParserError("Invalid bitdepth [%s] in pano line\n", (yyvsp[(2) - (2)].strVal));
                        return -1;
                    }
                } else if (strcmp((yyvsp[(2) - (2)].strVal), "FLOAT") == 0) {
                        script.pano.bitDepthOutput = FLOAT;
                } else {
                    panoScriptParserError("Invalid bitdepth [%s] in pano line\n", (yyvsp[(2) - (2)].strVal));
                    return -1;
                }
                break;
            default:
                panoScriptParserError("Invalid variable name [%c] in pano line\n", (yyvsp[(1) - (2)].cVal));
                return -1;
            }
            break;
        case PT_TOKEN_INPUT_LINE:
            if ((yyvsp[(1) - (2)].cVal) != 'n') {
                panoScriptParserError("Invalid variable name [%c] in image line...\n", (yyvsp[(1) - (2)].cVal));
                return -1;
            }
            ParserStringCopy(&image->name, (yyvsp[(2) - (2)].strVal));
            break;
        default:
            panoScriptParserError("Error Not handled case [%c]\n", (yyvsp[(1) - (2)].cVal));
            return -1;
        }
    }
    break;

  case 56:
/* Line 1778 of yacc.c  */
#line 641 "ptoparser/panoParser.y"
    {
        if (currentLine != PT_TOKEN_PANO_LINE) {
            panoScriptParserError("Unexpected 'P' parameter!!\n");
        }
        nbProjParms = 0;
        projParms = NULL;
    }
    break;

  case 57:
/* Line 1778 of yacc.c  */
#line 649 "ptoparser/panoParser.y"
    {
        /* Processing of int variables with keyword of one character only */
        switch (currentLine) {
        case PT_TOKEN_CONTROL_PT_LINE:
            switch ((yyvsp[(1) - (2)].cVal)) {
            case 'n':
                ctrlPoint->iImage1 = (yyvsp[(2) - (2)].iVal);
                break;
            case 'N':
                ctrlPoint->iImage2 = (yyvsp[(2) - (2)].iVal);
                break;
            case 'x':
                ctrlPoint->p1.x = (yyvsp[(2) - (2)].iVal);
                break;
            case 'y':
                ctrlPoint->p1.y = (yyvsp[(2) - (2)].iVal);
                break;
            case 'X':
                ctrlPoint->p2.x = (yyvsp[(2) - (2)].iVal);
                break;
            case 'Y':
                ctrlPoint->p2.y = (yyvsp[(2) - (2)].iVal);
                break;
            case 't':
                ctrlPoint->type = (yyvsp[(2) - (2)].iVal);
                break;
            default:
                panoScriptParserError("Invalid variable name [%c] in control point line.\n", (yyvsp[(1) - (2)].cVal));
                return -1;
            }
            break;
        case PT_TOKEN_PANO_LINE:
            switch ((yyvsp[(1) - (2)].cVal)) {
            case 'w':
                script.pano.width = (yyvsp[(2) - (2)].iVal);
                break;
            case 'h':
                script.pano.height = (yyvsp[(2) - (2)].iVal);
                break;
            case 'f':
                script.pano.projection = (yyvsp[(2) - (2)].iVal);
                break;
            case 'v':
                script.pano.fHorFOV = (yyvsp[(2) - (2)].iVal);
                break;
            case 'k':
                script.pano.iImagePhotometricReference = (yyvsp[(2) - (2)].iVal);
                break;
            case 'E':
                script.pano.exposureValue = (yyvsp[(2) - (2)].iVal);
                break;
            case 'R':
                script.pano.dynamicRangeMode = (yyvsp[(2) - (2)].iVal);
                break;
            default:
                panoScriptParserError("Error Invalid variable name [%c] in pano line\n", (yyvsp[(1) - (2)].cVal));
                return -1;
            }
            break;
        case PT_TOKEN_INPUT_LINE:
            switch ((yyvsp[(1) - (2)].cVal)) {
            case 'w':
                image->width = (yyvsp[(2) - (2)].iVal);
                break;
            case 'h':
                image->height = (yyvsp[(2) - (2)].iVal);
                break;
            case 'f':
                image->projection = (yyvsp[(2) - (2)].iVal);
                break;
            case 'v':
                image->fHorFOV = (yyvsp[(2) - (2)].iVal);
                break;
            case 'y':
                image->yaw = (yyvsp[(2) - (2)].iVal);
                break;
            case 'p':
                image->pitch = (yyvsp[(2) - (2)].iVal);
                break;
            case 'r':
                image->roll = (yyvsp[(2) - (2)].iVal);
                break;
            case 'a':
            case 'b':
            case 'c':
            case 'd':
            case 'e':
                image->geometryCoef[(yyvsp[(1) - (2)].cVal) - 'a'] = (yyvsp[(2) - (2)].iVal);
                break;
            case 'g':
                image->geometryCoef[5] = (yyvsp[(2) - (2)].iVal);
                break;
            case 't':
                image->geometryCoef[6] = (yyvsp[(2) - (2)].iVal);
                break;
            case 'j':
                image->stack = (yyvsp[(2) - (2)].iVal);
                break;
            default:
                panoScriptParserError("Invalid variable name [%c] in image line...\n", (yyvsp[(1) - (2)].cVal));
                return -1;
            }
            break;
        case PT_TOKEN_OPTIMIZE_OPT_LINE:
            switch ((yyvsp[(1) - (2)].cVal)) {
            case 'g':
                script.optimize.fGamma = (yyvsp[(2) - (2)].iVal);
                if (script.optimize.fGamma <= 0.0) {
                    panoScriptParserError("Invalid value for gamma %f. Must be bigger than zero\n", script.optimize.fGamma);
                }
            break;
            case 'i':
                script.optimize.interpolator = (yyvsp[(2) - (2)].iVal);
                break;
            case 'f':
                script.optimize.fastFT = 2 - (yyvsp[(2) - (2)].iVal);
                break;
            case 'm':
                script.optimize.huberEstimator = (yyvsp[(2) - (2)].iVal);
                break;
            case 'p':
                script.optimize.photometricHuberSigma = (yyvsp[(2) - (2)].iVal);
                break;
            default:
                panoScriptParserError("Invalid variable name [%c] in optimize line\n", (yyvsp[(1) - (2)].cVal));
                return -1;
            }
            break;
        default:
            panoScriptParserError("Error. Not handled (token int [%c])\n", (yyvsp[(1) - (2)].cVal));
            return -1;
        }
    }
    break;

  case 58:
/* Line 1778 of yacc.c  */
#line 783 "ptoparser/panoParser.y"
    {
        /* Processing of int variables with keyword of one character only */
        switch (currentLine) {
        case PT_TOKEN_CONTROL_PT_LINE:
            switch ((yyvsp[(1) - (2)].cVal)) {
            case 'x':
                ctrlPoint->p1.x = (yyvsp[(2) - (2)].fVal);
                break;
            case 'y':
                ctrlPoint->p1.y = (yyvsp[(2) - (2)].fVal);
                break;
            case 'X':
                ctrlPoint->p2.x = (yyvsp[(2) - (2)].fVal);
                break;
            case 'Y':
                ctrlPoint->p2.y = (yyvsp[(2) - (2)].fVal);
                break;
            case 't':
                ctrlPoint->type = (yyvsp[(2) - (2)].fVal);
                break;
            default:
                panoScriptParserError("Invalid variable name [%c] in control point line.\n", (yyvsp[(1) - (2)].cVal));
                return -1;
            }
            break;
        case PT_TOKEN_PANO_LINE:
            switch ((yyvsp[(1) - (2)].cVal)) {
            case 'v':
                script.pano.fHorFOV = (yyvsp[(2) - (2)].fVal);
                break;
            case 'E':
                script.pano.exposureValue = (yyvsp[(2) - (2)].fVal);
                break;
            default:
                panoScriptParserError("Error Invalid variable name [%c] in pano line\n", (yyvsp[(1) - (2)].cVal));
                return -1;
            }
            break;
        case PT_TOKEN_INPUT_LINE:
            switch ((yyvsp[(1) - (2)].cVal)) {
            case 'v':
                image->fHorFOV = (yyvsp[(2) - (2)].fVal);
                break;
            case 'y':
                image->yaw = (yyvsp[(2) - (2)].fVal);
                break;
            case 'p':
                image->pitch = (yyvsp[(2) - (2)].fVal);
                break;
            case 'r':
                image->roll = (yyvsp[(2) - (2)].fVal);
                break;
            case 'a':
            case 'b':
            case 'c':
            case 'd':
            case 'e':
                image->geometryCoef[(yyvsp[(1) - (2)].cVal) - 'a'] = (yyvsp[(2) - (2)].fVal);
                break;
            case 'g':
                image->geometryCoef[5] = (yyvsp[(2) - (2)].fVal);
                break;
            case 't':
                image->geometryCoef[6] = (yyvsp[(2) - (2)].fVal);
                break;
            default:
                panoScriptParserError("Invalid variable name [%c] in image line...\n", (yyvsp[(1) - (2)].cVal));
                return -1;
            }
            break;
        case PT_TOKEN_OPTIMIZE_OPT_LINE:
            switch ((yyvsp[(1) - (2)].cVal)) {
            case 'g':
                script.optimize.fGamma = (yyvsp[(2) - (2)].fVal);
                if (script.optimize.fGamma <= 0.0) {
                    panoScriptParserError("Invalid value for gamma %f. Must be bigger than zero\n", script.optimize.fGamma);
                }
                break;
            case 'm':
                script.optimize.huberEstimator = (yyvsp[(2) - (2)].fVal);
                break;
            case 'p':
                script.optimize.photometricHuberSigma = (yyvsp[(2) - (2)].fVal);
                break;
            default:
                panoScriptParserError("Invalid variable name [%c] in optimize line\n", (yyvsp[(1) - (2)].cVal));
                return -1;
            }
            break;
        default:
            panoScriptParserError("Error. Not handled (token int [%c])\n", (yyvsp[(1) - (2)].cVal));
            return -1;
        }
    }
    break;

  case 59:
/* Line 1778 of yacc.c  */
#line 878 "ptoparser/panoParser.y"
    {
        if (currentLine != PT_TOKEN_INPUT_LINE) {
            panoScriptParserError("Invalid variable name [%s]\n", (yyvsp[(1) - (2)].strVal));
            return -1;
        }
        if (strcmp((yyvsp[(1) - (2)].strVal), "Vf") != 0) {
            panoScriptParserError("Invalid variable name [%s] in image line...\n", (yyvsp[(1) - (2)].strVal));
            return -1;
        }
        ParserStringCopy(&image->vignettingFlatFieldFile, (yyvsp[(2) - (2)].strVal));
        break;
    }
    break;

  case 60:
/* Line 1778 of yacc.c  */
#line 891 "ptoparser/panoParser.y"
    {
        char *keyword = (yyvsp[(1) - (2)].strVal);

        switch (*keyword) {
        case 'R':
        {
            switch (*(keyword + 1)) {
            case 'a':
            case 'b':
            case 'c':
            case 'd':
            case 'e':
                if (*(keyword + 2) == '\0') {
                    image->photometricCoef[*(keyword + 1) - 'a'] = (yyvsp[(2) - (2)].fVal);
                    break;
                }
            default:
                panoScriptParserError("Invalid variable name [%s]\n", keyword);
                return -1;
            }
            break;
        }
        case 'V':
        {
            if (*(keyword + 2) != '\0') {
                panoScriptParserError("Invalid variable name [%s]\n", keyword);
                return -1;
            }
            switch (*(keyword + 1)) {
            case 'a':
            case 'b':
            case 'c':
            case 'd':
            case 'e':
                image->vignettingCorrectionCoef[*(keyword + 1) - 'a'] = (yyvsp[(2) - (2)].fVal);
                break;
            case 'm':
                image->vignettingCorrectionMode = lroundf((yyvsp[(2) - (2)].fVal));
                break;
            case 'x':
            case 'y':
                image->vignettingCorrectionCoef[*(keyword + 1) - 'x' + 4] = (yyvsp[(2) - (2)].fVal);
                break;
            default:
                panoScriptParserError("Invalid variable name [%s]\n", keyword);
                return -1;
            }
            break;
        }
        case 'E':
        {
            if (strcmp(keyword + 1, "ev") == 0) {
                image->imageEV = (yyvsp[(2) - (2)].fVal);
                break;
            }


            if (*(keyword + 2) != '\0') {
                panoScriptParserError("Invalid variable name [%s]\n", keyword);
                return -1;
            }
            switch (*(keyword + 1)) {
            case 'r':
                image->whiteBalanceFactorRed = (yyvsp[(2) - (2)].fVal);
                break;
            case 'b':
                image->whiteBalanceFactorBlue = (yyvsp[(2) - (2)].fVal);
                break;
            default:
                panoScriptParserError("Invalid variable name [%s]\n", keyword);
                return -1;
            }
            break;
        }
        case 'T':
        {
            if (*(keyword + 1) != 'r' || *(keyword + 3) != '\0') {
                panoScriptParserError("Invalid variable name [%s]\n", keyword);
                return -1;
            }
            switch (*(keyword + 2)) {
            case 'X':
            case 'Y':
            case 'Z':
                image->translationCoef[*(keyword + 2) - 'X'] = (yyvsp[(2) - (2)].fVal);
                break;
            default:
                panoScriptParserError("Invalid variable name [%s]\n", keyword);
                return -1;
            }
            break;
        }
        default:
            panoScriptParserError("Invalid variable name [%s]\n", keyword);
            return -1;
        }
    }
    break;

  case 61:
/* Line 1778 of yacc.c  */
#line 992 "ptoparser/panoParser.y"
    {
        switch (currentLine) {
        case PT_TOKEN_PANO_LINE:
            if ((yyvsp[(1) - (1)].cVal) != 'T') {
                panoScriptParserError("Invalid variable name [%c] in pano line\n", (yyvsp[(1) - (1)].cVal));
                return -1;
            }
            script.pano.bitDepthOutput = UINT8;
            break;
        case PT_TOKEN_INPUT_LINE:
            panoScriptParserError("Invalid variable name [%c] in image line....\n", (yyvsp[(1) - (1)].cVal));
            return -1;
        default:
            panoScriptParserError("Error Not handled 3\n");
            return -1;
        }
    }
    break;

  case 62:
/* Line 1778 of yacc.c  */
#line 1011 "ptoparser/panoParser.y"
    {
        double* param = (double*) panoScriptReAlloc((void**) &projParms,
                                                    sizeof(double),
                                                    &nbProjParms);
        *param = (yyvsp[(1) - (1)].fVal);
    }
    break;

  case 63:
/* Line 1778 of yacc.c  */
#line 1018 "ptoparser/panoParser.y"
    {
        double* param = (double*) panoScriptReAlloc((void**) &projParms,
                                                    sizeof(double),
                                                    &nbProjParms);
        *param = (yyvsp[(3) - (3)].fVal);
    }
    break;

  case 64:
/* Line 1778 of yacc.c  */
#line 1025 "ptoparser/panoParser.y"
    {(yyval.fVal) = (yyvsp[(1) - (1)].fVal);}
    break;

  case 65:
/* Line 1778 of yacc.c  */
#line 1027 "ptoparser/panoParser.y"
    {(yyval.iVal) = (yyvsp[(1) - (1)].iVal);}
    break;

  case 66:
/* Line 1778 of yacc.c  */
#line 1029 "ptoparser/panoParser.y"
    {(yyval.fVal) = (yyvsp[(1) - (1)].fVal);}
    break;

  case 67:
/* Line 1778 of yacc.c  */
#line 1030 "ptoparser/panoParser.y"
    {(yyval.fVal) = (yyvsp[(1) - (1)].iVal);}
    break;


/* Line 1778 of yacc.c  */
#line 2514 "/tmp/digikam-sc/build/extra/kipi-plugins/panorama/panoParser.c"
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

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
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
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

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

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
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
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


/* Line 2041 of yacc.c  */
#line 1033 "ptoparser/panoParser.y"

