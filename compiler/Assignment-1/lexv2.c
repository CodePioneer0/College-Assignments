#include "values.h"

/* Helper Function for Error 4: Spelling Error Detection */
int is_spelling_error(const char* str) {
    /* Hardcoded list of common typos for demonstration */
    const char* typos[] = {"whle", "whil", "flot", "floa", "charr", "esle", "iff", "doo", "inr", "forr", "retrn", "viod"};
    int num_typos = 12;
    for(int i = 0; i < num_typos; i++) {
        if(strcmp(str, typos[i]) == 0) return 1;
    }
    return 0;
}

int yylex() {
    int c;
    int len_exceeded = 0;

    /* Skip Whitespace */
    while ((c = fgetc(yyin)) != EOF) {
        if (c == '\n') yylineno++;
        else if (!isspace(c)) break;
    }

    if (c == EOF) return EOF_TOK;

    yyleng = 0;
    yytext[yyleng++] = (char)c;
    yytext[yyleng] = '\0';

    /* IDENTIFIERS AND KEYWORDS */
    if (isalpha(c) || c == '_') {
        while ((c = fgetc(yyin)) != EOF && (isalnum(c) || c == '_')) {
            if (yyleng < MAX_LEXEME_LEN) {
                yytext[yyleng++] = (char)c;
            } else {
                len_exceeded = 1; /* ERROR 1: Track length overflow */
            }
        }
        if (c != EOF) ungetc(c, yyin);
        yytext[yyleng] = '\0';

        if (len_exceeded) {
            return EXCEEDS_LENGTH_ERR_TOK; /* ERROR 1 */
        }
        

        /* Match All 32 Standard C Reserved Words */
        if (strcmp(yytext, "auto") == 0) return AUTO_TOK;
        if (strcmp(yytext, "break") == 0) return BREAK_TOK;
        if (strcmp(yytext, "case") == 0) return CASE_TOK;
        if (strcmp(yytext, "char") == 0) return CHAR_TOK;
        if (strcmp(yytext, "const") == 0) return CONST_TOK;
        if (strcmp(yytext, "continue") == 0) return CONTINUE_TOK;
        if (strcmp(yytext, "default") == 0) return DEFAULT_TOK;
        if (strcmp(yytext, "do") == 0) return DO_TOK;
        if (strcmp(yytext, "double") == 0) return DOUBLE_TOK;
        if (strcmp(yytext, "else") == 0) return ELSE_TOK;
        if (strcmp(yytext, "enum") == 0) return ENUM_TOK;
        if (strcmp(yytext, "extern") == 0) return EXTERN_TOK;
        if (strcmp(yytext, "float") == 0) return FLOAT_TOK;
        if (strcmp(yytext, "for") == 0) return FOR_TOK;
        if (strcmp(yytext, "goto") == 0) return GOTO_TOK;
        if (strcmp(yytext, "if") == 0) return IF_TOK;
        if (strcmp(yytext, "int") == 0) return INT_TOK;
        if (strcmp(yytext, "long") == 0) return LONG_TOK;
        if (strcmp(yytext, "register") == 0) return REGISTER_TOK;
        if (strcmp(yytext, "return") == 0) return RETURN_TOK;
        if (strcmp(yytext, "short") == 0) return SHORT_TOK;
        if (strcmp(yytext, "signed") == 0) return SIGNED_TOK;
        if (strcmp(yytext, "sizeof") == 0) return SIZEOF_TOK;
        if (strcmp(yytext, "static") == 0) return STATIC_TOK;
        if (strcmp(yytext, "struct") == 0) return STRUCT_TOK;
        if (strcmp(yytext, "switch") == 0) return SWITCH_TOK;
        if (strcmp(yytext, "typedef") == 0) return TYPEDEF_TOK;
        if (strcmp(yytext, "union") == 0) return UNION_TOK;
        if (strcmp(yytext, "unsigned") == 0) return UNSIGNED_TOK;
        if (strcmp(yytext, "void") == 0) return VOID_TOK;
        if (strcmp(yytext, "volatile") == 0) return VOLATILE_TOK;
        if (strcmp(yytext, "while") == 0) return WHILE_TOK;

        /* ERROR 4: Spelling Error Check */
        if (is_spelling_error(yytext)) {
            return SPELLING_ERR_TOK;
        }

        return ID_TOK; 
    }

    /* NUMBERS */
    if (isdigit(c)) {
        while ((c = fgetc(yyin)) != EOF && isdigit(c)) {
            if (yyleng < MAX_LEXEME_LEN) {
                yytext[yyleng++] = (char)c;
            } else {
                len_exceeded = 1; /* ERROR 1: Track length overflow */
            }
        }

        /* ERROR 5: Malformed Suffix (e.g., 12$34 or 12abc) */
        if (c != EOF && (isalpha(c) || c == '$' || c == '@' || c == '#')) {
            yytext[yyleng++] = (char)c; /* Capture the bad character */
            yytext[yyleng] = '\0';
            
            /* Consume the rest of the malformed token to reset state */
            while ((c = fgetc(yyin)) != EOF && !isspace(c) && !ispunct(c)) {
                if (yyleng < MAX_LEXEME_LEN) yytext[yyleng++] = (char)c;
            }
            if (c != EOF) ungetc(c, yyin);
            yytext[yyleng] = '\0';
            
            return INVALID_SUFFIX_ERR_TOK; 
        }

        if (c != EOF) ungetc(c, yyin);
        yytext[yyleng] = '\0';

        if (len_exceeded) return EXCEEDS_LENGTH_ERR_TOK; /* ERROR 1 */
        
        return INTCONST_TOK; 
    }

    /* STRING LITERALS & ERROR 3 (Unmatched String) */
    if (c == '"') {
        while ((c = fgetc(yyin)) != EOF && c != '"' && c != '\n') {
            if (yyleng < 1023) yytext[yyleng++] = (char)c;
        }
        
        if (c == '"') {
            yytext[yyleng++] = (char)c;
            yytext[yyleng] = '\0';
            return STRING_TOK;
        } else {
            /* ERROR 3: Reached newline or EOF without closing quote */
            yytext[yyleng] = '\0';
            if (c == '\n') ungetc(c, yyin); 
            return UNMATCHED_STRING_ERR_TOK;
        }
    }

    /* OPERATORS & PUNCTUATION */
    switch (c) {
        case '(': return LPAREN_TOK;
        case ')': return RPAREN_TOK;
        case '{': return LBRACE_TOK;
        case '}': return RBRACE_TOK;
        case ';': return SEMICOLON_TOK;
        case ',' : return COMMA_TOK;
        case '+':
            c = fgetc(yyin);
            if (c == '+') { yytext[yyleng++] = (char)c; yytext[yyleng] = '\0'; return INC_TOK; }
            if (c == '=') { yytext[yyleng++] = (char)c; yytext[yyleng] = '\0'; return PLUS_ASSIGN_TOK; }
            if (c != EOF) ungetc(c, yyin);
            return PLUS_TOK;

        case '-':
            c = fgetc(yyin);
            if (c == '-') { yytext[yyleng++] = (char)c; yytext[yyleng] = '\0'; return DEC_TOK; }
            if (c == '=') { yytext[yyleng++] = (char)c; yytext[yyleng] = '\0'; return MINUS_ASSIGN_TOK; }
            if (c != EOF) ungetc(c, yyin);
            return MINUS_TOK; 

        case '*':
            c = fgetc(yyin);
            if (c == '=') { yytext[yyleng++] = (char)c; yytext[yyleng] = '\0'; return MULT_ASSIGN_TOK; }
            if (c != EOF) ungetc(c, yyin);
            return MULT_TOK;

        case '/':
            c = fgetc(yyin);
            if (c == '=') { yytext[yyleng++] = (char)c; yytext[yyleng] = '\0'; return DIV_ASSIGN_TOK; }
            if (c != EOF) ungetc(c, yyin);
            return DIV_TOK;

        case '%':
            c = fgetc(yyin);
            if (c == '=') { yytext[yyleng++] = (char)c; yytext[yyleng] = '\0'; return MOD_ASSIGN_TOK; }
            if (c != EOF) ungetc(c, yyin);
            return MOD_TOK;

        case '=':
            c = fgetc(yyin);
            if (c == '=') { yytext[yyleng++] = (char)c; yytext[yyleng] = '\0'; return EQ_EQ_TOK; }
            if (c != EOF) ungetc(c, yyin);
            return EQ_TOK; 

        case '!':
            c = fgetc(yyin);
            if (c == '=') { yytext[yyleng++] = (char)c; yytext[yyleng] = '\0'; return NEQ_TOK; }
            if (c != EOF) ungetc(c, yyin);
            return LOGICAL_NOT_TOK;

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

        case '&':
            c = fgetc(yyin);
            if (c == '&') { yytext[yyleng++] = (char)c; yytext[yyleng] = '\0'; return LOGICAL_AND_TOK; }
            if (c == '=') { yytext[yyleng++] = (char)c; yytext[yyleng] = '\0'; return AND_ASSIGN_TOK; }
            if (c != EOF) ungetc(c, yyin);
            return BITWISE_AND_TOK;

        case '|':
            c = fgetc(yyin);
            if (c == '|') { yytext[yyleng++] = (char)c; yytext[yyleng] = '\0'; return LOGICAL_OR_TOK; }
            if (c == '=') { yytext[yyleng++] = (char)c; yytext[yyleng] = '\0'; return OR_ASSIGN_TOK; }
            if (c != EOF) ungetc(c, yyin);
            return BITWISE_OR_TOK;

        case '^':
            c = fgetc(yyin);
            if (c == '=') { yytext[yyleng++] = (char)c; yytext[yyleng] = '\0'; return XOR_ASSIGN_TOK; }
            if (c != EOF) ungetc(c, yyin);
            return BITWISE_XOR_TOK;

        case '~':
            return BITWISE_NOT_TOK;

        /* ERROR 2: Appearance of illegal characters */
        default:
            return ILLEGAL_CHAR_ERR_TOK; 
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

        printf("%-20s | %-15s | %s\n", "TOKEN / ERROR ID", "LEXEME", "LINE NO");
        printf("------------------------------------------------------------\n");

        while(!feof(yyin)) { 
            token = yylex();
            if (token == EOF_TOK) break;

            /* Error Output Routing */
            if (token == EXCEEDS_LENGTH_ERR_TOK) {
                printf("[ERR 1] Exceeds Len  | %-15s | %d\n", "<truncated>", yylineno);
            } else if (token == ILLEGAL_CHAR_ERR_TOK) {
                printf("[ERR 2] Illegal Char | %-15s | %d\n", yytext, yylineno);
            } else if (token == UNMATCHED_STRING_ERR_TOK) {
                printf("[ERR 3] Unmatched Str| %-15s | %d\n", yytext, yylineno);
            } else if (token == SPELLING_ERR_TOK) {
                printf("[ERR 4] Misspelled ID| %-15s | %d\n", yytext, yylineno);
            } else if (token == INVALID_SUFFIX_ERR_TOK) {
                printf("[ERR 5] Bad Suffix   | %-15s | %d\n", yytext, yylineno);
            } else {
                /* Standard Token Routing */
                printf("%-20d | %-15s | %d\n", token, yytext, yylineno);
            }
        }
        
        fclose(yyin);
    }
    return 0;
}