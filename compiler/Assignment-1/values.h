#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/* ==================================================================
   TOKEN DEFINITIONS (Categorized as per assignment)
   ================================================================== */

/* e) Parentheses, Curly braces & Punctuation */
#define LPAREN_TOK '('      /* Defined explicitly in L02_CD_lab_Lex.pdf */
#define RPAREN_TOK ')'      /* Defined explicitly in L02_CD_lab_Lex.pdf */
#define LBRACE_TOK '{'
#define RBRACE_TOK '}'
#define SEMICOLON_TOK ';'   /* Defined explicitly in L02_CD_lab_Lex.pdf */

/* a) Arithmetic Operators */
#define MINUS_TOK '-'       /* Defined explicitly in L02_CD_lab_Lex.pdf */
#define PLUS_TOK '+'
#define MULT_TOK '*'
#define DIV_TOK '/'
#define MOD_TOK '%'
#define INC_TOK 300
#define DEC_TOK 301

/* a) Relational Operators */
#define GT_TOK '>'          /* Defined explicitly in L02_CD_lab_Lex.pdf */
#define LT_TOK '<'
#define GE_TOK 302
#define LE_TOK 303
#define EQ_EQ_TOK 304
#define NEQ_TOK 305

/* a) Logical Operators */
#define LOGICAL_NOT_TOK '!'
#define LOGICAL_AND_TOK 306
#define LOGICAL_OR_TOK 307

/* a) Bitwise Operators */
#define BITWISE_AND_TOK '&'
#define BITWISE_OR_TOK '|'
#define BITWISE_XOR_TOK '^'
#define BITWISE_NOT_TOK '~'
#define LSHIFT_TOK 308
#define RSHIFT_TOK 309

/* a) Assignment Operators */
#define EQ_TOK '='          /* Defined explicitly in L02_CD_lab_Lex.pdf */
#define PLUS_ASSIGN_TOK 310
#define MINUS_ASSIGN_TOK 311
#define MULT_ASSIGN_TOK 312
#define DIV_ASSIGN_TOK 313
#define MOD_ASSIGN_TOK 314
#define LSHIFT_ASSIGN_TOK 315
#define RSHIFT_ASSIGN_TOK 316
#define AND_ASSIGN_TOK 317
#define OR_ASSIGN_TOK 318
#define XOR_ASSIGN_TOK 319

/* b) Reserved words */
#define WHILE_TOK 256       /* Defined explicitly in L02_CD_lab_Lex.pdf */
#define FOR_TOK 257
#define IF_TOK 258
#define ELSE_TOK 259
#define INT_TOK 260
#define FLOAT_TOK 261
#define CHAR_TOK 262

/* c) Identifier & d) Integer Constants */
#define ID_TOK 350          /* Defined explicitly in L02_CD_lab_Lex.pdf */
#define INTCONST_TOK 351    /* Defined explicitly in L02_CD_lab_Lex.pdf */

/* Internal Lexer Definitions */
#define EOF_TOK 0
#define UNKNOWN_TOK 400
