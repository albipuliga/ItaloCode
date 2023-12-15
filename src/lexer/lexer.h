#ifndef LEXER_H
#define LEXER_H

#include "token.h"

// Function prototypes
Token tokenizeWord(char *word);
const char *getTokenTypeName(TokenType type);

#endif
