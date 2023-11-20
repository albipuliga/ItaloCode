/*
REALLY COMPLICATE WAY TO TOKENISE:
*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef enum {
    TOKEN_CIAO, TOKEN_CIAOCIAO, TOKEN_RO, 
    TOKEN_CARBS, TOKEN_VEGGIE, TOKEN_MEAT,
    TOKEN_FUSILLI, TOKEN_FORCHETTA, TOKEN_COLTELLO, 
    TOKEN_SCRIVI, TOKEN_LEGGI, TOKEN_BASTA,
    TOKEN_BICCHIERI, TOKEN_EOF, TOKEN_ERROR,
    TOKEN_CUCINA, TOKEN_PER_MIN
} TokenType;

typedef struct {
    const char* source_code;
    size_t index;
} Lexer;

typedef struct {
    TokenType type;
    char* value; 
} Token;

int starts_with(const char* source, const char* str) {
    return strncmp(source, str, strlen(str)) == 0;
}

int is_digit(char c) {
    return c >= '0' && c <= '9';
}

Lexer init_lexer(const char* source_code) {
    return (Lexer){ .source_code = source_code, .index = 0 };
}



Token get_next_token(Lexer* lexer) {
    while (lexer->source_code[lexer->index] != '\0') {
        char current_char = lexer->source_code[lexer->index];

        // Skip whitespace
        if (current_char == ' ' || current_char == '\n' || current_char == '\t') {
            lexer->index++;
            continue;
        }

        // Handling specific tokens
        if (starts_with(&lexer->source_code[lexer->index], "CIAO()")) {
            lexer->index += strlen("CIAO()");
            return (Token){ .type = TOKEN_CIAO, .value = NULL };
        } else if (starts_with(&lexer->source_code[lexer->index], "CIAOCIAO()")) {
            lexer->index += strlen("CIAOCIAO()");
            return (Token){ .type = TOKEN_CIAOCIAO, .value = NULL };
        } else if (starts_with(&lexer->source_code[lexer->index], "RO")) {
            // Assuming RO starts a comment, skipping until end of line
            while (lexer->source_code[lexer->index] != '\n' && lexer->source_code[lexer->index] != '\0') {
                lexer->index++;
            }
            continue; // Skipping the token and continuing to the next
        } else if (starts_with(&lexer->source_code[lexer->index], "carbs")) {
            lexer->index += strlen("carbs");
            return (Token){ .type = TOKEN_CARBS, .value = NULL };
        } else if (starts_with(&lexer->source_code[lexer->index], "veggie")) {
            lexer->index += strlen("veggie");
            return (Token){ .type = TOKEN_VEGGIE, .value = NULL };
        } else if (starts_with(&lexer->source_code[lexer->index], "meat")) {
            lexer->index += strlen("meat");
            return (Token){ .type = TOKEN_MEAT, .value = NULL };
        } else if (starts_with(&lexer->source_code[lexer->index], "fusilli")) {
            lexer->index += strlen("fusilli");
            return (Token){ .type = TOKEN_FUSILLI, .value = NULL };
        } else if (starts_with(&lexer->source_code[lexer->index], "cucina")) {
            lexer->index += strlen("cucina");
            return (Token){ .type = TOKEN_CUCINA, .value = NULL };
        } else if (starts_with(&lexer->source_code[lexer->index], "forchetta")) {
            lexer->index += strlen("forchetta");
            return (Token){ .type = TOKEN_FORCHETTA, .value = NULL };
        } else if (starts_with(&lexer->source_code[lexer->index], "coltello")) {
            lexer->index += strlen("coltello");
            return (Token){ .type = TOKEN_COLTELLO, .value = NULL };
        } else if (starts_with(&lexer->source_code[lexer->index], "Scrivi(")) {
            lexer->index += strlen("Scrivi(");
            return (Token){ .type = TOKEN_SCRIVI, .value = NULL };
        } else if (starts_with(&lexer->source_code[lexer->index], "Leggi(")) {
            lexer->index += strlen("Leggi(");
            return (Token){ .type = TOKEN_LEGGI, .value = NULL };
        } else if (starts_with(&lexer->source_code[lexer->index], "basta()")) {
            lexer->index += strlen("basta()");
            return (Token){ .type = TOKEN_BASTA, .value = NULL };
        }else if (starts_with(&lexer->source_code[lexer->index], "bicchieri")) {
            lexer->index += strlen("bicchieri");
            return (Token){ .type = TOKEN_BICCHIERI, .value = NULL };
        } else if (starts_with(&lexer->source_code[lexer->index], "per ")) {
            lexer->index += strlen("per ");
            // Extract the number here and handle it accordingly
            while (is_digit(lexer->source_code[lexer->index])) {
                lexer->index++;
            }
            if (starts_with(&lexer->source_code[lexer->index], " min")) {
                lexer->index += strlen(" min");
                return (Token){ .type = TOKEN_PER_MIN, .value = NULL };
            }
        }

        // Unrecognized token handling
        if (lexer->source_code[lexer->index] != '\0') {
            lexer->index++;
            return (Token){ .type = TOKEN_ERROR, .value = NULL };
        }
    }

    return (Token){ .type = TOKEN_EOF, .value = NULL };
}

void test_lexer(const char* source_code) {
    Lexer lexer = init_lexer(source_code);
    Token token;
    do {
        token = get_next_token(&lexer);
        printf("Token Type: %d\n", token.type);  // You can enhance this to print token names
    } while (token.type != TOKEN_EOF && token.type != TOKEN_ERROR);
}

int main() {
    test_lexer("CIAO() RO This is a comment \n carbs meat fusilli");
    // Add more test strings
    return 0;
}
