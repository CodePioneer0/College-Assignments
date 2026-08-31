%{
#include "values.h"
/* Declare the spelling error function which will be linked from main.c */
extern int is_spelling_error(const char* str);
%}

/* Tell Flex not to require a yywrap function, and to automatically track line numbers */
%option noyywrap yylineno

/* REGULAR DEFINITIONS */
WS          [ \t\n\r]+
DIGIT       [0-9]
LETTER      [a-zA-Z_]
ID          {LETTER}({LETTER}|{DIGIT})*
ICONST      {DIGIT}+

/* Custom regex to catch bad suffixes like '12@45' or 'count$' */
BAD_SUFFIX  ({ICONST}[a-zA-Z_@#$]+|{ID}[@#$]+)[a-zA-Z0-9@#$]*

%%

{WS}        { /* Ignore whitespace entirely */ }

"auto"      { return AUTO_TOK; }
"break"     { return BREAK_TOK; }
"case"      { return CASE_TOK; }
"char"      { return CHAR_TOK; }
"const"     { return CONST_TOK; }
"continue"  { return CONTINUE_TOK; }
"default"   { return DEFAULT_TOK; }
"do"        { return DO_TOK; }
"double"    { return DOUBLE_TOK; }
"else"      { return ELSE_TOK; }
"enum"      { return ENUM_TOK; }
"extern"    { return EXTERN_TOK; }
"float"     { return FLOAT_TOK; }
"for"       { return FOR_TOK; }
"goto"      { return GOTO_TOK; }
"if"        { return IF_TOK; }
"int"       { return INT_TOK; }
"long"      { return LONG_TOK; }
"register"  { return REGISTER_TOK; }
"return"    { return RETURN_TOK; }
"short"     { return SHORT_TOK; }
"signed"    { return SIGNED_TOK; }
"sizeof"    { return SIZEOF_TOK; }
"static"    { return STATIC_TOK; }
"struct"    { return STRUCT_TOK; }
"switch"    { return SWITCH_TOK; }
"typedef"   { return TYPEDEF_TOK; }
"union"     { return UNION_TOK; }
"unsigned"  { return UNSIGNED_TOK; }
"void"      { return VOID_TOK; }
"volatile"  { return VOLATILE_TOK; }
"while"     { return WHILE_TOK; }

"("         { return LPAREN_TOK; }
")"         { return RPAREN_TOK; }
"{"         { return LBRACE_TOK; }
"}"         { return RBRACE_TOK; }
";"         { return SEMICOLON_TOK; }
","         { return COMMA_TOK; }

"++"        { return INC_TOK; }
"--"        { return DEC_TOK; }
"+="        { return PLUS_ASSIGN_TOK; }
"-="        { return MINUS_ASSIGN_TOK; }
"*="        { return MULT_ASSIGN_TOK; }
"/="        { return DIV_ASSIGN_TOK; }
"%="        { return MOD_ASSIGN_TOK; }
"=="        { return EQ_EQ_TOK; }
"!="        { return NEQ_TOK; }
">="        { return GE_TOK; }
"<="        { return LE_TOK; }
"&&"        { return LOGICAL_AND_TOK; }
"||"        { return LOGICAL_OR_TOK; }
"<<"        { return LSHIFT_TOK; }
">>"        { return RSHIFT_TOK; }
"<<="       { return LSHIFT_ASSIGN_TOK; }
">>="       { return RSHIFT_ASSIGN_TOK; }
"&="        { return AND_ASSIGN_TOK; }
"|="        { return OR_ASSIGN_TOK; }
"^="        { return XOR_ASSIGN_TOK; }

"+"         { return PLUS_TOK; }
"-"         { return MINUS_TOK; }
"*"         { return MULT_TOK; }
"/"         { return DIV_TOK; }
"%"         { return MOD_TOK; }
">"         { return GT_TOK; }
"<"         { return LT_TOK; }
"="         { return EQ_TOK; }
"!"         { return LOGICAL_NOT_TOK; }
"&"         { return BITWISE_AND_TOK; }
"|"         { return BITWISE_OR_TOK; }
"^"         { return BITWISE_XOR_TOK; }
"~"         { return BITWISE_NOT_TOK; }

\"[^\"\n]*\" { return STRING_TOK; }
\"[^\"\n]*\n { return UNMATCHED_STRING_ERR_TOK; }

{BAD_SUFFIX} { return INVALID_SUFFIX_ERR_TOK; }

{ID}        { 
                if (yyleng >= MAX_LEXEME_LEN) return EXCEEDS_LENGTH_ERR_TOK;
                if (is_spelling_error(yytext)) return SPELLING_ERR_TOK;
                return ID_TOK; 
            }

{ICONST}    { 
                if (yyleng >= MAX_LEXEME_LEN) return EXCEEDS_LENGTH_ERR_TOK;
                return INTCONST_TOK; 
            }

.           { return ILLEGAL_CHAR_ERR_TOK; } /* Catch-all for illegal characters */

%%