#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>



// Token types
typedef enum {
    CIAO,                   //
    CIAOCIAO,               // return
    INT,                    // int
    STRING,                 // string
    OPEN_PARENTESIS,        // (
    CLOSE_PARENTESIS,       // )
    DUE_PUNTI,              // :
    VIRGOLETTE,             // "
    NUMERO,                 // number
    VARIABILE,              // variable/identifier
    SE,                     // if
    OPPURE,                 // else
    PIU,                    // +
    MENO,                   // -
    PER,                    // *
    DIVISO,                 // /
    UGUALE,                 // =
    DIVERSO,                // !=
    MINORE,                 // <
    MAGGIORE,               // >
    STAMPA,                 // print
    LEGGI,                  // scanf
    BASTA,                  // break
    E,                      // &&
    O,                      // ||
} TokenType;


// given an index it will return the name of the unum token
const char *getTokenTypeName(TokenType type) {
    const char *typeNames[] = {
            "CIAO",
            "CIAOCIAO",
            "INT",
            "STRING",
            "OPEN_PARENTESIS",
            "CLOSE_PARENTESIS",
            "DUE_PUNTI",
            "VIRGOLETTE",
            "NUMERO",
            "VARIABILE",
            "SE",
            "OPPURE",
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


// Token structure
typedef struct {
    TokenType type;
    char *lexeme;
} Token;


// Function to check if a string is a keyword and return its token type
TokenType checkKeyword(char *str) {
    // Check for Keywords
    if (strcmp(str, "ciao") == 0) {return CIAO;}
    else if (strcmp(str, "ciaociao") == 0) {return CIAOCIAO;}
    else if (strcmp(str, "int") == 0) {return INT;}
    else if (strcmp(str, "string") == 0) {return STRING;}
    else if (strcmp(str, "(") == 0) {return OPEN_PARENTESIS;}
    else if (strcmp(str, ")") == 0) {return CLOSE_PARENTESIS;}
    else if (strcmp(str, ":") == 0) {return DUE_PUNTI;}
    else if (strcmp(str, "\"") == 0) {return VIRGOLETTE;}
    else if (strcmp(str, "se") == 0) {return SE;}
    else if (strcmp(str, "oppure") == 0) {return OPPURE;}
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
    //const char *input = "for ( int i = 0 ; i < 10 ; i + + ) { CIAO } while ( x > 0 ) { PASTA } 3 4 34";
    const char *input = "12 piu oppure ciaociao ( )";
    lexer(input);
    return 0;
}
// void main() {test();}
















// AST Node types
typedef enum {
    PROGRAM_NODE,
    EXPRESSION_NODE,
    OPERATION_NODE,
    LITERAL_NODE,
} NodeType;

// AST Node structure
typedef struct TreeNode {
    NodeType type;
    Token token; // Token associated with the node (for literals and operators)
    struct TreeNode *left; // Left child
    struct TreeNode *right; // Right child
} TreeNode;

// Function to create a new AST node
TreeNode* createNode(NodeType type, Token token) {
    TreeNode *node = (TreeNode*)malloc(sizeof(TreeNode));
    node->type = type;
    node->token = token;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Parse functions
TreeNode* parseExpression(Token tokens[], int *currentToken);
TreeNode* parseOperation(Token tokens[], int *currentToken);
TreeNode* parseLiteral(Token tokens[], int *currentToken);

// Parse an entire program
TreeNode* parseProgram(Token tokens[]) {
    int currentToken = 0;
    return parseExpression(tokens, &currentToken);
}

// Parse an expression
TreeNode* parseExpression(Token tokens[], int *currentToken) {
    return parseOperation(tokens, currentToken);
}

// Parse an operation
TreeNode* parseOperation(Token tokens[], int *currentToken) {
    TreeNode *left = parseLiteral(tokens, currentToken);

    while (tokens[*currentToken].type == PIU || tokens[*currentToken].type == PER) {
        Token operatorToken = tokens[(*currentToken)++];
        TreeNode *right = parseLiteral(tokens, currentToken);

        TreeNode *operationNode = createNode(OPERATION_NODE, operatorToken);
        operationNode->left = left;
        operationNode->right = right;

        left = operationNode;
    }

    return left;
}

// Parse a literal
TreeNode* parseLiteral(Token tokens[], int *currentToken) {
    Token literalToken = tokens[(*currentToken)++];
    return createNode(LITERAL_NODE, literalToken);
}

// Print AST
void printAST(TreeNode *root) {
    if (root == NULL) {
        return;
    }

    switch (root->type) {
        case PROGRAM_NODE:
        case EXPRESSION_NODE:
            printAST(root->left);
            break;

        case OPERATION_NODE:
            printf("(");
            printAST(root->left);
            printf(" %s ", getTokenTypeName(root->token.type));
            printAST(root->right);
            printf(")");
            break;

        case LITERAL_NODE:
            printf("%s", root->token.lexeme);
            break;

        default:
            printf("UNKNOWN_NODE_TYPE");
    }
}
// Print AST with indentation
void printASTIndented(TreeNode* root, int level) {
    if (root == NULL) {
        return;
    }

    // Print spaces for indentation
    for (int i = 0; i < level; ++i) {
        printf("  ");
    }

    switch (root->type) {
        case PROGRAM_NODE:
        case EXPRESSION_NODE:
            printf("Expression:\n");
            printASTIndented(root->left, level + 1);
            break;

        case OPERATION_NODE:
            printf("Operation: %s\n", getTokenTypeName(root->token.type));
            printASTIndented(root->left, level + 1);
            printASTIndented(root->right, level + 1);
            break;

        case LITERAL_NODE:
            printf("Literal: %s\n", root->token.lexeme);
            break;

        default:
            printf("UNKNOWN_NODE_TYPE\n");
    }
}

int main() {
    const char *input = "12 piu 4 per 6";
    const char delimiters[] = " \t\n"; // Word delimiters
    char *copy = strdup(input); // Make a copy of the input string
    char *word = strtok(copy, delimiters); // Tokenize the first word
    Token tokens[100]; // Array of tokens
    int tokenCount = 0; // Counter for the number of tokens

    while (word != NULL)
    {
        tokens[tokenCount++] = tokenizeWord(word);
        word = strtok(NULL, delimiters);
    }
    free(copy);

    TreeNode *ast = parseProgram(tokens);

    // Print AST
    printAST(ast);
    printf("\n");
    printASTIndented(ast, 0);
    printf("\n");

    return 0;
}