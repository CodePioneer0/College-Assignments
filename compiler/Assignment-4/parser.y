%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int yylineno;
extern char* yytext;
int yylex();
void yyerror(char *s);

/* Symbol Table to enforce "declare before use" requirement */
char sym_table[1000][32];
int sym_count = 0;

void add_symbol(char *name) {
    for(int i = 0; i < sym_count; i++) {
        if(strcmp(sym_table[i], name) == 0) return; /* Symbol already exists in scope */
    }
    strcpy(sym_table[sym_count++], name);
}

void check_symbol(char *name) {
    for(int i = 0; i < sym_count; i++) {
        if(strcmp(sym_table[i], name) == 0) return; /* Symbol found */
    }
    /* Semantic error for undeclared variables */
    fprintf(stderr, "Semantic Error at line %d: Variable '%s' must be declared before use.\n", yylineno, name);
}
%}

%union {
    int iValue;
    char* sIndex;
}

/* Tokens */
%token <sIndex> ID
%token <iValue> NUM
%token INT FLOAT VOID MAIN
%token IF ELSE WHILE FOR RETURN
%token PLUS MINUS MULT DIV ASSIGN
%token EQ NEQ LT GT LE GE
%token SEMICOLON COMMA LPAREN RPAREN LBRACE RBRACE

/* Precedence and Associativity to resolve ambiguities */
%nonassoc IFX
%nonassoc ELSE
%left EQ NEQ LT GT LE GE
%left PLUS MINUS
%left MULT DIV

%start program

%%

/* Main function & User defined functions */
program: 
      global_declarations function_definitions main_function
    ;

/* Global/Local Declarations */
global_declarations: 
      global_declarations declaration
    | /* empty */
    ;

declaration: 
      type id_list SEMICOLON
    ;

type: 
      INT 
    | FLOAT 
    | VOID
    ;

id_list: 
      ID                    { add_symbol($1); }
    | id_list COMMA ID      { add_symbol($3); }
    ;

function_definitions: 
      function_definitions function_def
    | /* empty */
    ;

function_def: 
      type ID LPAREN param_list RPAREN block
    ;

param_list: 
      params 
    | /* empty */
    ;

params: 
      param 
    | params COMMA param
    ;

param: 
      type ID               { add_symbol($2); }
    ;

main_function: 
      type MAIN LPAREN RPAREN block
    ;

/* Blocks enforce that variables can only be defined at the very beginning */
block: 
      LBRACE global_declarations statement_list RBRACE
    ;

statement_list: 
      statement_list statement 
    | /* empty */
    ;

/* Statements */
statement: 
      assignment_stmt
    | conditional_stmt
    | iterative_stmt
    | function_call_stmt
    | block
    | RETURN expr SEMICOLON
    ;

/* Assignment Statements */
assignment_stmt: 
      ID ASSIGN expr SEMICOLON { check_symbol($1); }
    ;

/* Conditional Statements */
conditional_stmt: 
      IF LPAREN expr RPAREN block %prec IFX
    | IF LPAREN expr RPAREN block ELSE block
    ;

/* Iterative Statements */
iterative_stmt: 
      WHILE LPAREN expr RPAREN block
    | FOR LPAREN assignment_stmt expr SEMICOLON ID ASSIGN expr RPAREN block { check_symbol($6); }
    ;

/* Function Call */
function_call_stmt: 
      ID LPAREN arg_list RPAREN SEMICOLON
    ;

arg_list: 
      args 
    | /* empty */
    ;

args: 
      expr 
    | args COMMA expr
    ;

/* Expressions */
expr: 
      expr PLUS expr
    | expr MINUS expr
    | expr MULT expr
    | expr DIV expr
    | expr LT expr
    | expr GT expr
    | expr LE expr
    | expr GE expr
    | expr EQ expr
    | expr NEQ expr
    | LPAREN expr RPAREN
    | ID                    { check_symbol($1); }
    | NUM
    | ID LPAREN arg_list RPAREN 
    ;

%%

void yyerror(char *s) {
    fprintf(stderr, "Syntax Error at line %d: %s\n", yylineno, s);
}

int main(void) {
    if (yyparse() == 0) {
        printf("Parsed Successfully.\n");
    }
    return 0;
}