/*
MEDIUM HARD WAY TO TOKENISE:
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
    TOKEN_BRACE,            // {, }, [, ] ,(, )
    SINGLE_LINE_COMMENT,    // // Comment
    TOKEN_IDENTIFIER,       // User-defined names
    TOKEN_NUMBER,           // Numeric literals
    TOKEN_FOR_LOOP,         // "for" loop
    TOKEN_WHILE_LOOP,       // "while" loop
    DATA_TYPE,              // int, float
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
        "DATA_TYPE",        
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
    // Check for Punctuation
    else if (strcmp(str, ";") == 0 || strcmp(str, ",") == 0 || strcmp(str, ":") == 0 || strcmp(str, "|") == 0 || strcmp(str, "\"") == 0) {
        return TOKEN_PUNCTUATION;
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
    // Check for Brace
    else if (strcmp(str, "[") == 0 || strcmp(str, "]") == 0 || strcmp(str, "{") == 0 || strcmp(str, "}") == 0 || strcmp(str, "(") == 0 || strcmp(str, ")") == 0 ) {
        return TOKEN_BRACE;
    }
    // Check for Data Types
    else if (strcmp(str, "int") == 0 || strcmp(str, "float") == 0 ) {
        return DATA_TYPE;
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



/*BEST LEXER*/
void lexer(const char* input) {
    const char delimiters[] = " \t\n"; // Word delimiters
    char* copy = strdup(input); // Make a copy of the input string
    char* word = strtok(copy, delimiters); // Tokenize the first word

    while (word != NULL) {
        // Tokenize the current word
        Token token = tokenizeWord(word);

        // Get the token type name
        const char* typeName = getTokenTypeName(token.type);

        // Print the token information
        printf(" Lexeme: %s, TokenName: %s, Token: %d\n", token.lexeme, typeName, token.type);

        // Tokenize the next word
        word = strtok(NULL, delimiters);
    }

    // Free the memory allocated for the copy
    free(copy);
}
 
int main() {
    const char* input = "for ( int i = 0 ; i < 10 ; i + + ) { CIAO } while ( x > 0 ) { PASTA } 3 4 34";
    lexer(input);

    return 0;
}

