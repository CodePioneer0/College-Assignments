#ifndef VALUES_H
#define VALUES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* e) Parentheses, Curly braces & Punctuation */
#define LPAREN_TOK '('      
#define RPAREN_TOK ')'      
#define LBRACE_TOK '{'
#define RBRACE_TOK '}'
#define SEMICOLON_TOK ';' 
#define COMMA_TOK ','  

/* a) Arithmetic Operators */
#define MINUS_TOK '-'       
#define PLUS_TOK '+'
#define MULT_TOK '*'
#define DIV_TOK '/'
#define MOD_TOK '%'
#define INC_TOK 300
#define DEC_TOK 301

/* a) Relational Operators */
#define GT_TOK '>'         
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
#define EQ_TOK '='          
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

/* b) Reserved words (All 32 Standard C Keywords) */
#define AUTO_TOK 256
#define BREAK_TOK 257
#define CASE_TOK 258
#define CHAR_TOK 259
#define CONST_TOK 260
#define CONTINUE_TOK 261
#define DEFAULT_TOK 262
#define DO_TOK 263
#define DOUBLE_TOK 264
#define ELSE_TOK 265
#define ENUM_TOK 266
#define EXTERN_TOK 267
#define FLOAT_TOK 268
#define FOR_TOK 269
#define GOTO_TOK 270
#define IF_TOK 271
#define INT_TOK 272
#define LONG_TOK 273
#define REGISTER_TOK 274
#define RETURN_TOK 275
#define SHORT_TOK 276
#define SIGNED_TOK 277
#define SIZEOF_TOK 278
#define STATIC_TOK 279
#define STRUCT_TOK 280
#define SWITCH_TOK 281
#define TYPEDEF_TOK 282
#define UNION_TOK 283
#define UNSIGNED_TOK 284
#define VOID_TOK 285
#define VOLATILE_TOK 286
#define WHILE_TOK 287 

/* c) Identifier, Constants & Strings */
#define ID_TOK 350          
#define INTCONST_TOK 351    
#define STRING_TOK 352

/* Internal Lexer Definitions */
#define EOF_TOK 0
#define UNKNOWN_TOK 400

/* ==================================================================
   ERROR TOKEN DEFINITIONS & LIMITS
   ================================================================== */
#define EXCEEDS_LENGTH_ERR_TOK 501
#define ILLEGAL_CHAR_ERR_TOK 502
#define UNMATCHED_STRING_ERR_TOK 503
#define SPELLING_ERR_TOK 504
#define INVALID_SUFFIX_ERR_TOK 505

#define MAX_LEXEME_LEN 31 /* Max length for IDs and Numbers */[cite: 13]

#endif