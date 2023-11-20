/*
SIMPLER WAY TO TOKENISE:
This lexer work really goot, take a look
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// Token types
typedef enum {
    TOKEN_KEYWORD,          // CIAO, PASTA, ALDENTE, etc.
    TOKEN_DATATYPE,         // CARBS, VEGGIE, FORMAGGIO, OIL
    TOKEN_ARITHMETIC_OP,    // +, -, *, /
    TOKEN_COMPARISON_OP,    // ==, !=, <, >, <=, >=, =
    TOKEN_LOGICAL_OP,       // E, OPPURE
    TOKEN_PUNCTUATION,      // ;, , (comma), etc.
    TOKEN_BRACE,            // {, }, [, ]
    SINGLE_LINE_COMMENT,    // // Comment
    TOKEN_IDENTIFIER,       // User-defined names
    TOKEN_NUMBER,           // Numeric literals
    TOKEN_FOR_LOOP,         // "for" loop
    TOKEN_WHILE_LOOP,       // "while" loop
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
        "TOKEN_NUMBER",    
        "TOKEN_FOR_LOOP",         
        "TOKEN_WHILE_LOOP",            
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
    // Check for Arithmetic Operators
    else if (strcmp(str, "+") == 0 || strcmp(str, "-") == 0 || strcmp(str, "*") == 0 || strcmp(str, "/") == 0) {
        return TOKEN_ARITHMETIC_OP;
    }
    // Check for Comparison Operators
    else if (strcmp(str, "!=") == 0 || strcmp(str, "<") == 0 || strcmp(str, ">") == 0 || strcmp(str, "=") == 0) {
        return TOKEN_COMPARISON_OP;
    }
    // Check for Numbers
    else if (strspn(str, "0123456789") == strlen(str)) {
        return TOKEN_NUMBER;
    }
    // Check for "for" loop
    else if (strcmp(str, "for") == 0) {
        return TOKEN_FOR_LOOP;
    }
    // Check for "while" loop
    else if (strcmp(str, "while") == 0) {
        return TOKEN_WHILE_LOOP;
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



// Function to tokenize input string
void tokenizeInput(char* input) {
    char* token = strtok(input, " "); //strtok will split the string whenever it encounters a space.
    
    while (token != NULL) {
        TokenType type = checkKeyword(token);
        printf("Lexeme: %s, Type: %d, TokenName: %s\n", token, type, getTokenTypeName(type));
        token = strtok(NULL, " ");
    }
}

int main() {
    // Example usage
    char input[] = "for ( int i = 0; i < 10; i + + ) { CIAO } while (x > 0) { PASTA }";
    
    // Call the tokenizeInput function with the input string
    tokenizeInput(input);

    return 0;
}
