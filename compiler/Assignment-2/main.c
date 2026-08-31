#include "values.h"

/* Externally defined variables created by Flex */
extern int yylex();
extern FILE *yyin;
extern char *yytext;
extern int yylineno;

/* Helper Function for Error 4: Spelling Error Detection */
int is_spelling_error(const char* str) {
    const char* typos[] = {"whle", "whil", "flot", "floa", "charr", "esle", "iff", "doo", "inr", "forr", "retrn", "viod"};
    int num_typos = 12;
    for(int i = 0; i < num_typos; i++) {
        if(strcmp(str, typos[i]) == 0) return 1;
    }
    return 0;
} /* */

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

        /* Flex implicitly updates yytext, yyleng, and yylineno every time yylex() is called */
        while((token = yylex()) != EOF_TOK) { 
            /* Error Output Routing */
            if (token == EXCEEDS_LENGTH_ERR_TOK) {
                printf("[ERR 1] Exceeds Len  | %-15s | %d\n", "<truncated>", yylineno);
            } else if (token == ILLEGAL_CHAR_ERR_TOK) {
                printf("[ERR 2] Illegal Char | %-15s | %d\n", yytext, yylineno);
            } else if (token == UNMATCHED_STRING_ERR_TOK) {
                /* Remove the trailing newline character from the print output for clean formatting */
                yytext[strcspn(yytext, "\n")] = 0;
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
} /*[cite: 11] */