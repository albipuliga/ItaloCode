#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "lexer.h"

// AST Node types
typedef enum {
    PROGRAM_NODE,
    EXPRESSION_NODE,
    OPERATION_NODE,
    LITERAL_NODE,
    VARIABLE_NODE,
    PRINT_NODE,
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

////////////Parse functions////////////
TreeNode* parseExpression(Token tokens[], int *currentToken);
TreeNode* parseTerm(Token tokens[], int *currentToken);
TreeNode* parseFactor(Token tokens[], int *currentToken);
TreeNode* parsePrint(Token tokens[], int *currentToken); // Added for STAMPA

// Parse a literal
TreeNode* parseLiteral(Token tokens[], int *currentToken) {
    Token literalToken = tokens[(*currentToken)++];

    if (literalToken.type == NUMERO) {
        return createNode(LITERAL_NODE, literalToken);
    } else {
        return createNode(VARIABLE_NODE, literalToken);
    }
}

// Parse an entire program
TreeNode* parseProgram(Token tokens[]) {
    int currentToken = 0;
    return parseExpression(tokens, &currentToken);
}

// Parse an expression
TreeNode* parseExpression(Token tokens[], int *currentToken) {
    if (tokens[*currentToken].type == STAMPA) {
        return parsePrint(tokens, currentToken);
    }
    return parseTerm(tokens, currentToken);
}

// Parse a print statement
TreeNode* parsePrint(Token tokens[], int *currentToken) {
    (*currentToken)++; // Skip the STAMPA token
    TreeNode *valueToPrint = parseExpression(tokens, currentToken);
    TreeNode *printNode = createNode(PRINT_NODE, (Token){STAMPA, "stampa"});
    printNode->left = valueToPrint;
    return printNode;
}

// Parse a term (handles addition and subtraction)
TreeNode* parseTerm(Token tokens[], int *currentToken) {
    TreeNode *left = parseFactor(tokens, currentToken);

    while (tokens[*currentToken].type == PIU || tokens[*currentToken].type == MENO) {
        Token operatorToken = tokens[(*currentToken)++];
        // Check if there is a token after the operator
        if (tokens[*currentToken].type == NUMERO || tokens[*currentToken].type == NUMERO) {
            TreeNode *right = parseFactor(tokens, currentToken);

            TreeNode *operationNode = createNode(OPERATION_NODE, operatorToken);
            operationNode->left = left;
            operationNode->right = right;

            left = operationNode;
        } else {
            fprintf(stderr, "Error: Missing argument after operator %s\n", getTokenTypeName(operatorToken.type));
            // Handle the error (exit or return an error code)
        }
    }

    return left;
}

// Parse a factor (handles multiplication and division)
TreeNode* parseFactor(Token tokens[], int *currentToken) {
    TreeNode *left = parseLiteral(tokens, currentToken);

    while (tokens[*currentToken].type == PER || tokens[*currentToken].type == DIVISO) {
        Token operatorToken = tokens[(*currentToken)++];
        TreeNode *right = parseLiteral(tokens, currentToken);

        TreeNode *operationNode = createNode(OPERATION_NODE, operatorToken);
        operationNode->left = left;
        operationNode->right = right;

        left = operationNode;
    }

    return left;
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

        case VARIABLE_NODE:
            printf("VARIABLE_NODE: %s", root->token.lexeme);  // Display variable name
            break;

        case PRINT_NODE:
            printf("Stampa(");
            printAST(root->left);  // Print the content of the expression
            printf(")");
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

        case VARIABLE_NODE:
            //printf("%s", root->token.lexeme);  // Display variable name
            break;

        case PRINT_NODE:
            //printf("Stampa(");
            //printAST(root->left);  // Print the content of the expression
            //printf(")\n");
            break;

        default:
            printf("UNKNOWN_NODE_TYPE\n");
    }
}

