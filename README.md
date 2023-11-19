
# Italian Cuisine Inspired Programming Language

## Project Overview
This project aims to create a simple, user-friendly programming language based on C, inspired by Italian cuisine and language. It's designed to make programming accessible and engaging, especially for Italian speakers and culinary enthusiasts.

## Features
- **Culinary-Themed Syntax**: Utilizes Italian culinary terms for programming constructs, making it intuitive for our target audience.
- **Simple and Educational**: Ideal for beginners and educational purposes, particularly in Italian learning environments.
- **Focus on Basic Programming Concepts**: Emphasizes fundamental concepts in programming without the complexity of more advanced languages.

## Getting Started
### Prerequisites
- Basic understanding of programming concepts.
- C compiler (like GCC) installed on your system.

### Installation
- Clone the repository: `git clone [repository link]`
- Compile the source files using your C compiler.
- Run the executable to start using the language interpreter.

## Usage
Write your code using the Italian culinary-themed syntax. For example:
- `CIAO()` as the main function.
- Data types like `CARBS`, `VEGGIE` for integers and strings.
- Control structures like `Fusilli` for loops.

Refer to the documentation for detailed syntax and examples.

## Authors
- Diana Rubaga
- Alberto Puliga
- Gregorio Orlando

## Develop a Lexer (Tokenizer):
<p align="center">
  <img src="https://cdn-media-1.freecodecamp.org/images/qade0oMhjMIBsiv29aYB3YpAF-7MmO0mDndO" alt="Image" width="250">
</p>

- ‘Lex’ is short for lexical analysis
- Write regular expressions or a similar method to recognize keywords, identifiers, literals, and symbols.
- Implement a lexer that tokenizes the input code into meaningful components.
- Lexter split a bunch of text into tokens.
- Lexter is a Tokenizer
- Token might be a variable or function name or an operator or a number.
- A frase is a sequence of tokens => the grammar/struction of our lenguage
- Lexter take a string and of source code and spit out a list containing every token.
- Lexer may do tasks such as removing comments or detecting if something is a number or identifier.


- ### Flex:
    - Flex, is a program that generates lexers. 
    -  You give it a file which has a special syntax to describe the language’s grammar. From that it generates a C program which lexes a string and produces the desired output.
