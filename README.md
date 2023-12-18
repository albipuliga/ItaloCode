*# Italian Cuisine Inspired Programming Language

## Table of Contents
- [Table of Contents](#table-of-contents)
- [Project Overview](#project-overview)
- [Authors](#authors)
- [Features](#features)
- [Additional information \& resources](#additional-information--resources)
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Installation](#installation)
- [Usage](#usage)
- [How It Works](#how-it-works)
  - [Compilation and Linking](#compilation-and-linking)
  - [Input Format](#input-format)
  - [Arithmetic Operations](#arithmetic-operations)
  - [Print Statements](#print-statements)
- [Develop a Lexer (Tokenizer)](#develop-a-lexer-tokenizer)
  - [Implementation Overview (`lexer.c`)](#implementation-overview-lexerc)
    - [`getTokenTypeName`](#gettokentypename)
    - [`checkKeyword`](#checkkeyword)
    - [`tokenizeWord`](#tokenizeword)
    - [`lexer`](#lexer)
    - [`test`](#test)
  - [Implementation Overview (`parser.c`)](#implementation-overview-parserc)
    - [AST Node types](#ast-node-types)
    - [AST Node structure](#ast-node-structure)
    - [`createNode`](#createnode)
    - [Parse functions](#parse-functions)
    - [`parseLiteral`](#parseliteral)
    - [`parseProgram`](#parseprogram)
    - [`parseExpression`](#parseexpression)
    - [`parseTerm`](#parseterm)
    - [`parseFactor`](#parsefactor)
    - [Print AST](#print-ast)
    - [`printAST`](#printast)
    - [`printASTIndented`](#printastindented)
    - [Evaluate AST](#evaluate-ast)
    - [`evaluate`](#evaluate)
    - [Main function](#main-function)
- [Header Files for Lexer (`token.h` and `lexer.h`)](#header-files-for-lexer-tokenh-and-lexerh)
  - [`token.h`](#tokenh)
  - [`lexer.h`](#lexerh)
- [Compilation and Linking Commands](#compilation-and-linking-commands)

## Project Overview
This project aims to create a simple, user-friendly programming language based on C, inspired by Italian cuisine and language. It is designed to be highly scalable, allowing for the easy addition of new tokens and the configuration of corresponding parser functions. The project currently supports basic arithmetic operations and print statements, providing a solid foundation for further development.

## Authors
- Diana Rubaga
- Alberto Puliga
- Gregorio Orlando

## Features
- **Italian Terms Syntax**: Utilizes Italian terms for programming constructs, making it intuitive for our target audience.
- **Simple and Educational**: Ideal for beginners and educational purposes, particularly in Italian learning environments.
- **Scalable**: Easy addition of new tokens and configuration of parser functions for extensibility.
- **Focus on Basic Programming Concepts**: Emphasizes fundamental concepts in programming without the complexity of more advanced languages.

## Additional information & resources
Please check out the `./documentation` folder to find a detailed PDF report and videos showing the functioning of each file.

## Getting Started
### Prerequisites
- Basic understanding of programming concepts.
- C compiler (like GCC) installed on your system.

### Installation
- Clone the repository: `git clone https://github.com/albipuliga/ItaloCode`
- Compile the source files using your C compiler. Run this command to link lexer.c with parser.c thank to the header files we prepared.
```bash
gcc lexer.c parser.c -o myprogram
```
- Run the executable to start using the language interpreter.

## Usage
Write your code using the Italian syntax. For instance:
- `stampa` for printing. Add what you want to print after the command `stampa` without spaces.
- `piu`, `meno` `per`, and `diviso` for mathematical arithmetics.
- `PS` for comments. If you write `PS`, the interpreter will skipp everything in his line.
- ` !` for ending each line (with a blank space before it). At the end of each line a exclamation mark is needed.
- Write everything in lower letter.

Refer to the documentation for detailed syntax and examples.

## How It Works
### Compilation and Linking
To compile and link the lexer implementation (`lexer.c`) with the parser (`parser.c`), use the following commands:
```bash
gcc lexer.c parser.c -o myprogram
```
This compiles both source files and links them into an executable named `myprogram`. The header files (`token.h` and `lexer.h`) ensure that necessary declarations are available during compilation, promoting code organization and ease of maintenance.
### Input Format
1. Each line of code in the input file (`input.txt`) should end with a " !" to denote the end of the line.
2. All lines in `input.txt` should be written in lowercase, and the use of parentheses does not have any specific meaning in the current implementation.
### Arithmetic Operations
To perform arithmetic operations, follow the format:
```bash
number operation number !
```
for example:
```bash
5 + 3 !
```
### Print Statements
To execute print statements, use the following format:
```bash
stampa what-u-want-to-print !
```
for example:
```bash
stampa ciao-come-stai? !
```

## Develop a Lexer (Tokenizer)
### Implementation Overview (`lexer.c`)
The `lexer.c` file contains the implementation of the lexer, which is responsible for tokenizing the input code into meaningful components. Below are key functions and their descriptions:

#### `getTokenTypeName`
Given a token type, this function returns the corresponding name of the token.

#### `checkKeyword`
This function checks if a given string is a keyword and returns its token type.

#### `tokenizeWord`
This function tokenizes a single word, returning a `Token` structure.

#### `lexer`
The main lexer function that takes an input string and tokenizes it using the specified delimiters.

#### `test`
A test function with an example input string to demonstrate the lexer.

To use the lexer, you can call the `lexer` function with your input code.

### Implementation Overview (`parser.c`)
The `parser.c` file contains the implementation of the parser, which is responsible for building an Abstract Syntax Tree (AST) from the tokens generated by the lexer. Below are key components and their descriptions:

#### AST Node types
Enumeration of different node types in the Abstract Syntax Tree (AST), including Program, Expression, Operation, Literal, and Variable.

#### AST Node structure
Structure defining the nodes of the Abstract Syntax Tree (AST), including the type of the node, the associated token, and pointers to left and right child nodes.

#### `createNode`
Function to create a new AST node with the specified type and token.

#### Parse functions
Functions responsible for parsing different parts of the code and constructing the AST, including `parseLiteral`, `parseProgram`, `parseExpression`, `parseTerm`, and `parseFactor`.

#### `parseLiteral`
Function to parse a literal, handling both numbers and variables.

#### `parseProgram`
Function to parse an entire program, typically an expression.

#### `parseExpression`
Function to parse an expression.

#### `parseTerm`
Function to parse a term, handling addition and subtraction.

#### `parseFactor`
Function to parse a factor, handling multiplication and division.

#### Print AST
Functions for printing the AST in a readable format, including `printAST` and `printASTIndented`.

#### `printAST`
Function to print the AST in a simple format.

#### `printASTIndented`
Function to print the AST with indentation for better readability.

#### Evaluate AST
Functions for evaluating the AST, including `evaluate` and `main`.

#### `evaluate`
Function to evaluate the result of an AST node, supporting basic arithmetic operations.

#### Main function
The main function reads code from a file, tokenizes it using the lexer, parses it into an AST, prints the AST, and evaluates the result.

## Header Files for Lexer (`token.h` and `lexer.h`)

### `token.h`
- **Contents:** Defines token types (`enum TokenType`) and the token structure (`struct Token`).
- **Purpose:** Provides clear token-related declarations for use in other source files.

### `lexer.h`
- **Contents:** Includes `token.h` and declares function prototypes (`tokenizeWord` and `getTokenTypeName`) used in `lexer.c`.
- **Purpose:** Enables importing lexer-related declarations in other source files (e.g., `parser.c`) without exposing implementation details, promoting code organization and ease of maintenance.

## Compilation and Linking Commands

To compile and link the lexer implementation (`lexer.c`) with the parser (`parser.c`), use the following commands:

```bash
gcc lexer.c parser.c -o myprogram
```

These commands compile both source files and link them into an executable named `myprogram`. Header files ensure necessary declarations are available during compilation, allowing `parser.c` to use functions and structures defined in `lexer.c`.
*