// Function to evaluate an AST node
char* evaluate(TreeNode *node) {
    char* leftValueStr = NULL;
    char* rightValueStr = NULL;
    char *result;

    // Function to evaluate an AST node and return the result as a string
    if (node == NULL) {
        char *emptyString = malloc(1);
        emptyString[0] = '\0';
        return emptyString;
    }

    switch (node->type) {
        case LITERAL_NODE:
            result = malloc(strlen(node->token.lexeme) + 1);
            strcpy(result, node->token.lexeme);
            return result;

        case VARIABLE_NODE:
            result = malloc(strlen(node->token.lexeme) + 1);
            strcpy(result, node->token.lexeme);
            return result;

        case OPERATION_NODE:
            leftValueStr = evaluate(node->left);
            rightValueStr = evaluate(node->right);
            if (leftValueStr == NULL || rightValueStr == NULL) {
                // Handle error: Memory allocation failure in subexpression evaluation
                char *errorResult = malloc(strlen("Error: Memory allocation failure") + 1);
                strcpy(errorResult, "Error: Memory allocation failure");
                // Free memory for partial results
                free(leftValueStr);
                free(rightValueStr);
                return errorResult;
            }
            //turn string into int
            int leftValue = atoi(leftValueStr);
            int rightValue = atoi(rightValueStr);
            if (node->token.type == PIU){
                int resultValue = leftValue + rightValue;
                result = malloc(12);
                // turn int into string
                sprintf(result, "%d", resultValue);
                free(leftValueStr);
                free(rightValueStr);
                return result;
            }
            else if (node->token.type == MENO){
                int resultValue = leftValue - rightValue;
                result = malloc(12);
                sprintf(result, "%d", resultValue);
                free(leftValueStr);
                free(rightValueStr);
                return result;
            }
            else if (node->token.type == PER){
                int resultValue = leftValue * rightValue;
                result = malloc(12);
                sprintf(result, "%d", resultValue);
                free(leftValueStr);
                free(rightValueStr);
                return result;
            }
            else if (node->token.type == DIVISO){
                if (rightValue != 0) {
                    int resultValue = leftValue / rightValue;
                    result = malloc(12);
                    sprintf(result, "%d", resultValue);
                    free(leftValueStr);
                    free(rightValueStr);
                    return result;
                } else {
                    fprintf(stderr, "Error: Division by zero, discard result");
                    char *errorResult = malloc(strlen("Error: Division by zero") + 1);
                    strcpy(errorResult, "Error: Division by zero");
                    free(leftValueStr);
                    free(rightValueStr);
                    return errorResult;
                }
            }

        case PRINT_NODE:
            return evaluate(node->left);

        default:
            return NULL;
    }
}

int main() {
    printf("\nITALO CODE\n");
    printf("Let's learn some math!\n\n\n");
    FILE *file;
    char buffer[1024]; // Buffer to store each line of the file

    // Open the file
    file = fopen("input.txt", "r"); //src/
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    // Read and process each line of the file
    while (fgets(buffer, sizeof(buffer), file)) {
        // Check if the line ends with " !"
        size_t lineLength = strlen(buffer);
        size_t newlinePos = strcspn(buffer, "\n");

        if (newlinePos == lineLength - 1) {
            // Check if the substring from newlinePos to the end is " !"
            if (strncmp(buffer + newlinePos - 2, " !", 2) != 0) {
                fprintf(stderr, "Error: There is a line that does not end with ' !'\n");
                fclose(file);
                return 1;
            }
        }
        const char delimiters[] = " !"; // Word delimiters
        char *copy = strdup(buffer); // Make a copy of the buffer
        char *word = strtok(copy, delimiters); // Tokenize the first word
        Token tokens[100]; // Array of tokens
        int tokenCount = 0; // Counter for the number of tokens

        while (word != NULL) {
            tokens[tokenCount++] = tokenizeWord(word);
            word = strtok(NULL, delimiters);
        }

        free(copy);

        TreeNode *ast = parseProgram(tokens);

        // Print AST
        printAST(ast);
        printf("\n");
        printASTIndented(ast, 0);
        char *result = evaluate(ast);
        printf("--> Evaluation Result: %s\n\n", result);

        free(result);  // Free the dynamically allocated memory
    }

    fclose(file); // Close the file
    return 0;
}