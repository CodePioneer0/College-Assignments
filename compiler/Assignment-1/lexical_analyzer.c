#include "values.h"

int yylex() {
    int c;

    /* Skip whitespaces and track newlines */
    while ((c = fgetc(yyin)) != EOF) {
        if (c == '\n') yylineno++;
        else if (!isspace(c)) break;
    }

    if (c == EOF) return EOF_TOK;

    yyleng = 0;
    yytext[yyleng++] = (char)c;
    yytext[yyleng] = '\0';

    /* 1. Identifiers and Reserved Words */
    if (isalpha(c) || c == '_') {
        while ((c = fgetc(yyin)) != EOF && (isalnum(c) || c == '_')) {
            yytext[yyleng++] = (char)c;
        }
        if (c != EOF) ungetc(c, yyin);
        yytext[yyleng] = '\0';

        if (strcmp(yytext, "while") == 0) return WHILE_TOK;
        if (strcmp(yytext, "for") == 0) return FOR_TOK;
        if (strcmp(yytext, "if") == 0) return IF_TOK;
        if (strcmp(yytext, "else") == 0) return ELSE_TOK;
        if (strcmp(yytext, "int") == 0) return INT_TOK;
        if (strcmp(yytext, "float") == 0) return FLOAT_TOK;
        if (strcmp(yytext, "char") == 0) return CHAR_TOK;
        return ID_TOK;
    }

    /* 2. Integer Constants */
    if (isdigit(c)) {
        while ((c = fgetc(yyin)) != EOF && isdigit(c)) {
            yytext[yyleng++] = (char)c;
        }
        if (c != EOF) ungetc(c, yyin);
        yytext[yyleng] = '\0';
        return INTCONST_TOK;
    }

    /* 3. Operators and Punctuation (Loop and Switch approach) */
    switch (c) {
        /* Parentheses, Curly braces & Punctuation */
        case '(': return LPAREN_TOK;
        case ')': return RPAREN_TOK;
        case '{': return LBRACE_TOK;
        case '}': return RBRACE_TOK;
        case ';': return SEMICOLON_TOK;

        /* Plus Variants (+, ++, +=) */
        case '+':
            c = fgetc(yyin);
            if (c == '+') { yytext[yyleng++] = (char)c; yytext[yyleng] = '\0'; return INC_TOK; }
            if (c == '=') { yytext[yyleng++] = (char)c; yytext[yyleng] = '\0'; return PLUS_ASSIGN_TOK; }
            if (c != EOF) ungetc(c, yyin);
            return PLUS_TOK;

        /* Minus Variants (-, --, -=) */
        case '-':
            c = fgetc(yyin);
            if (c == '-') { yytext[yyleng++] = (char)c; yytext[yyleng] = '\0'; return DEC_TOK; }
            if (c == '=') { yytext[yyleng++] = (char)c; yytext[yyleng] = '\0'; return MINUS_ASSIGN_TOK; }
            if (c != EOF) ungetc(c, yyin);
            return MINUS_TOK; 

        /* Multiply Variants (*, *=) */
        case '*':
            c = fgetc(yyin);
            if (c == '=') { yytext[yyleng++] = (char)c; yytext[yyleng] = '\0'; return MULT_ASSIGN_TOK; }
            if (c != EOF) ungetc(c, yyin);
            return MULT_TOK;

        /* Divide Variants (/, /=) */
        case '/':
            c = fgetc(yyin);
            if (c == '=') { yytext[yyleng++] = (char)c; yytext[yyleng] = '\0'; return DIV_ASSIGN_TOK; }
            if (c != EOF) ungetc(c, yyin);
            return DIV_TOK;

        /* Modulo Variants (%, %=) */
        case '%':
            c = fgetc(yyin);
            if (c == '=') { yytext[yyleng++] = (char)c; yytext[yyleng] = '\0'; return MOD_ASSIGN_TOK; }
            if (c != EOF) ungetc(c, yyin);
            return MOD_TOK;

        /* Equals Variants (=, ==) */
        case '=':
            c = fgetc(yyin);
            if (c == '=') { yytext[yyleng++] = (char)c; yytext[yyleng] = '\0'; return EQ_EQ_TOK; }
            if (c != EOF) ungetc(c, yyin);
            return EQ_TOK; 

        /* Not Variants (!, !=) */
        case '!':
            c = fgetc(yyin);
            if (c == '=') { yytext[yyleng++] = (char)c; yytext[yyleng] = '\0'; return NEQ_TOK; }
            if (c != EOF) ungetc(c, yyin);
            return LOGICAL_NOT_TOK;

        /* Greater Than Variants (>, >=, >>, >>=) */
        case '>':
            c = fgetc(yyin);
            if (c == '=') { yytext[yyleng++] = (char)c; yytext[yyleng] = '\0'; return GE_TOK; }
            if (c == '>') {
                yytext[yyleng++] = (char)c; yytext[yyleng] = '\0';
                c = fgetc(yyin);
                if (c == '=') { yytext[yyleng++] = (char)c; yytext[yyleng] = '\0'; return RSHIFT_ASSIGN_TOK; }
                if (c != EOF) ungetc(c, yyin);
                return RSHIFT_TOK;
            }
            if (c != EOF) ungetc(c, yyin);
            return GT_TOK; 

        /* Less Than Variants (<, <=, <<, <<=) */
        case '<':
            c = fgetc(yyin);
            if (c == '=') { yytext[yyleng++] = (char)c; yytext[yyleng] = '\0'; return LE_TOK; }
            if (c == '<') {
                yytext[yyleng++] = (char)c; yytext[yyleng] = '\0';
                c = fgetc(yyin);
                if (c == '=') { yytext[yyleng++] = (char)c; yytext[yyleng] = '\0'; return LSHIFT_ASSIGN_TOK; }
                if (c != EOF) ungetc(c, yyin);
                return LSHIFT_TOK;
            }
            if (c != EOF) ungetc(c, yyin);
            return LT_TOK;

        /* Bitwise AND Variants (&, &&, &=) */
        case '&':
            c = fgetc(yyin);
            if (c == '&') { yytext[yyleng++] = (char)c; yytext[yyleng] = '\0'; return LOGICAL_AND_TOK; }
            if (c == '=') { yytext[yyleng++] = (char)c; yytext[yyleng] = '\0'; return AND_ASSIGN_TOK; }
            if (c != EOF) ungetc(c, yyin);
            return BITWISE_AND_TOK;

        /* Bitwise OR Variants (|, ||, |=) */
        case '|':
            c = fgetc(yyin);
            if (c == '|') { yytext[yyleng++] = (char)c; yytext[yyleng] = '\0'; return LOGICAL_OR_TOK; }
            if (c == '=') { yytext[yyleng++] = (char)c; yytext[yyleng] = '\0'; return OR_ASSIGN_TOK; }
            if (c != EOF) ungetc(c, yyin);
            return BITWISE_OR_TOK;

        /* Bitwise XOR Variants (^, ^=) */
        case '^':
            c = fgetc(yyin);
            if (c == '=') { yytext[yyleng++] = (char)c; yytext[yyleng] = '\0'; return XOR_ASSIGN_TOK; }
            if (c != EOF) ungetc(c, yyin);
            return BITWISE_XOR_TOK;

        /* Bitwise NOT (~) */
        case '~':
            return BITWISE_NOT_TOK;

        default:
            return UNKNOWN_TOK;
    }
}

int main(int argc, char *argv[]) {
    int token;
    
    if (argc != 2) {
        printf("Usage: %s <input_source_file.c>\n", argv[0]);
    } else {
        yyin = fopen(argv[1], "r");
        if (!yyin) {
            printf("Error: Cannot open file '%s'\n", argv[1]);
            return 1;
        }

        printf("TOKEN_ID\t%-15s\tLINE_NO\n", "LEXEME");
        printf("------------------------------------------------\n");

        while(!feof(yyin)) { 
            token = yylex();
            if (token == EOF_TOK) break;
            printf("%-8d\t%-15s\t%d\n", token, yytext, yylineno);
        }
        
        fclose(yyin);
    }
    return 0;
}