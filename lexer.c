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
void lexer(const char* source) {        //takes a constant character pointer (const char*) as an argument.
    char currentWord[256];      // Declares an array of characters named currentWord. Used to store the current word being processed by the lexer.
    int wordIndex = 0;      // used to keep track of the current index in the currentWord array.

    for (int i = 0; source[i] != '\0'; i++) {       // loop that iterates over each character in the source string until the null terminator ('\0') is encountered.
        char currentChar = source[i];       // Assigns the current character to a variable named currentChar.

        if (isspace(currentChar) || ispunct(currentChar)) {     //Checks if the current character is a space or punctuation 
            if (wordIndex != 0) {       // Checks if there are characters in currentWord
                currentWord[wordIndex] = '\0';      // Appends a null terminator to currentWord, indicating the end of the current word.
                Token token = tokenizeWord(currentWord);        // Calls the tokenizeWord function with currentWord as an argument to create a Token structure named token
                const char* typeName = getTokenTypeName(token.type);        // Gets the string representation of the token type
                printf("TokenName: %s, Token: %d, Lexeme: %s\n", typeName, token.type, token.lexeme);       // Prints information about the token
                free(token.lexeme);     // frees memory
                wordIndex = 0;      // Resets wordIndex to 0 for the next word.
            }

            if (ispunct(currentChar)) {     // Checks if the current character is a punctuation mark.
                // Handle punctuation and braces as separate tokens
                // This is a simplification; in a full lexer, you'd handle each punctuation mark separately
                TokenType type = (currentChar == ';' || currentChar == ',') ? TOKEN_PUNCTUATION : TOKEN_BRACE;      // Determines the token type based on whether the current character is a semicolon or comma
                printf("Token: %d, Lexeme: %c\n", type, currentChar);
            }
        } else {
            currentWord[wordIndex++] = currentChar;     // Adds the current character to currentWord and increments wordIndex to move to the next position in the array.
        }
    }

    // Handle the last word
    if (wordIndex != 0) {
        currentWord[wordIndex] = '\0';
        Token token = tokenizeWord(currentWord);        // Calls the tokenizeWord function with currentWord as an argument to create a Token structure named token
        printf("Token: %d, Lexeme: %s\n", token.type, token.lexeme);
        free(token.lexeme);
    }
}




int main() {
    const char* sourceCode = "CIAO PASTA CARBS ; { }"; // Example source code
    lexer(sourceCode);
    return 0;
}
