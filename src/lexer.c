#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "lexer.h"
#include "token.h"


// given an index it will return the name of the unum token
const char *getTokenTypeName(TokenType type) {
    const char *typeNames[] = {
            "CIAO",
            "CIAOCIAO",
            "INT",
            "STRING",
            "OPEN_PARENTHESIS",
            "CLOSE_PARENTHESIS",
            "DUE_PUNTI",
            "VIRGOLETTE",
            "NUMERO",
            "VARIABILE",
            "SE",
            "OPPURE",
            "PS",
            "PIU",
            "MENO",
            "PER",
            "DIVISO",
            "UGUALE",
            "DIVERSO",
            "MINORE",
            "MAGGIORE",
            "STAMPA",
            "LEGGI",
            "BASTA",
            "E",
            "O"
    };

    if (type >= CIAO && type <= O) {
        return typeNames[type];
    }

    return "UNKNOWN_TOKEN_TYPE";
}


// Function to check if a string is a keyword and return its token type
TokenType checkKeyword(char *str) {
    // Check for Keywords
    if (strcmp(str, "ciao") == 0) {return CIAO;}
    else if (strcmp(str, "ciaociao") == 0) {return CIAOCIAO;}
    else if (strcmp(str, "int") == 0) {return INT;}
    else if (strcmp(str, "string") == 0) {return STRING;}
    else if (strcmp(str, "(") == 0) {return OPEN_PARENTHESIS;}
    else if (strcmp(str, ")") == 0) {return CLOSE_PARENTHESIS;}
    else if (strcmp(str, ":") == 0) {return DUE_PUNTI;}
    else if (strcmp(str, "\"") == 0) {return VIRGOLETTE;}
    else if (strcmp(str, "se") == 0) {return SE;}
    else if (strcmp(str, "oppure") == 0) {return OPPURE;}
    else if (strcmp(str, "PS") == 0) {return PS;}
    else if (strcmp(str, "piu") == 0) {return PIU;}
    else if (strcmp(str, "meno") == 0) {return MENO;}
    else if (strcmp(str, "per") == 0) {return PER;}
    else if (strcmp(str, "diviso") == 0) {return DIVISO;}
    else if (strcmp(str, "=") == 0) {return UGUALE;}
    else if (strcmp(str, "!=") == 0) {return DIVERSO;}
    else if (strcmp(str, "<") == 0) {return MINORE;}
    else if (strcmp(str, ">") == 0) {return MAGGIORE;}
    else if (strspn(str, "0123456789") == strlen(str)) {return NUMERO;}
    else if (strcmp(str, "stampa") == 0) {return STAMPA;}
    else if (strcmp(str, "leggi") == 0) {return LEGGI;}
    else if (strcmp(str, "basta") == 0) {return BASTA;}
    else if (strcmp(str, "e") == 0) {return E;}
    else if (strcmp(str, "o") == 0) {return O;}
    else {return VARIABILE;} // Default to Identifier is variable
}


// Function to tokenize a single word
Token tokenizeWord(char *word) {
    Token token;
    token.type = checkKeyword(word);
    token.lexeme = strdup(word);
    return token;
}


/*BEST LEXER*/
void lexer(const char *input) {
    const char delimiters[] = " \t\n"; // Word delimiters
    char *copy = strdup(input); // Make a copy of the input string
    char *word = strtok(copy, delimiters); // Tokenize the first word

    while (word != NULL) {
        // Tokenize the current word
        Token token = tokenizeWord(word);

        // Get the token type name
        const char *typeName = getTokenTypeName(token.type);

        // Print the token information
        printf(" Lexeme: %s, TokenName: %s, Token: %d\n", token.lexeme, typeName, token.type);

        // Tokenize the next word
        word = strtok(NULL, delimiters);
    }

    // Free the memory allocated for the copy
    free(copy);
}

int test() {
    const char *input = "12 PS piu oppure ciaociao ( )";
    lexer(input);
    return 0;
}
void main() {test();}

