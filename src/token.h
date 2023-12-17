#ifndef TOKEN_H
#define TOKEN_H

// Token types
typedef enum {
    CIAO, CIAOCIAO, INT, STRING, OPEN_PARENTHESIS, CLOSE_PARENTHESIS, DUE_PUNTI,
    VIRGOLETTE, NUMERO, VARIABILE, SE, OPPURE, PIU, MENO, PER, DIVISO, UGUALE, 
    DIVERSO, MINORE, MAGGIORE, STAMPA, LEGGI, BASTA, E, O,
} TokenType;

// Token structure
typedef struct {
    TokenType type;
    char *lexeme;
} Token;

#endif
