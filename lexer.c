#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// Token types
typedef enum {
    TOKEN_KEYWORD,          // CIAO, PASTA, ALDENTE, etc.
    TOKEN_DATATYPE,         // CARBS, VEGGIE, FORMAGGIO, OIL
    TOKEN_ARITHMETIC_OP,    // +, -, *, /
    TOKEN_COMPARISON_OP,    // ==, !=, <, >, <=, >=
    TOKEN_LOGICAL_OP,       // E, OPPURE
    TOKEN_PUNCTUATION,      // ;, , (comma), etc.
    TOKEN_BRACE,            // {, }, [, ]
    SINGLE_LINE_COMMENT,    // // Comment
    TOKEN_IDENTIFIER,       // User-defined names
    TOKEN_EOF               // End of file/input
} TokenType;


// given an idex it will return the name of the unum token
const char* getTokenTypeName(TokenType type) {
    const char* typeNames[] = {
        "TOKEN_KEYWORD",
        "TOKEN_DATATYPE",
        "TOKEN_ARITHMETIC_OP",
        "TOKEN_COMPARISON_OP",
        "TOKEN_LOGICAL_OP",
        "TOKEN_PUNCTUATION",
        "TOKEN_BRACE",
        "SINGLE_LINE_COMMENT",
        "TOKEN_IDENTIFIER",
        "TOKEN_EOF"
    };

    if (type >= TOKEN_KEYWORD && type <= TOKEN_EOF) {
        return typeNames[type];
    }

    return "UNKNOWN_TOKEN_TYPE";
}

// Token structure
typedef struct {
    TokenType type;
    char* lexeme;
} Token;

// Function to check if a string is a keyword and return its token type
TokenType checkKeyword(char* str) {
    // Check for Keywords
    if (strcmp(str, "CIAO") == 0 || strcmp(str, "PASTA") == 0 || strcmp(str, "ALDENTE") == 0 /* ... other keywords ... */) {
        return TOKEN_KEYWORD;
    }
    // Check for Data Types
    else if (strcmp(str, "CARBS") == 0 || strcmp(str, "VEGGIE") == 0 || strcmp(str, "FORMAGGIO") == 0 || strcmp(str, "OLIO") == 0) {
        return TOKEN_DATATYPE;
    }
    // Check for Logical Operators
    else if (strcmp(str, "E") == 0 || strcmp(str, "OPPURE") == 0) {
        return TOKEN_LOGICAL_OP;
    }
    // Check for Single Line Comment
    else if (strncmp(str, "//", 2) == 0) {
        return SINGLE_LINE_COMMENT;
    }
    // Default to Identifier
    else {
        return TOKEN_IDENTIFIER;
    }
}


// Function to tokenize a single word
Token tokenizeWord(char* word) {
    Token token;
    token.type = checkKeyword(word);
    token.lexeme = strdup(word);
    return token;
}

// Main lexer function
void lexer(const char* source) {
    char currentWord[256]; 
    int wordIndex = 0;

    for (int i = 0; source[i] != '\0'; i++) {
        char currentChar = source[i];

        if (isspace(currentChar) || ispunct(currentChar)) {
            if (wordIndex != 0) {
                currentWord[wordIndex] = '\0';
                Token token = tokenizeWord(currentWord);
                const char* typeName = getTokenTypeName(token.type);
                printf("TokenName: %s, Token: %d, Lexeme: %s\n", typeName, token.type, token.lexeme);
                free(token.lexeme);
                wordIndex = 0;
            }

            if (ispunct(currentChar)) {
                // Handle punctuation and braces as separate tokens
                // This is a simplification; in a full lexer, you'd handle each punctuation mark separately
                TokenType type = (currentChar == ';' || currentChar == ',') ? TOKEN_PUNCTUATION : TOKEN_BRACE;
                printf("Token: %d, Lexeme: %c\n", type, currentChar);
            }
        } else {
            currentWord[wordIndex++] = currentChar;
        }
    }

    // Handle the last word
    if (wordIndex != 0) {
        currentWord[wordIndex] = '\0';
        Token token = tokenizeWord(currentWord);
        printf("Token: %d, Lexeme: %s\n", token.type, token.lexeme);
        free(token.lexeme);
    }
}

int main() {
    const char* sourceCode = "CIAO PASTA CARBS ; { }"; // Example source codeπ
    lexer(sourceCode);
    return 0;
}
